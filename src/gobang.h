///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  8 2010)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __gobang__
#define __gobang__

#include <wx/string.h>
#include <wx/dialog.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class GobangDialog
///////////////////////////////////////////////////////////////////////////////
class GobangDialog : public wxDialog 
{
	private:
	
	protected:
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnEraseBackground( wxEraseEvent& event ) { event.Skip(); }
		virtual void OnInitDialog( wxInitDialogEvent& event ) { event.Skip(); }
		virtual void OnLeaveWindow( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnMouseMove( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnPaint( wxPaintEvent& event ) { event.Skip(); }
		
	
	public:
		
		GobangDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("gobang"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 600,625 ), long style = wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX );
		~GobangDialog();
	
};

#endif //__gobang__
