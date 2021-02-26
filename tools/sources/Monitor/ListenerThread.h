#ifndef LISTENERTHREAD_H
#define LISTENERTHREAD_H

#include "MonitorGUIApp.h"


#include <DigiProtocol.h>
#include <wx/thread.h>
#include <wx/msgqueue.h>

// how to declare a custom event. this can go in a header
DECLARE_EVENT_TYPE(wxEVT_DEVICE_MESSAGE, -1)

// a thread class that will periodically send events to the GUI thread
class ListenerThread : public wxThread
{
protected:
    int no_response;
	wxEvtHandler* m_parent;
	wxMessageQueue<wxString>& m_queue;
	std::string deviceID;


public:
	explicit ListenerThread(wxEvtHandler* parent, wxMessageQueue<wxString>& q, std::string ID) : wxThread(), m_parent(parent),  m_queue(q) { deviceID = ID; no_response=1; }

	ExitCode Entry() override;
};

#endif // LISTENERTHREAD_H
