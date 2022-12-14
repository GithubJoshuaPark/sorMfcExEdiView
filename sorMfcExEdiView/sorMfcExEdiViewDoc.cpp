
// sorMfcExEdiViewDoc.cpp : implementation of the CsorMfcExEdiViewDoc class
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


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CsorMfcExEdiViewDoc

IMPLEMENT_DYNCREATE(CsorMfcExEdiViewDoc, CDocument)

BEGIN_MESSAGE_MAP(CsorMfcExEdiViewDoc, CDocument)
END_MESSAGE_MAP()


// CsorMfcExEdiViewDoc construction/destruction

CsorMfcExEdiViewDoc::CsorMfcExEdiViewDoc() noexcept
{
	// TODO: add one-time construction code here

}

CsorMfcExEdiViewDoc::~CsorMfcExEdiViewDoc()
{
}

BOOL CsorMfcExEdiViewDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
	if (!m_viewList.IsEmpty())
	{
		reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(nullptr);
	}

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CsorMfcExEdiViewDoc serialization

void CsorMfcExEdiViewDoc::Serialize(CArchive& ar)
{
	// CEditView contains an edit control which handles all serialization
	//if (!m_viewList.IsEmpty())
	//{
	//	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
	//}

	CsorMfcExEdiViewView* pEditView = (CsorMfcExEdiViewView*)m_viewList.GetHead();
	pEditView->Serialize(ar);

//#ifdef SHARED_HANDLERS
//
//	if (m_viewList.IsEmpty() && ar.IsLoading())
//	{
//		CFile* pFile = ar.GetFile();
//		pFile->Seek(0, FILE_BEGIN);
//		ULONGLONG nFileSizeBytes = pFile->GetLength();
//		ULONGLONG nFileSizeChars = nFileSizeBytes/sizeof(TCHAR);
//		LPTSTR lpszText = (LPTSTR)malloc(((size_t)nFileSizeChars + 1) * sizeof(TCHAR));
//		if (lpszText != nullptr)
//		{
//			ar.Read(lpszText, (UINT)nFileSizeBytes);
//			lpszText[nFileSizeChars] = '\0';
//			m_strThumbnailContent = lpszText;
//			m_strSearchContent = lpszText;
//		}
//	}
//#endif

}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CsorMfcExEdiViewDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(m_strThumbnailContent, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CsorMfcExEdiViewDoc::InitializeSearchContent()
{
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// Use the entire text file content as the search content.
	SetSearchContent(m_strSearchContent);
}

void CsorMfcExEdiViewDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CsorMfcExEdiViewDoc diagnostics

#ifdef _DEBUG
void CsorMfcExEdiViewDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CsorMfcExEdiViewDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CsorMfcExEdiViewDoc commands
