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

	// ���α׷��� ��Ʈ���� �ѷ� ������ ���ؼ� ������ ũ�⸦ ���
	CRect cRect, LeftRect, RightRect;
	GetClientRect(&cRect);
	LeftRect  = cRect;
	RightRect = cRect;

	// 1%�� �ش��ϴ� ������ ũ�⸦ ���
	// �ѷ� �������� ���ʰ� ������ ������ ���ؼ� �ٸ����� ĥ��
	LeftRect.right = (cRect.right * m_nData) / 100;
	RightRect.left = (cRect.right * m_nData) / 100;

	dc.FillSolidRect(LeftRect, RGB(0,0,128));
	dc.FillSolidRect(RightRect, RGB(255, 255, 255));

	// ���ʰ� �������� �� �������� ����
	CRgn LeftRgn, RightRgn;
	LeftRgn.CreateRectRgnIndirect(LeftRect);
	RightRgn.CreateRectRgnIndirect(RightRect);

	// ���� ������ ���� ǥ�� �ؽ�Ʈ�� �߾� ���� ���
	dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));
	dc.SelectClipRgn(&LeftRgn);
	dc.DrawText(strTmp, cRect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);

	// ������ ������ ���� ǥ�� �ؽ�Ʈ�� �߾� ���� ���
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
