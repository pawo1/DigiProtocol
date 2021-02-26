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
	fileMenu = new wxMenu();
	wxMenuItem* menuFileRefresh;
	menuFileRefresh = new wxMenuItem( fileMenu, idRefreshMenu, wxString( _("Refresh Device List") ) + wxT('\t') + wxT("F5"), _("Refresh List with Devices"), wxITEM_NORMAL );
	fileMenu->Append( menuFileRefresh );

	wxMenuItem* menuFileQuit;
	menuFileQuit = new wxMenuItem( fileMenu, idMenuQuit, wxString( _("&Quit") ) + wxT('\t') + wxT("Alt+F4"), _("Quit the application"), wxITEM_NORMAL );
	fileMenu->Append( menuFileQuit );

	mbar->Append( fileMenu, _("&File") );

	menuSettings = new wxMenu();
	wxMenuItem* showMessages;
	showMessages = new wxMenuItem( menuSettings, idShowMessages, wxString( _("Show sent messages") ) , _("Show/Hide sent messages "), wxITEM_CHECK );
	menuSettings->Append( showMessages );
	showMessages->Check( true );

	lineEnding = new wxMenu();
	wxMenuItem* lineEndingItem = new wxMenuItem( menuSettings, wxID_ANY, _("Line ending"), wxEmptyString, wxITEM_NORMAL, lineEnding );
	wxMenuItem* NLE;
	NLE = new wxMenuItem( lineEnding, idNLE, wxString( _("No line ending") ) , _("Choose line ending"), wxITEM_RADIO );
	lineEnding->Append( NLE );

	wxMenuItem* LF;
	LF = new wxMenuItem( lineEnding, idLF, wxString( _("Line feed \\n") ) , _("Choose line ending"), wxITEM_RADIO );
	lineEnding->Append( LF );
	LF->Check( true );

	wxMenuItem* CR;
	CR = new wxMenuItem( lineEnding, idCR, wxString( _("Carriage return \\r") ) , _("Choose line ending"), wxITEM_RADIO );
	lineEnding->Append( CR );

	wxMenuItem* LFCR;
	LFCR = new wxMenuItem( lineEnding, idLFCR, wxString( _("LF and CR \\r\\n") ) , _("Choose line ending"), wxITEM_RADIO );
	lineEnding->Append( LFCR );

	menuSettings->Append( lineEndingItem );

	mbar->Append( menuSettings, _("Settings") );

	helpMenu = new wxMenu();
	wxMenuItem* menuHelpAbout;
	menuHelpAbout = new wxMenuItem( helpMenu, idMenuAbout, wxString( _("&About") ) + wxT('\t') + wxT("F1"), _("Show info about this application"), wxITEM_NORMAL );
	helpMenu->Append( menuHelpAbout );

	mbar->Append( helpMenu, _("&Help") );

	this->SetMenuBar( mbar );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer2;
	bSizer2 = new wxBoxSizer( wxHORIZONTAL );

	wxString IdChoiceChoices[] = { _("Default ID") };
	int IdChoiceNChoices = sizeof( IdChoiceChoices ) / sizeof( wxString );
	IdChoice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, IdChoiceNChoices, IdChoiceChoices, 0 );
	IdChoice->SetSelection( 0 );
	bSizer2->Add( IdChoice, 1, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	connectButton = new wxButton( this, wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer2->Add( connectButton, 0, wxALL|wxEXPAND, 5 );


	bSizer1->Add( bSizer2, 0, wxEXPAND, 5 );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxHORIZONTAL );

	staticText1 = new wxStaticText( this, wxID_ANY, _("Status:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText1->Wrap( -1 );
	bSizer4->Add( staticText1, 0, wxALL, 5 );

	statusText = new wxStaticText( this, wxID_ANY, _("Disconnected"), wxDefaultPosition, wxDefaultSize, 0 );
	statusText->Wrap( -1 );
	statusText->SetForegroundColour( wxColour( 255, 0, 0 ) );

	bSizer4->Add( statusText, 0, wxALL, 5 );


	bSizer1->Add( bSizer4, 0, 0, 5 );

	staticText2 = new wxStaticText( this, wxID_ANY, _("Send message:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText2->SetLabelMarkup( _("Send message:") );
	staticText2->Wrap( -1 );
	staticText2->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer1->Add( staticText2, 0, wxALL, 5 );

	sendCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	bSizer1->Add( sendCtrl, 0, wxALL|wxEXPAND, 5 );

	staticText3 = new wxStaticText( this, wxID_ANY, _("Recived message:"), wxDefaultPosition, wxDefaultSize, 0 );
	staticText3->SetLabelMarkup( _("Recived message:") );
	staticText3->Wrap( -1 );
	staticText3->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer1->Add( staticText3, 0, wxALL, 5 );

	reciveCtrl = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_READONLY );
	reciveCtrl->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_WINDOW ) );

	bSizer1->Add( reciveCtrl, 1, wxALL|wxEXPAND, 5 );

	clearButton = new wxButton( this, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( clearButton, 0, wxALL|wxALIGN_RIGHT, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_statusBar2 = this->CreateStatusBar( 1, wxSTB_SHOW_TIPS|wxSTB_SIZEGRIP, wxID_ANY );

	// Connect Events
	this->Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnRefresh ), this, menuFileRefresh->GetId());
	fileMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnQuit ), this, menuFileQuit->GetId());
	menuSettings->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::UpdateShowRule ), this, showMessages->GetId());
	lineEnding->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnLineEnding ), this, NLE->GetId());
	lineEnding->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnLineEnding ), this, LF->GetId());
	lineEnding->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnLineEnding ), this, CR->GetId());
	lineEnding->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnLineEnding ), this, LFCR->GetId());
	helpMenu->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( GUIFrame::OnAbout ), this, menuHelpAbout->GetId());
	connectButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
	sendCtrl->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrame::SendMessageFromGUI ), NULL, this );
	clearButton->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnClear ), NULL, this );
}

GUIFrame::~GUIFrame()
{
	// Disconnect Events
	this->Disconnect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler( GUIFrame::OnClose ) );
	connectButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnConnect ), NULL, this );
	sendCtrl->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( GUIFrame::SendMessageFromGUI ), NULL, this );
	clearButton->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( GUIFrame::OnClear ), NULL, this );

}

AboutDialog::AboutDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer4;
	bSizer4 = new wxBoxSizer( wxVERTICAL );

	m_staticText5 = new wxStaticText( this, wxID_ANY, _("DigiProtocol Monitor v1.0"), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
	m_staticText5->Wrap( -1 );
	m_staticText5->SetFont( wxFont( 11, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false, wxT("Arial") ) );

	bSizer4->Add( m_staticText5, 0, wxALL|wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	m_staticText8 = new wxStaticText( this, wxID_ANY, _("debugging tool for the DigiProtocol library "), wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL );
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
