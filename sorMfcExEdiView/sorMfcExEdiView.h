
// sorMfcExEdiView.h : main header file for the sorMfcExEdiView application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols

// CsorMfcExEdiViewApp:
// See sorMfcExEdiView.cpp for the implementation of this class
//


class CsorMfcExEdiViewApp : public CWinApp
{
public:
	CsorMfcExEdiViewApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CsorMfcExEdiViewApp theApp;
