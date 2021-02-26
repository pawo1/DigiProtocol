#include "IdBurnerAddDialog.h"

IdBurnerAddDialog::IdBurnerAddDialog( wxWindow* parent, std::string file_path, std::string &name_device )
:
EditDialog( parent ), configuration(file_path), idValidator( wxFILTER_ALPHANUMERIC), new_name(name_device)
{
    this->SetLabel("Add new Device Type");

    ctrlCounterValue->SetValidator(idValidator);
    ctrlShortCode->SetValidator(idValidator);
}

void IdBurnerAddDialog::checkCounter( wxCommandEvent& event ) {
    if(event.IsChecked()) {

        wxMessageDialog dlg(NULL, _("duplicating IDs may result in incorrect operation of devices.\nIt is recommended that you edit this field only to recovery the record"), _("Warning"), wxOK | wxCANCEL | wxCANCEL_DEFAULT | wxCENTRE);
        dlg.SetOKCancelLabels(_("OK"), _("Cancel"));

        int answer = dlg.ShowModal();
        if(answer == wxID_OK) {
            ctrlCounterValue->Enable(true);
        } else
            setCounter->SetValue(false);
   } else {
        ctrlCounterValue->Enable(false);
   }
}

void IdBurnerAddDialog::onSave( wxCommandEvent& event )
{
    std::string name = ctrlDeviceType->GetLineText(0).ToStdString();
    std::string shortCode = ctrlShortCode->GetLineText(0).ToStdString();
    std::string counter = ctrlCounterValue->GetLineText(0).ToStdString();

    if( shortCode.length() < 2 || counter.length() < 2) {
        wxMessageBox(_("Short code and counter must be 2 bytes long!"), _(""));
        return;
    }

    if( name == "Device Type name") {
        wxMessageBox(_("Set Device Type name"), _(""));
        return;
    }
    if(configuration.existsValue("name", name)) {
        wxMessageBox(_("Device Type name must be unique!"), _(""));
        return;
    }
    if(configuration.existSection(shortCode)) {
        wxMessageBox(_("Short code must be unique!"), _(""));
        return;
    }

    configuration.addRecord(shortCode, "name", name);
    configuration.addRecord(shortCode, "counter", counter);
    new_name = name;
    EndModal(1);
}

void IdBurnerAddDialog::onCancel( wxCommandEvent& event )
{
    EndModal(0);
}
