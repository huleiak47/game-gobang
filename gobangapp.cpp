#include <wx/wx.h>
#include "gobangimpl.h"

class GobangApp: public wxApp
{
public:
    virtual bool OnInit();

};

DECLARE_APP(GobangApp);

bool GobangApp::OnInit()
{
    GobangDialogImpl dlg(NULL);
    dlg.ShowModal();
    return false;
}


IMPLEMENT_APP(GobangApp)
