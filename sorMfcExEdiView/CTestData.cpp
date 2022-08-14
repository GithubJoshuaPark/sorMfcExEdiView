// CTestData.cpp : implementation file
//

#include "pch.h"
#include "sorMfcExEdiView.h"
#include "CTestData.h"


// CTestData
IMPLEMENT_SERIAL(CTestData, CObject, VERSIONABLE_SCHEMA | 2)

CTestData::CTestData()
{
	m_nData = 0;
	m_nLine = 0;
}

CTestData::~CTestData()
{
}

// CTestData member functions

void CTestData::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_nData << m_nLine;
	}
	else
	{	// loading code
		ar >> m_nData >> m_nLine;
	}
}
