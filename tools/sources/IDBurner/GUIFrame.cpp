///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif //__BORLANDC__

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif //WX_PRECOMP

#include "GUIFrame.h"

///////////////////////////////////////////////////////////////////////////

GUIFrame::GUIFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	mbar = new wxMenuBar( 0 );
	fileMenu1 = new wxMenu();
	wxMenuItem* menuFileRefresh;
	menuFileRefresh = new wxMenuItem( fileMenu1, idRefreshMenu, wxString( _("Refresh Device List") ) + wxT('\t') + wxT("F5"), _("Refresh List with Devices"), wxITEM_NORMAL );
	fileMenu1->Append( menuFileRefresh );

	wxMenuItem* menuReloadConfig;
	menuReloadConfig = new wxMenuItem( fileMenu1, idReloadConfig, wxString( _("Reload Config File") ) + wxT('\t') + wxT("F6"), wxEmptyString, wxITEM_NORMAL );
	fileMenu1->Append( menuReloadConfig );

	wxMenuItem* menuFileQuit1;
	menuFileQuit1 = new wxMenuItem( fileMenu1, idMenuQuit, wxString( _("&Quit") ) + wxT('\t') + wxT("Alt+F4"), _("Quit the application"), wxITEM_NORMAL );
	fileMenu1->Append( menuFileQuit1 );

	mbar->Append( fileMenu1, _("&File") );

	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( _("&About") ) + wxT('\t') + wxT("F1"), _("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );

	mbar->Append( helpMenu, _("&Help") );

	this->SetMenuBar( mbar );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer18;
	bSizer18 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( this, wxID_ANY, _("Choose device:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizer3->Add( m_staticText1, 0, wxTOP|wxRIGHT|wxLEFT|wxALIGN_CENTER_VERTICAL, 5 );

	wxString IdChoiceChoices[] = { _("Default ID") };
	int IdChoiceNChoices = sizeof( IdChoiceChoices ) / sizeof( wxString );
	IdChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, IdChoiceNChoices, IdChoiceChoices, 0 );
	IdChoice->SetSelection( 0 );
	bSizer3->Add( IdChoice, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer18->Add( bSizer3, 0, wxEXPAND, 5 );

	m_staticline1 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer18->Add( m_staticline1, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxString ChoiceDeviceTypeChoices[] = { _("Device Type") };
	int ChoiceDeviceTypeNChoices = sizeof( ChoiceDeviceTypeChoices ) / sizeof( wxString );
	ChoiceDeviceType = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, ChoiceDeviceTypeNChoices, ChoiceDeviceTypeChoices, 0 );
	ChoiceDeviceType->SetSelection( 0 );
	bSizer2->Add( ChoiceDeviceType, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	addButton = new wxButton( this, wxID_ANY, _("add"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer2->Add( addButton, 0, wxALL, 5 );

	editButton = new wxButton( this, wxID_ANY, _("edit"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer2->Add( editButton, 0, wxALL, 5 );

	deleteButton = new wxButton( this, wxID_ANY, _("delete"), wxDefaultPosition, wxDefaultSize, wxBU_EXACTFIT );
	bSizer2->Add( deleteButton, 0, wxALL, 5 );


	bSizer18->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Date: "), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer4->Add( m_staticText3, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	pickDate = new wxDatePickerCtrl( this, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT|wxDP_DROPDOWN );
	pickDate->Enable( false );

	bSizer4->Add( pickDate, 0, wxALL, 5 );

	checkDate = new wxCheckBox( this, wxID_ANY, _("Use system date"), wxDefaultPosition, wxDefaultSize, 0 );
	checkDate->SetValue(true);
	bSizer4->Add( checkDate, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer18->Add( bSizer4, 0, wxEXPAND, 5 );

	m_staticline2 = new wxStaticLine( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLI_HORIZONTAL );
	bSizer18->Add( m_staticline2, 0, wxEXPAND | wxALL, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxHORIZONTAL );

	typeID = new wxTextCtrl( this, wxID_ANY, _("AA"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !typeID->HasFlag( wxTE_MULTILINE ) )
	{
	typeID->SetMaxLength( 2 );
	}
	#else
	typeID->SetMaxLength( 2 );
	#endif
	typeID->Enable( false );

	bSizer5->Add( typeID, 0, wxALL, 5 );

	dateID = new wxTextCtrl( this, wxID_ANY, _("000000"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !dateID->HasFlag( wxTE_MULTILINE ) )
	{
	dateID->SetMaxLength( 6 );
	}
	#else
	dateID->SetMaxLength( 6 );
	#endif
	dateID->Enable( false );

	bSizer5->Add( dateID, 0, wxALL, 5 );

	deviceID = new wxTextCtrl( this, wxID_ANY, _("aa"), wxDefaultPosition, wxDefaultSize, wxTE_CENTER );
	#ifdef __WXGTK__
	if ( !deviceID->HasFlag( wxTE_MULTILINE ) )
	{
	deviceID->SetMaxLength( 2 );
	}
	#else
	deviceID->SetMaxLength( 2 );
	#endif
	deviceID->Enable( false );

	bSizer5->Add( deviceID, 0, wxALL, 5 );


	bSizer18->Add( bSizer5, 1, wxALIGN_CENTER, 5 );

	checkManualID = new wxCheckBox( this, wxID_ANY, _("Enter the code manually"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer18->Add( checkManualID, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer1->Add( bSizer18, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	burnButton = new wxButton( this, wxID_ANY, _("BURN ID"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer6->Add( burnButton, 1, wxALIGN_BOTTOM|wxBOTTOM, 5 );


	bSizer1->Add( bSizer6, 2, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	statusBar = this->CreateStatusBar( 2, wxSTB_SIZEGRIP, wxID_ANY );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	fileMenu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRefresh ), this, menuFileRefresh->GetId());
	fileMenu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnReload ), this, menuReloadConfig->GetId());
	fileMenu1->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, menuFileQuit1->GetId());
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ), this, menuHelpAbout->GetId());
	ChoiceDeviceType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::OnTypeChoice ), NULL, this );
	addButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnAdd ), NULL, this );
	editButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnEdit ), NULL, this );
	deleteButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnDelete ), NULL, this );
	pickDate->Connect( wxEVT_DATE_CHANGED, wxDateEventHandler( GUIFrame::OnDateUpdate ), NULL, this );
	checkDate->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrame::UsingSystemDate ), NULL, this );
	checkManualID->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrame::OnManualCode ), NULL, this );
	burnButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBurn ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	ChoiceDeviceType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( GUIFrame::OnTypeChoice ), NULL, this );
	addButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnAdd ), NULL, this );
	editButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnEdit ), NULL, this );
	deleteButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnDelete ), NULL, this );
	pickDate->Disconnect( wxEVT_DATE_CHANGED, wxDateEventHandler( GUIFrame::OnDateUpdate ), NULL, this );
	checkDate->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrame::UsingSystemDate ), NULL, this );
	checkManualID->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( GUIFrame::OnManualCode ), NULL, this );
	burnButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnBurn ), NULL, this );

}

