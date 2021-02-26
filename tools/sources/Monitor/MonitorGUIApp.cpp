#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#include "MonitorGUIApp.h"
#include "MonitorGUIMain.h"
#include "ListenerThread.h"


IMPLEMENT_APP(MonitorGUIApp);

bool MonitorGUIApp::OnInit()
{
    MonitorGUIFrame* frame = new MonitorGUIFrame(0L);
    frame->SetIcon(wxICON(aaaa)); // To Set App Icon
    frame->Show();


    return true;
}

int MonitorGUIApp::OnExit()
{
    return 0;
}
