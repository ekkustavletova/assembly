#pragma once
#include "afxdialogex.h"
#include "assemblyDoc.h"


// Диалоговое окно CAssembleCreateDlg

class CAssembleCreateDlg : public CDialog
{
	DECLARE_DYNAMIC(CAssembleCreateDlg)

public:
	CAssembleCreateDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CAssembleCreateDlg();

	CassemblyDoc* pDoc;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CAssembleCreateDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
