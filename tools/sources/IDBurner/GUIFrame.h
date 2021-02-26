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
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/sizer.h>
#include <wx/statline.h>
#include <wx/button.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/statbox.h>
#include <wx/dialog.h>
#include <wx/hyperlink.h>

///////////////////////////////////////////////////////////////////////////

#define idRefreshMenu 1000
#define idReloadConfig 1001
#define idMenuQuit 1002
#define idMenuAbout 1003

///////////////////////////////////////////////////////////////////////////////
/// Class GUIFrame
///////////////////////////////////////////////////////////////////////////////
class GUIFrame : public wxFrame
{
	private:

	protected:
		wxMenuBar* mbar;
		wxMenu* fileMenu1;
		wxMenu* helpMenu;
		wxStaticText* m_staticText1;
		wxChoice* IdChoice;
		wxStaticLine* m_staticline1;
		wxChoice* ChoiceDeviceType;
		wxButton* addButton;
		wxButton* editButton;
		wxButton* deleteButton;
		wxStaticText* m_staticText3;
		wxDatePickerCtrl* pickDate;
		wxCheckBox* checkDate;
		wxStaticLine* m_staticline2;
		wxTextCtrl* typeID;
		wxTextCtrl* dateID;
		wxTextCtrl* deviceID;
		wxCheckBox* checkManualID;
		wxButton* burnButton;
		wxStatusBar* statusBar;

		// Virtual event handlers, overide them in your derived class
		virtual void OnClose( wxCloseEvent& event ) { event.Skip(); }
		virtual void OnRefresh( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnReload( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnQuit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAbout( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTypeChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnAdd( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDateUpdate( wxDateEvent& event ) { event.Skip(); }
		virtual void UsingSystemDate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnManualCode( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnBurn( wxCommandEvent& event ) { event.Skip(); }


	public:

		GUIFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("DigiProtocol ID Burner"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 481,388 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~GUIFrame();

};

///////////////////////////////////////////////////////////////////////////////
/// Class EditDialog
///////////////////////////////////////////////////////////////////////////////
class EditDialog : public wxDialog
{
	private:

	protected:
		wxTextCtrl* ctrlDeviceType;
		wxStaticText* m_staticText3;
		wxTextCtrl* ctrlShortCode;
		wxCheckBox* setCounter;
		wxTextCtrl* ctrlCounterValue;
		wxButton* saveButton;
		wxButton* cancelButton;

		// Virtual event handlers, overide them in your derived class
		virtual void checkCounter( wxCommandEvent& event ) { event.Skip(); }
		virtual void onSave( wxCommandEvent& event ) { event.Skip(); }
		virtual void onCancel( wxCommandEvent& event ) { event.Skip(); }


	public:

		EditDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Add/Edit Device Type"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 280,229 ), long style = wxDEFAULT_DIALOG_STYLE );
		~EditDialog();

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

