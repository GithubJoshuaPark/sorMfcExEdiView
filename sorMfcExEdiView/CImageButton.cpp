// CImageButton.cpp : implementation file
//

#include "pch.h"
#include "sorMfcExEdiView.h"
#include "CImageButton.h"


// CImageButton

IMPLEMENT_DYNAMIC(CImageButton, CButton)

CImageButton::CImageButton()
{
	m_bHover    = FALSE;
	m_bTracking = FALSE;
	m_uImageID  = 0;
}

CImageButton::~CImageButton()
{
}


BEGIN_MESSAGE_MAP(CImageButton, CButton)
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



// CImageButton message handlers


void CImageButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	OutputDebugStringW(_T("�ء١� CImageButton::DrawItem �ء١� \n"));

	if (m_uImageID == 0) return;

	// TODO:  Add your code to draw the specified item
	CDC* pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	CBitmap Bmp;
	BITMAP bmpInfo = { 0 };

	Bmp.LoadBitmapW(IDB_BITMAP2);
	Bmp.GetBitmap(&bmpInfo);

	int cx = bmpInfo.bmWidth / 3;
	int cy = bmpInfo.bmHeight;

	CBitmap* pOldBmp = MemDC.SelectObject(&Bmp);

	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		pDC->BitBlt(0, 0, cx, cy,
			&MemDC, (cx*2), 0, SRCCOPY);
	}
	else {
		if (m_bHover) {
			pDC->BitBlt(0, 0, cx, cy,
				&MemDC, cx, 0, SRCCOPY);
		}
		else {
			pDC->BitBlt(0, 0, cx, cy,
				&MemDC, 0, 0, SRCCOPY);
		}
	}

	MemDC.SelectObject(pOldBmp);
	
}


void CImageButton::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	OutputDebugStringW(_T("�ء١� CImageButton::OnMouseHover �ء١� \n"));
	m_bHover = TRUE;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CButton::OnMouseHover(nFlags, point);
}


void CImageButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	OutputDebugStringW(_T("�ء١� CImageButton::OnMouseLeave �ء١� \n"));
	m_bHover    = FALSE;
	m_bTracking = FALSE;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CButton::OnMouseLeave();
}


void CImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	OutputDebugStringW(_T("�ء١� CImageButton::OnMouseMove �ء١� \n"));
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		::ZeroMemory(&tme, sizeof(tme));

		tme.cbSize      = sizeof(tme);
		tme.hwndTrack   = m_hWnd;                 // �̺�Ʈ�� ���� ������ �ڵ�
		tme.dwFlags     = TME_LEAVE | TME_HOVER;  // �߻���ų �̺�Ʈ
		tme.dwHoverTime = 1;                      // millesecond hover timerout

		m_bTracking = ::_TrackMouseEvent(&tme);
	}

	CButton::OnMouseMove(nFlags, point);
}


void CImageButton::SetBtnImage(UINT uID)
{
	// TODO: Add your implementation code here.
	m_uImageID = uID;
	RedrawWindow();
}

