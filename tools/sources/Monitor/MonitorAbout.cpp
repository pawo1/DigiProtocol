#include "MonitorAbout.h"

#include "MonitorGUIApp.h"

MonitorAbout::MonitorAbout( wxWindow* parent )
:
AboutDialog( parent )
{

}

void MonitorAbout::OnClick( wxCommandEvent& event )
{
   EndModal(0);
}


