#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MonitorGUIMain.h"
#include "ListenerThread.h"


BEGIN_EVENT_TABLE(MonitorGUIFrame, wxFrame)
    EVT_COMMAND(wxID_ANY, wxEVT_DEVICE_MESSAGE, MonitorGUIFrame::IncomingData)
END_EVENT_TABLE()


MonitorGUIFrame::MonitorGUIFrame(wxFrame *frame)
    : GUIFrame(frame)
{

    connected = false;

    ConfigReader monitorConfiguration("user_preferences");

    if(!fileExists("user_preferences")) {
        std::map<std::string, std::string> config;
        config["show"] = true;
        config["lineEnding"] = "LF";
        monitorConfiguration.createConfig(config);
    }

    std::string temp = monitorConfiguration.getRecord("show");
    if(temp == "false") file_showRule = false;
    else file_showRule = true;  // default values can be used without user_preferences exists e.g. no permissions

    temp = monitorConfiguration.getRecord("lineEnding");
    if(temp == "NLE") file_lineEndingStatus = 1003;
    else if(temp == "CR") file_lineEndingStatus = 1005;
    else if(temp == "LFCR") file_lineEndingStatus = 1006;
    else file_lineEndingStatus = 1004; // '\n' as default


    showRule = file_showRule;
    lineEndingStatus = file_lineEndingStatus;

    for(int x=1003; x<=1006; x++) {
        wxMenuItem *radio = lineEnding->FindItem(x);
        if(x == lineEndingStatus) {
            radio->Check(true);
        } else
            radio->Check(false);
    }
    wxMenuItem *check = menuSettings->FindItem(idShowMessages);
    check->Check(showRule);


    RefreshDeviceList();
}

MonitorGUIFrame::~MonitorGUIFrame()
{
    if(showRule != file_showRule || lineEndingStatus != file_lineEndingStatus) {
        ConfigReader monitorConfiguration("user_preferences");
        if(showRule != file_showRule) {
            if(showRule) monitorConfiguration.editRecord("show", "true");
            else monitorConfiguration.editRecord("show", "false");
        }
        if(lineEndingStatus != file_lineEndingStatus) {
            switch(lineEndingStatus) {
            case 1003:
                monitorConfiguration.editRecord("lineEnding", "NLE");
                break;
            case 1004:
                monitorConfiguration.editRecord("lineEnding", "LF");
                break;
            case 1005:
                monitorConfiguration.editRecord("lineEnding", "CR");
                break;
            case 1006:
                monitorConfiguration.editRecord("lineEnding", "LFCR");
                break;

            }
        }
    }

    m_ListenerThread = nullptr;
}




void MonitorGUIFrame::OnClose(wxCloseEvent &event)
{
    DisconnectDevice();
    Destroy();
}

void MonitorGUIFrame::OnQuit(wxCommandEvent &event)
{
    DisconnectDevice();
    Destroy();
}

void MonitorGUIFrame::OnAbout(wxCommandEvent &event)
{
    MonitorAbout about(this);
    about.ShowModal();
}

void MonitorGUIFrame::OnConnect(wxCommandEvent &event) {
    if(!connected) ConnectDevice();
    else DisconnectDevice();
}

void MonitorGUIFrame::OnClear(wxCommandEvent &event) {
    reciveCtrl->Clear();
}

void MonitorGUIFrame::OnLineEnding(wxCommandEvent &event) {

    for(int x=1003; x<=1006; x++) {
        wxMenuItem *radio = lineEnding->FindItem(x);
        if(x == event.GetId()) {
            radio->Check(true);
            lineEndingStatus = x;
        } else
            radio->Check(false);
    }
}

void MonitorGUIFrame::UpdateShowRule(wxCommandEvent& event) {
    showRule = event.IsChecked();
}

void MonitorGUIFrame::SendMessageFromGUI(wxCommandEvent &event) {
    wxString message = sendCtrl->GetLineText(0);
    sendCtrl->Clear();
    if(connected) {
        switch(lineEndingStatus) {
            case idLF: message+="\n"; break;
            case idCR: message+="\r"; break;
            case idLFCR: message+="\r\n"; break;
            default: break;
        }

        if(showRule) {
            if(lineEndingStatus == idNLE)
                reciveCtrl->AppendText("\n");

            reciveCtrl->AppendText("Sent: "+message);

            if(lineEndingStatus == idNLE)
                reciveCtrl->AppendText("\n");
        }

        m_queue.Post(message);
    } else {
         wxMessageBox(_("You have to connect device before sending message"), _(""));
    }

}

void MonitorGUIFrame::OnRefresh(wxCommandEvent &event) {
    RefreshDeviceList();
}


void MonitorGUIFrame::IncomingData(wxCommandEvent &event) {
    int status = event.GetInt();
    if(status == -1) {                          // couldn't find the device
        wxMessageBox(_("Couldn't find device"), _(""));
        DisconnectDevice();
        m_queue.Clear(); // clear EOT message to prevent reading that by new thread
    } else if(status > 0) {
        statusText->SetLabel(_("No response..."));
        statusText->SetForegroundColour(wxColor(0x20A5DA));
        // TODO inform if no response is too long

    } else {
        if(connected) {
            statusText->SetLabel(_("Connected"));
            statusText->SetForegroundColour(wxColor(0x006400));
        }
        wxString *temp = (wxString*)event.GetClientData();
        if(temp != nullptr) {//wxMessageBox(_("No data"))
            reciveCtrl->AppendText(*temp);
            delete temp;
        }
    }
}

void MonitorGUIFrame::ConnectDevice() {
    int choice = IdChoice->GetSelection();
    std::string ID;
    if(choice == 0) ID="";
    else ID=IDlist[choice-1];


    m_ListenerThread = new ListenerThread(this, m_queue, ID);
    wxThreadError err = m_ListenerThread->Create();
    if (err != wxTHREAD_NO_ERROR) { wxMessageBox(_("Couldn't create thread!")); return;}
    err = m_ListenerThread->Run();
    if (err != wxTHREAD_NO_ERROR) { wxMessageBox(_("Couldn't run thread!")); return; }
    connected = true;
    connectButton->SetLabel(_("Disconnect"));
}

void MonitorGUIFrame::DisconnectDevice() {
    m_queue.Post((char)4); // END OF TRANSMISION - signal to close connection with USB Device, and destroy thread
    m_ListenerThread = nullptr;
    connected = false;
    connectButton->SetLabel(_("Connect"));
    statusText->SetLabel(_("Disconnected"));
    statusText->SetForegroundColour(wxColor(*wxRED));
}

void MonitorGUIFrame::RefreshDeviceList() {
    if(connected) {
        wxMessageBox(_("Can't refresh device list during connection!"));
        return;
    }
    DigiProtocol digiDevice;
    IDlist.clear();
    digiDevice.listDevices(IDlist);

    IdChoice->SetColumns(IDlist.size() + 1);
    IdChoice->Clear();
    IdChoice->Append("Default ID");
    for(int i=0; i<(int)IDlist.size(); i++) {
        IdChoice->Append(IDlist[i]);
    }
    IdChoice->SetSelection(0);
}

