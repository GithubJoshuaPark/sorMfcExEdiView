#pragma once

// CTestData command target

class CTestData : public CObject
{
	DECLARE_SERIAL(CTestData)

public:
	CTestData();
	virtual ~CTestData();

	int m_nData;
	int m_nLine;
	virtual void Serialize(CArchive& ar);
};


