#pragma once
#include "afxdialogex.h"
#include "assemblyDoc.h"


// Диалоговое окно CPuckCreateDlg

class CPuckCreateDlg : public CDialog
{
	DECLARE_DYNAMIC(CPuckCreateDlg)

public:
	CPuckCreateDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CPuckCreateDlg();

	CassemblyDoc* pDoc;

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPuckCreateDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cbPuckThick;
	CComboBox m_cbPuckR;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
