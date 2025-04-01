// CAssembleCreateDlg.cpp: файл реализации
//

#include "pch.h"
#include "assembly.h"
#include "afxdialogex.h"
#include "CAssembleCreateDlg.h"


// Диалоговое окно CAssembleCreateDlg

IMPLEMENT_DYNAMIC(CAssembleCreateDlg, CDialog)

CAssembleCreateDlg::CAssembleCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CAssembleCreateDlg, pParent)
{

}

CAssembleCreateDlg::~CAssembleCreateDlg()
{
}

void CAssembleCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAssembleCreateDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CAssembleCreateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CAssembleCreateDlg


void CAssembleCreateDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CDialog::OnOK();
}


BOOL CAssembleCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
