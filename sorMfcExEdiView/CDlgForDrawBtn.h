#pragma once
#include "afxdialogex.h"
#include "CImageButton.h"
#include "CTextProgressCtrl.h"

#define TIMER_ID2 20

// CDlgForDrawBtn dialog

class CDlgForDrawBtn : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgForDrawBtn)

public:
	CDlgForDrawBtn(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDlgForDrawBtn();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CImageButton m_btn;
	CImageButton m_btn2;
	int nPos;

	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	CTextProgressCtrl m_wndPrgressCtl;
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
};
