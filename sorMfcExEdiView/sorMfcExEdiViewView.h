
// sorMfcExEdiViewView.h : interface of the CsorMfcExEdiViewView class
//

#pragma once

#include "CTestData.h"


class CsorMfcExEdiViewView : public CEditView
{
protected: // create from serialization only
	
	DECLARE_DYNCREATE(CsorMfcExEdiViewView)

// Attributes
public:
	CsorMfcExEdiViewDoc* GetDocument() const;

// Operations
public:

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
public:
	virtual void Serialize(CArchive& ar);
};

#ifndef _DEBUG  // debug version in sorMfcExEdiViewView.cpp
inline CsorMfcExEdiViewDoc* CsorMfcExEdiViewView::GetDocument() const
   { return reinterpret_cast<CsorMfcExEdiViewDoc*>(m_pDocument); }
#endif

