#include "MyApp.h"
#include "MyFrame.h"

DECLARE_APP(MyApp)

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	wxFrame* frame = new MyFrame(wxString(wxT("ParseEDID")), wxDefaultPosition, wxSize(600,500));
	frame->Show(true);
	return true;
}