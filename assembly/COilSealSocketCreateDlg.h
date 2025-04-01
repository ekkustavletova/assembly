#pragma once
#include "afxdialogex.h"
#include "assemblyDoc.h"


// Диалоговое окно COilSealSocketCreate

class COilSealSocketCreateDlg : public CDialog
{
	DECLARE_DYNAMIC(COilSealSocketCreateDlg)

public:
	COilSealSocketCreateDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~COilSealSocketCreateDlg();

	CassemblyDoc* pDoc;

	

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

public:
	DECLARE_MESSAGE_MAP()
	CComboBox m_cbSealR;
	CComboBox m_cbSealRInner;
	CComboBox m_cbSealLength;
	afx_msg void OnClickedBtnOilsealsocketCreate();
	afx_msg void OnClose();
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnNutCreate();
	afx_msg void OnDlgNutSet();
};
