
// sorMfcExEdiViewView.cpp : implementation of the CsorMfcExEdiViewView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "sorMfcExEdiView.h"
#endif

#include "sorMfcExEdiViewDoc.h"
#include "sorMfcExEdiViewView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CsorMfcExEdiViewView

IMPLEMENT_DYNCREATE(CsorMfcExEdiViewView, CEditView)

BEGIN_MESSAGE_MAP(CsorMfcExEdiViewView, CEditView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_MESSAGE(UM_TESTMESSAGE, &CsorMfcExEdiViewView::OnTestMessage)
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_WM_PAINT()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CsorMfcExEdiViewView construction/destruction

CsorMfcExEdiViewView::CsorMfcExEdiViewView() noexcept
{
	// TODO: add construction code here
	m_timer_occur_cnt = 0;
}

CsorMfcExEdiViewView::~CsorMfcExEdiViewView()
{
}

BOOL CsorMfcExEdiViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}


// CsorMfcExEdiViewView printing

BOOL CsorMfcExEdiViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default CEditView preparation
	return CEditView::OnPreparePrinting(pInfo);
}

void CsorMfcExEdiViewView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView begin printing
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CsorMfcExEdiViewView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Default CEditView end printing
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CsorMfcExEdiViewView diagnostics

#ifdef _DEBUG
void CsorMfcExEdiViewView::AssertValid() const
{
	CEditView::AssertValid();
}

void CsorMfcExEdiViewView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CsorMfcExEdiViewDoc* CsorMfcExEdiViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CsorMfcExEdiViewDoc)));
	return (CsorMfcExEdiViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CsorMfcExEdiViewView message handlers


void CsorMfcExEdiViewView::Serialize(CArchive& ar)
{
	
	CEdit&  theEdit   = GetEditCtrl();

	if (ar.IsStoring())
	{	// storing code
		
		CTestData cTestData;
		TCHAR     szBuffer[512];
		cTestData.m_nLine = theEdit.GetLineCount();

		//ar << &cTestData;

		//for (int i = 0; i < cTestData.m_nLine; i++)
		for (int i = 0; i < theEdit.GetLineCount(); i++)
		{
			::ZeroMemory(szBuffer, sizeof(szBuffer));
			if (theEdit.GetLine(i, szBuffer, 512) > 0) {
				ar.WriteString(szBuffer);
			}

			//if (i + 1 < cTestData.m_nLine) {
			if (i + 1 < theEdit.GetLineCount()) {
				ar.WriteString(_T("\r\n"));
			}
		}
	}
	else
	{	// loading code
		CString ls_strTmp     = _T("");
		CString ls_strText    = _T("");
		
		//CTestData* pcTestData = NULL;
		//ar >> pcTestData;

		int i = 0;
		while (ar.ReadString(ls_strTmp)) {
			ls_strText += ls_strTmp;
			ls_strText += "\r\n";
			i++;
		}

		theEdit.SetWindowTextW(ls_strText);
		//ls_strTmp.Format(_T("%d Lines"), pcTestData->m_nLine);
		ls_strTmp.Format(_T("%d Lines"), i);

		AfxMessageBox(ls_strTmp);

		//delete pcTestData;
	}
}


// MARK: - User define message handler
LRESULT CsorMfcExEdiViewView::OnTestMessage(WPARAM wParam, LPARAM lParam) 
{
	AfxMessageBox(_T("#define UM_TESTMESSAGE"));
	return 0;
}


int CsorMfcExEdiViewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	// MARK: - Make WM_TIMER
	if (SetTimer(TIMER_ID, 1000, NULL) != TIMER_ID)
	{
		AfxMessageBox(_T("Error: Failed to set timer!"));
	}

	srand((unsigned)time(NULL));

	return 0;
}


void CsorMfcExEdiViewView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TIMER_ID) {
		m_timer_occur_cnt++;

		RedrawWindow();
	}
	CEditView::OnTimer(nIDEvent);
}


void CsorMfcExEdiViewView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CEditView::OnPaint() for painting messages
	CRect cRect;
	GetClientRect(&cRect);

	CString ls_str = _T("");
	ls_str.Format(_T("Timer occured: [%d]"), m_timer_occur_cnt);

	CFont cFont;
	CFont* pOldFont;

	cFont.CreatePointFont(100, _T("D2Coding"), &dc);

	pOldFont = dc.SelectObject(&cFont);

	dc.SetBkColor(RGB(0,0,0));
	dc.SetTextColor(RGB(192,192,192));
	dc.SetBkMode(TRANSPARENT);
	dc.TextOutW((cRect.right - cRect.left) / 2, 
		          (cRect.bottom - cRect.top) / 2, ls_str);

	CImage cImage;
	cImage.LoadFromResource(AfxGetInstanceHandle(), IDB_BITMAP1);

	cImage.BitBlt(dc.m_hDC, 
		rand() % cRect.Width(), 
		rand() % cRect.Height(),
		SRCCOPY);

	dc.SelectObject(pOldFont);
}


void CsorMfcExEdiViewView::OnClose()
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(TIMER_ID);

	CEditView::OnClose();
}
