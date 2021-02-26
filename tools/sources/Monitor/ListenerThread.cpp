#include "ListenerThread.h"



DEFINE_EVENT_TYPE(wxEVT_DEVICE_MESSAGE)

wxThread::ExitCode ListenerThread::Entry()
{

    DigiProtocol myDevice(deviceID);

    if(!myDevice.isOpen()) {
        wxCommandEvent evt(wxEVT_DEVICE_MESSAGE, wxID_ANY);
        evt.SetInt(-1);
        m_parent->AddPendingEvent(evt);
        return ExitCode(nullptr);
    }

    no_response = 2;

    while(!TestDestroy()) {
        wxString parentMessage="";
        std::string deviceMessage="";
        wxCommandEvent evt(wxEVT_DEVICE_MESSAGE, wxID_ANY);


        m_queue.ReceiveTimeout(0, parentMessage);  // reading message from Main thread (GUI)

        if(parentMessage == (char)4) {
            myDevice.close();
            break;
        } else if(parentMessage != "") {
            myDevice.sendMessage(parentMessage.ToStdString());
        }

        int err = myDevice.readMessage(deviceMessage); // reading message from USB Device

        if(err == DP_ERROR_NO_RESPONSE) {
            no_response++;
            evt.SetInt(no_response);
        } else {

            switch(err) {
            case DP_ERROR_TIMEOUT:
                deviceMessage = "Incoming data with error: DP_ERROR_TIMEOUT";
                break;
            case DP_ERROR_WRONG_SIZE:
                deviceMessage = "Incoming data with error: DP_ERROR_WRONG_SIZE";
                break;
            case DP_ERROR_CORRUPTED_DATA:
                deviceMessage = "Incoming data with error: DP_ERROR_CORRUPTED_DATA";
                break;
            default:
                break;
            }

            if(deviceMessage.length() > 0) {
                wxString *message = new wxString(deviceMessage);
                evt.SetClientData((void*)message);
            }
            if(no_response > 1)
                no_response = 1;
            else no_response = 0;
            evt.SetInt(0);
        }
        if(deviceMessage.length() > 0 || no_response%10 == 1 ) {
            m_parent->AddPendingEvent(evt);
        }
    }

	return ExitCode(nullptr);
}
