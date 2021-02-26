

#ifndef MONITORGUIMAIN_H
#define MONITORGUIMAIN_H



#include "MonitorGUIApp.h"
#include "GUIFrame.h"



class MonitorGUIFrame: public GUIFrame
{
    public:
        MonitorGUIFrame(wxFrame *frame);
        ~MonitorGUIFrame();
    private:
        wxString sampleText;
        virtual void OnClose(wxCloseEvent& event);
        virtual void OnQuit(wxCommandEvent& event);
        virtual void OnAbout(wxCommandEvent& event);
        virtual void OnConnect(wxCommandEvent& event);
        virtual void OnClear(wxCommandEvent& event);
        virtual void OnLineEnding(wxCommandEvent& event);
        virtual void UpdateShowRule(wxCommandEvent& event);
        virtual void SendMessageFromGUI(wxCommandEvent& event);
        virtual void OnRefresh(wxCommandEvent& event);
        void OnResponse(wxCommandEvent& event);
        void IncomingData(wxCommandEvent& event);
        void ConnectDevice();
        void DisconnectDevice();
        void RefreshDeviceList();


        bool connected;
        bool showRule, file_showRule;
        int lineEndingStatus, file_lineEndingStatus;
        std::vector<std::string> IDlist;
        ListenerThread* m_ListenerThread;
        wxMessageQueue<wxString> m_queue;

        DECLARE_EVENT_TABLE()
};

#endif // MONITORGUIMAIN_H
