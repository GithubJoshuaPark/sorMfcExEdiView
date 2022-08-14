
// sorMfcExEdiViewView.h : interface of the CsorMfcExEdiViewView class
//

#pragma once

#include "CTestData.h"
#include <atlimage.h>  // CImage

#define TIMER_ID 10

class CsorMfcExEdiViewView : public CEditView
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CsorMfcExEdiViewView)

// Attributes
public:
	CsorMfcExEdiViewDoc* GetDocument() const;

// Operations
public:
	int m_timer_occur_cnt;

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	CsorMfcExEdiViewView() noexcept;
	virtual ~CsorMfcExEdiViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
	LRESULT afx_msg OnTestMessage(WPARAM wParam, LPARAM lParam);  // 사용자 정의 메시지 핸들러 (UM_TESTMESSAGE defined in framework.h )
public:
	virtual void Serialize(CArchive& ar);

	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnClose();
};

#ifndef _DEBUG  // debug version in sorMfcExEdiViewView.cpp
inline CsorMfcExEdiViewDoc* CsorMfcExEdiViewView::GetDocument() const
   { return reinterpret_cast<CsorMfcExEdiViewDoc*>(m_pDocument); }
#endif

