#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "IdBurnerMain.h"


IdBurnerMain::IdBurnerMain( wxWindow* parent )
:
GUIFrame( parent ), configuration("idburner.conf"), idValidator( wxFILTER_ALPHANUMERIC), numValidator( wxFILTER_NUMERIC )
{

    typeID->SetInitialSize(typeID->GetSizeFromTextSize(typeID->GetTextExtent("MM").x));
    dateID->SetInitialSize(dateID->GetSizeFromTextSize(dateID->GetTextExtent("MMMMMM").x));
    deviceID->SetInitialSize(deviceID->GetSizeFromTextSize(deviceID->GetTextExtent("MM").x));

    typeID->SetValidator(idValidator);
    dateID->SetValidator(numValidator);
    deviceID->SetValidator(idValidator);

    manual = false;

    RefreshDeviceList();
    ReloadConfig();

    if(!fileExists("idburner.conf")) {
        fileCreate("idburner.conf");
    }

    dateID->SetLabel(wxDateTime::Today().Format("%y%m%d"));

}

void IdBurnerMain::OnClose( wxCloseEvent& event )
{
    Destroy();
}

void IdBurnerMain::OnQuit( wxCommandEvent& event )
{
    Destroy();
}

void IdBurnerMain::OnAbout( wxCommandEvent& event )
{
    IdBurnerAboutDialog about(this);
    about.ShowModal();
}

void IdBurnerMain::OnRefresh( wxCommandEvent& event )
{
    RefreshDeviceList();
}

void IdBurnerMain::OnReload( wxCommandEvent& event ) {
    ReloadConfig();
}

void IdBurnerMain::OnTypeChoice( wxCommandEvent& event ) {
    if(ChoiceDeviceType->GetString(0) == "Device Type" && ChoiceDeviceType->GetCurrentSelection() != 0) {
        ChoiceDeviceType->Delete(0);
    }
    std::string selection = ChoiceDeviceType->GetString(ChoiceDeviceType->GetCurrentSelection()).ToStdString();
    if(selection != "Device Type" ) {
        UpdateID(selection);
    }


}

void IdBurnerMain::OnAdd( wxCommandEvent& event )
{
    std::string edited="";
    IdBurnerAddDialog add(this, "idburner.conf", edited);
    int result = add.ShowModal();
    if(result == 1) {
        configuration.updateConfig();
        ReloadConfig(edited);
        UpdateID(edited);
    }
}

void IdBurnerMain::OnEdit( wxCommandEvent& event )
{
    std::string selection = ChoiceDeviceType->GetString(ChoiceDeviceType->GetCurrentSelection()).ToStdString();
    std::string edited;

    if(selection != "Device Type") {
        IdBurnerEditDialog edit(this, "idburner.conf", configuration.getSectionByValue("name", selection), edited);
        int result = edit.ShowModal();
        if(result == 1) {
             configuration.updateConfig();
             ReloadConfig(edited);
             UpdateID(edited);
        }
    } else {
        wxMessageBox(_("Choose Device Type to edit"), _(""));
    }

}

void IdBurnerMain::OnDelete( wxCommandEvent& event )
{
    std::string selection = ChoiceDeviceType->GetString(ChoiceDeviceType->GetCurrentSelection()).ToStdString();

    if(selection != "Device Type") {
        configuration.deleteSection(configuration.getSectionByValue("name", selection));
        ChoiceDeviceType->Delete(ChoiceDeviceType->GetCurrentSelection());
        ChoiceDeviceType->SetSelection(0);
    } else {
        wxMessageBox(_("Choose Device Type to be removed"), _(""));
    }
}

void IdBurnerMain::OnDateUpdate( wxDateEvent& event )
{
    dateID->SetLabel(pickDate->GetValue().Format("%y%m%d"));
}

void IdBurnerMain::UsingSystemDate( wxCommandEvent& event )
{
    if(event.IsChecked()) {
        dateID->SetLabel(wxDateTime::Today().Format("%y%m%d"));
        pickDate->Enable(false);
    } else {
        dateID->SetLabel(pickDate->GetValue().Format("%y%m%d"));
        pickDate->Enable(true);
    }
}

void IdBurnerMain::OnManualCode( wxCommandEvent& event )
{
    bool state = event.IsChecked();
    manual = state;
    typeID->Enable(state);
    dateID->Enable(state);
    deviceID->Enable(state);
    if(!state) {
        if(!checkDate->IsChecked())
            dateID->SetLabel(pickDate->GetValue().Format("%y%m%d"));
        else
            dateID->SetLabel(wxDateTime::Today().Format("%y%m%d"));

        UpdateID(ChoiceDeviceType->GetString(ChoiceDeviceType->GetCurrentSelection()).ToStdString());
    }
}

