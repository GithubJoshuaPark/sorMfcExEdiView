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
	OutputDebugStringW(_T("※☆★ CImageButton::DrawItem ※☆★ \n"));

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
	OutputDebugStringW(_T("※☆★ CImageButton::OnMouseHover ※☆★ \n"));
	m_bHover = TRUE;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CButton::OnMouseHover(nFlags, point);
}


void CImageButton::OnMouseLeave()
{
	// TODO: Add your message handler code here and/or call default
	OutputDebugStringW(_T("※☆★ CImageButton::OnMouseLeave ※☆★ \n"));
	m_bHover    = FALSE;
	m_bTracking = FALSE;
	RedrawWindow(NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	CButton::OnMouseLeave();
}


void CImageButton::OnMouseMove(UINT nFlags, CPoint point)
{
	OutputDebugStringW(_T("※☆★ CImageButton::OnMouseMove ※☆★ \n"));
	// TODO: Add your message handler code here and/or call default
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		::ZeroMemory(&tme, sizeof(tme));

		tme.cbSize      = sizeof(tme);
		tme.hwndTrack   = m_hWnd;                 // 이벤트를 받을 윈도우 핸들
		tme.dwFlags     = TME_LEAVE | TME_HOVER;  // 발생시킬 이벤트
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