EditDialog::EditDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* sbSizer4;
	sbSizer4 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Device Type Name") ), wxVERTICAL );

	ctrlDeviceType = new wxTextCtrl( sbSizer4->GetStaticBox(), wxID_ANY, _("Device Type name"), wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer4->Add( ctrlDeviceType, 0, wxALL|wxEXPAND, 5 );


	bSizer7->Add( sbSizer4, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer8;
	bSizer8 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_staticText3 = new wxStaticText( this, wxID_ANY, _("Short type code:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	bSizer9->Add( m_staticText3, 0, wxALL, 5 );


	bSizer8->Add( bSizer9, 1, wxEXPAND, 5 );

	ctrlShortCode = new wxTextCtrl( this, wxID_ANY, _("AA"), wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !ctrlShortCode->HasFlag( wxTE_MULTILINE ) )
	{
	ctrlShortCode->SetMaxLength( 2 );
	}
	#else
	ctrlShortCode->SetMaxLength( 2 );
	#endif
	bSizer8->Add( ctrlShortCode, 0, wxALL, 5 );


	bSizer7->Add( bSizer8, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer16;
	bSizer16 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	setCounter = new wxCheckBox( this, wxID_ANY, _("Set counter value"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer17->Add( setCounter, 0, wxALL, 5 );


	bSizer16->Add( bSizer17, 1, wxEXPAND, 5 );

	ctrlCounterValue = new wxTextCtrl( this, wxID_ANY, _("aa"), wxDefaultPosition, wxDefaultSize, 0 );
	#ifdef __WXGTK__
	if ( !ctrlCounterValue->HasFlag( wxTE_MULTILINE ) )
	{
	ctrlCounterValue->SetMaxLength( 2 );
	}
	#else
	ctrlCounterValue->SetMaxLength( 2 );
	#endif
	ctrlCounterValue->Enable( false );

	bSizer16->Add( ctrlCounterValue, 0, wxALL, 5 );


	bSizer7->Add( bSizer16, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxHORIZONTAL );

	saveButton = new wxButton( this, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0 );

	saveButton->SetBitmapPosition( wxBOTTOM );
	bSizer10->Add( saveButton, 0, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5 );

	cancelButton = new wxButton( this, wxID_ANY, _("Cancel"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer10->Add( cancelButton, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	bSizer7->Add( bSizer10, 1, wxALIGN_CENTER_HORIZONTAL, 5 );


	this->SetSizer( bSizer7 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	setCounter->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EditDialog::checkCounter ), NULL, this );
	saveButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditDialog::onSave ), NULL, this );
	cancelButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditDialog::onCancel ), NULL, this );
}

EditDialog::~EditDialog()
{
	// Disconnect Events
	setCounter->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( EditDialog::checkCounter ), NULL, this );
	saveButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditDialog::onSave ), NULL, this );
	cancelButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( EditDialog::onCancel ), NULL, this );

}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_staticText5 = new wxStaticText( this, wxID_ANY, _("DigiProtocol ID Burner v1.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_staticText5, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText8 = new wxStaticText( this, wxID_ANY, _("GUI tool to generate ID for your device easily"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText8->Wrap( -1 );
	bSizer5->Add( m_staticText8, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxHORIZONTAL );

	m_staticText9 = new wxStaticText( this, wxID_ANY, _("2020 by Pawo"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	bSizer6->Add( m_staticText9, 1, wxALL|wxEXPAND|wxALIGN_CENTER_VERTICAL, 5 );

	author_site = new wxHyperlinkCtrl( this, wxID_ANY, _("https://www.pandretix.pl"), wxT("https://www.pandretix.pl"), wxDefaultPosition, wxDefaultSize, wxHL_DEFAULT_STYLE );
	bSizer6->Add( author_site, 0, wxALL, 5 );


	bSizer5->Add( bSizer6, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	project_site = new wxHyperlinkCtrl( this, wxID_ANY, _("Check Project on Github"), wxT("http://www.wxformbuilder.org"), wxDefaultPosition, wxDefaultSize, wxHL_ALIGN_CENTRE|wxHL_DEFAULT_STYLE );
	bSizer9->Add( project_site, 0, wxALL|wxALIGN_CENTER_HORIZONTAL, 5 );


	bSizer5->Add( bSizer9, 0, wxEXPAND, 5 );

	okButton = new wxButton( this, wxID_ANY, _("OK"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer5->Add( okButton, 0, wxALIGN_CENTER|wxALL, 5 );


	bSizer4->Add( bSizer5, 1, wxEXPAND, 5 );


	this->SetSizer( bSizer4 );
	this->Layout();

	this->Centre( wxBOTH );

	// Connect Events
	okButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::OnClick ), NULL, this );
}

AboutDialog::~AboutDialog()
{
	// Disconnect Events
	okButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AboutDialog::OnClick ), NULL, this );

}
