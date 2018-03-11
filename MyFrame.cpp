#include "MyFrame.h"

MyFrame::MyFrame(const wxString &title)
		:wxFrame(NULL,wxID_ANY,title,wxPoint(300,200),wxSize(500,350))
{
	//wxIcon icon(wxT("AUIDemo.ico"), wxBITMAP_TYPE_ICO, 16, 16);
	//SetIcon(icon);
	
	//��ÿ�ܵĹ���Ȩ
	m_mgr.SetManagedWindow(this);
	
	m_mgr.AddPane(new wxPanel(this, wxID_ANY,wxDefaultPosition,wxSize(80, 80)), wxAuiPaneInfo().Name(wxT("panel1")).Caption(wxT("panel1")).Center().CloseButton(true).MaximizeButton(true).CaptionVisible(true));
	
	m_mgr.AddPane(new wxPanel(this, wxID_ANY,wxDefaultPosition,wxSize(80, 40)), wxAuiPaneInfo().Name(wxT("panel2")).Caption(wxT("panel2")).Bottom().CloseButton(true).MaximizeButton(true).CaptionVisible(true));
	
	//Ȼ����¹�����
	m_mgr.Update();
}

MyFrame::~MyFrame()
{
    m_mgr.UnInit();
}
