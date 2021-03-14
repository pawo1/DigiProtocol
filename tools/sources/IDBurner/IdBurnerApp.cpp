#ifdef WX_PRECOMP
#include "wx_pch.h"
#endif

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__


#include "IdBurnerApp.h"
#include "IdBurnerMain.h"

IMPLEMENT_APP(IdBurnerApp);

bool IdBurnerApp::OnInit()
{
    IdBurnerMain* frame = new IdBurnerMain(0L);

#ifdef _WIN32
	frame->SetIcon(wxICON(aaaa)); // To Set App Icon
#endif

    frame->Show();

    return true;
}
