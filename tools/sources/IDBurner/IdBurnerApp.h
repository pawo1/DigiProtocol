#ifndef IDBURNERAPP_H
#define IDBURNERAPP_H

#include <wx/valtext.h>
#include <wx/datetime.h>
#include <wx/msgdlg.h>
#include <wx/app.h>
#include <wx/progdlg.h>

#include "ConfigReader.h"


class IdBurnerApp : public wxApp
{
    public:
        virtual bool OnInit();
};

#endif // IDBURNERAPP_H
