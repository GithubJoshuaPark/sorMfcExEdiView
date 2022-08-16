// CDlgForDrawBtn.cpp : implementation file
//

#include "pch.h"
#include "sorMfcExEdiView.h"
#include "afxdialogex.h"
#include "CDlgForDrawBtn.h"


// CDlgForDrawBtn dialog

IMPLEMENT_DYNAMIC(CDlgForDrawBtn, CDialogEx)

CDlgForDrawBtn::CDlgForDrawBtn(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{
	nPos = 0;
}

CDlgForDrawBtn::~CDlgForDrawBtn()
{
}

void CDlgForDrawBtn::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_btn);
	DDX_Control(pDX, IDC_BUTTON2, m_btn2);
	DDX_Control(pDX, IDC_PROGRESS1, m_wndPrgressCtl);
}


BEGIN_MESSAGE_MAP(CDlgForDrawBtn, CDialogEx)
	ON_WM_DRAWITEM()
	ON_WM_ERASEBKGND()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgForDrawBtn message handlers


BOOL CDlgForDrawBtn::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	m_btn.SetBtnImage(IDB_BITMAP2);
	m_btn2.SetBtnImage(IDB_BITMAP2);

	m_btn.SetWindowPos(NULL, 80, 80, 40, 40, SWP_NOZORDER | SWP_NOMOVE);
	m_btn2.SetWindowPos(NULL, 80, 100, 40, 40, SWP_NOZORDER | SWP_NOMOVE);

	// MARK: - Make WM_TIMER
	if (SetTimer(TIMER_ID2, 1000, NULL) != TIMER_ID2)
	{
		AfxMessageBox(_T("Error: Failed to set timer!"));
	}

	srand((unsigned)time(NULL));

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgForDrawBtn::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


BOOL CDlgForDrawBtn::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	CRect cRect;
	GetClientRect(&cRect);
	pDC->FillSolidRect(&cRect, RGB(255,255,255));
	return TRUE;

	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CDlgForDrawBtn::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(TIMER_ID2);

	CDialogEx::OnClose();
}


void CDlgForDrawBtn::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_ID2) {
		if (nPos > 100) {
			nPos = 0;
		}
		else {
			nPos++;
		}
		
		m_wndPrgressCtl.SetnData(nPos);

		//RedrawWindow();
	}

	CDialogEx::OnTimer(nIDEvent);
}




void CDlgForDrawBtn::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialogEx::OnPaint() for painting messages
}
