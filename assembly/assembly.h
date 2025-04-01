
// assembly.h: основной файл заголовка для приложения assembly
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CassemblyApp:
// Сведения о реализации этого класса: assembly.cpp
//

class CassemblyApp : public CWinApp
{
public:
	CassemblyApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CassemblyApp theApp;
