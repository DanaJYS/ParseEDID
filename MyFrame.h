// MyFrame.h: interface for the MyFrame class.
//
//////////////////////////////////////////////////////////////////////
#include "wx/artprov.h"
#include "wx/aui/aui.h"
#include "wx/wx.h"

class MyFrame:public wxFrame
{
public:
	MyFrame(const wxString &title=wxT("AUI"), const wxPoint& pos=wxDefaultPosition, const wxSize& size=wxSize(600,500));
	~MyFrame();

private:
	//�ȶ���һ��wxAuiManager����
    wxAuiManager m_mgr;
};