///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "gobang.h"

///////////////////////////////////////////////////////////////////////////

GobangDialog::GobangDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetBackgroundColour( wxColour( 213, 220, 73 ) );
	
	
	this->Centre( wxBOTH );
	
	// Connect Events
	this->Connect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( GobangDialog::OnEraseBackground ) );
	this->Connect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( GobangDialog::OnInitDialog ) );
	this->Connect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( GobangDialog::OnLeaveWindow ) );
	this->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GobangDialog::OnLeftDown ) );
	this->Connect( wxEVT_MOTION, wxMouseEventHandler( GobangDialog::OnMouseMove ) );
	this->Connect( wxEVT_PAINT, wxPaintEventHandler( GobangDialog::OnPaint ) );
}

GobangDialog::~GobangDialog()
{
	// Disconnect Events
	this->Disconnect( wxEVT_ERASE_BACKGROUND, wxEraseEventHandler( GobangDialog::OnEraseBackground ) );
	this->Disconnect( wxEVT_INIT_DIALOG, wxInitDialogEventHandler( GobangDialog::OnInitDialog ) );
	this->Disconnect( wxEVT_LEAVE_WINDOW, wxMouseEventHandler( GobangDialog::OnLeaveWindow ) );
	this->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( GobangDialog::OnLeftDown ) );
	this->Disconnect( wxEVT_MOTION, wxMouseEventHandler( GobangDialog::OnMouseMove ) );
	this->Disconnect( wxEVT_PAINT, wxPaintEventHandler( GobangDialog::OnPaint ) );
	
}
