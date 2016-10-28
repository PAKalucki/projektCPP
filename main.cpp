#include <wx/wx.h>
#include "Gui.h"

class MyApp : public wxApp
{
public:
	virtual bool OnInit();
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	Gui *gui = new Gui(wxT("Projekt Kalkulator"));
	gui->Show(true);
	return true;
}
