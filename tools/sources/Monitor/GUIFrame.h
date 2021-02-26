///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/choice.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/hyperlink.h>
#include <wx/dialog.h>

///////////////////////////////////////////////////////////////////////////

#define idRefreshMenu 1000
#define idMenuQuit 1001
#define idShowMessages 1002
#define idNLE 1003
#define idLF 1004
#define idCR 1005
#define idLFCR 1006
#define idMenuAbout 1007

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu;
		wxMenu* menuSettings;
		wxMenu* lineEnding;
		wxMenu* helpMenu;
		wxChoice* IdChoice;
		wxButton* connectButton;
		wxStaticText* staticText1;
		wxStaticText* statusText;
		wxStaticText* staticText2;
		wxTextCtrl* sendCtrl;
		wxStaticText* staticText3;
		wxTextCtrl* reciveCtrl;
		wxButton* clearButton;
		wxStatusBar* m_statusBar2;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void UpdateShowRule( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnLineEnding( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnConnect( wxCommandEvent& event ) { event.Skip(); }
		virtual void SendMessageFromGUI( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClear( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("DigiProtocol Monitor"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 481,551 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class AboutDialog
///////////////////////////////////////////////////////////////////////////////
class AboutDialog : public wxDialog
{
	private:

	protected:
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText8;
		wxStaticText* m_staticText9;
		wxHyperlinkCtrl* author_site;
		wxHyperlinkCtrl* project_site;
		wxButton* okButton;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClick( wxCommandEvent& event ) { event.Skip(); }


	public:

		AboutDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("About..."), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 319,207 ), long style = wxDEFAULT_DIALOG_STYLE );
		~AboutDialog();

};

