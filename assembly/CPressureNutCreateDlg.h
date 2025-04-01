#pragma once
#include "afxdialogex.h"
#include "assemblyDoc.h"


// Диалоговое окно CPressureNutCreateDlg

class CPressureNutCreateDlg : public CDialog
{
	DECLARE_DYNAMIC(CPressureNutCreateDlg)

public:
	CPressureNutCreateDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CPressureNutCreateDlg();


	CassemblyDoc* pDoc;





// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPressureNutCreateDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CComboBox m_cbNutR;
	CComboBox m_cbNutHexagonThick;
	CComboBox m_cbNutHexagonR;
	virtual BOOL OnInitDialog();
};
