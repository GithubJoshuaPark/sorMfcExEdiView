// CTextProgressCtrl.cpp : implementation file
//

#include "pch.h"
#include "sorMfcExEdiView.h"
#include "CTextProgressCtrl.h"


// CTextProgressCtrl

IMPLEMENT_DYNAMIC(CTextProgressCtrl, CProgressCtrl)

CTextProgressCtrl::CTextProgressCtrl()
{
	m_nData = 0;
}

CTextProgressCtrl::~CTextProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CTextProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CTextProgressCtrl message handlers


void CTextProgressCtrl::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CProgressCtrl::OnPaint() for painting messages

	CString strTmp = _T("");
	strTmp.Format(_T("%d%%"), m_nData);

	// 프로그래스 컨트롤을 둘로 나누기 위해서 윈도우 크기를 계산
	CRect cRect, LeftRect, RightRect;
	GetClientRect(&cRect);
	LeftRect  = cRect;
	RightRect = cRect;

	// 1%에 해당하는 윈도우 크기를 계산
	// 둘로 나뉘어진 왼쪽과 오른쪽 각각에 대해서 다른색을 칠함
	LeftRect.right = (cRect.right * m_nData) / 100;
	RightRect.left = (cRect.right * m_nData) / 100;

	dc.FillSolidRect(LeftRect, RGB(0,0,128));
	dc.FillSolidRect(RightRect, RGB(255, 255, 255));

	// 왼쪽과 오른쪽을 두 영역으로 구분
	CRgn LeftRgn, RightRgn;
	LeftRgn.CreateRectRgnIndirect(LeftRect);
	RightRgn.CreateRectRgnIndirect(RightRect);

	// 왼쪽 영역에 비율 표시 텍스트를 중앙 정렬 출력
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SelectClipRgn(&LeftRgn);
	dc.DrawText(strTmp, cRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// 오른쪽 영역에 비율 표시 텍스트를 중앙 정렬 출력
	dc.SetTextColor(RGB(0, 0, 128));
	dc.SelectClipRgn(&RightRgn);
	dc.DrawText(strTmp, cRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}


void CTextProgressCtrl::SetnData(int nPos)
{
	// TODO: Add your implementation code here.
	m_nData = nPos;
	RedrawWindow();
}