void IdBurnerMain::OnBurn( wxCommandEvent& event )
{
    std::string name, type, date, counter, id;
    name = ChoiceDeviceType->GetString(ChoiceDeviceType->GetCurrentSelection()).ToStdString();

    if(name != "Device Type" || manual) {
        type = typeID->GetLineText(0);
        date = dateID->GetLineText(0);
        counter = deviceID->GetLineText(0);
        id=type+date+counter;

        std::string selection_name = IdChoice->GetString(IdChoice->GetCurrentSelection()).ToStdString();
        if(selection_name == "Default ID")
            selection_name = "";
        DigiProtocol digiDevice(selection_name);

        if(digiDevice.isOpen()) {

            std::string temp = "";

            digiDevice.sendRequest(DP_BURN_ID);
            digiDevice.sendMessage(id);

            wxGenericProgressDialog* dialog = new wxGenericProgressDialog(_("Please wait..."), _("Burning in progress..."), 440, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxCENTRE);

            for(int i = 0; i < 440; i++){
                wxMilliSleep(5); // PC program has to be in idle, because burning has place on AVR side
                if(!dialog->Update(i))
                    dialog->Resume();
            }
            dialog->Update(440);
            delete dialog;

            digiDevice.readMessage(temp);
            if(temp == id) {
                wxMessageBox(_("Burning successful"), _(""));
                if(!manual) {
                    counter = wrapID(counter);                      // wrap counter only when successful burning
                    configuration.editRecord(type, "counter", counter);
                }
                deviceID->SetLabel(counter);
            }
            else
                wxMessageBox(_("Please reconnect device and try again"), _("Error while burning"), wxICON_ERROR | wxCENTRE);

            digiDevice.close();
            RefreshDeviceList(id);
        } else
            wxMessageBox(_("Could not connect device!"), _(""));
    } else
        wxMessageBox(_("Choose Device Type before burning ID!"), _(""));
}


void IdBurnerMain::ReloadConfig(std::string selection) {

    std::map<std::string, std::map<std::string, std::string>> config = configuration.dumpConfiguration();
    std::string temp_name = "";

    ChoiceDeviceType->SetColumns(config.size() + 1);
    ChoiceDeviceType->Clear();
    ChoiceDeviceType->Append("Device Type");

    for(auto const &element1 : config) {
            ChoiceDeviceType->Append(config[element1.first]["name"]);
    }
    if(selection=="")
        ChoiceDeviceType->SetSelection(0);
    else {
        ChoiceDeviceType->Delete(0);
        ChoiceDeviceType->SetSelection(ChoiceDeviceType->FindString(selection));
    }
}

void IdBurnerMain::RefreshDeviceList(std::string selection) {

    DigiProtocol digiDevice;
    IDlist.clear();
    digiDevice.listDevices(IDlist);

    IdChoice->SetColumns(IDlist.size() + 1);
    IdChoice->Clear();
    IdChoice->Append("Default ID");
    for(int i=0; i<(int)IDlist.size(); i++) {
        IdChoice->Append(IDlist[i]);
    }
    if(selection == "" || !IdChoice->SetStringSelection(selection))
        IdChoice->SetSelection(0);
}

void IdBurnerMain::UpdateID(std::string selection) {
        std::string section = configuration.getSectionByValue("name", selection);
        typeID->SetLabel(section);
        if(configuration.getRecord(section, "counter") == "")
            configuration.editRecord(section, "counter", "aa");
        deviceID->SetLabel(configuration.getRecord(section, "counter"));
}

std::string IdBurnerMain::wrapID(std::string counter) {
    bool carry = false;
    counter[1]++;
    if(counter[1] > 122) { // reached end of lower
        counter[1] = 65; // wrap to 'A' letter
    } else if(counter[1] > 90 && counter[1] < 97) { // reached end of upper
        counter[1] = 48; // wrap to '0'
    } else if(counter[1] > 57 && counter[1] < 65) { // reached end of numerics
        counter[1] = 97; // wrap again to 'a'
        carry = true;   // and set carry flag
    }

    if(carry) {
        counter[0]++;
        if(counter[0] > 122) { // reached end of lower
            counter[0] = 65; // wrap to 'A' letter
        } else if(counter[0] > 90 && counter[0] < 97) { // reached end of upper
            counter[0] = 48; // wrap to '0'
        } else if(counter[0] > 57 && counter[0] < 65) { // reached end of numerics
            counter[0] = 97; // wrap again to 'a'
        }
    }

    return counter;
}
