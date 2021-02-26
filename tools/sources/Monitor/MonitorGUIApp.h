/***************************************************************
 * Name:      MonitorGUIApp.h
 * Purpose:   Defines Application Class
 * Author:    Pawo (pawo@pandretix.pl)
 * Created:   2020-09-10
 * Copyright: Pawo (pandretix.pl)
 * License:
 **************************************************************/

#ifndef MONITORGUIAPP_H
#define MONITORGUIAPP_H

#include <wx/app.h>
#include <wx/msgdlg.h>
#include <wx/msgqueue.h>

#include <vector>
#include <string>
#include <DigiProtocol.h>

#include "ListenerThread.h"
#include "ConfigReader.h"
#include "MonitorAbout.h"

class MonitorGUIApp : public wxApp
{
    private:

    public:
        virtual bool OnInit();
        virtual int OnExit();



};

#endif // MONITORGUIAPP_H
