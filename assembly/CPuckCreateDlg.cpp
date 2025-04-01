// CPuckCreateDlg.cpp: файл реализации
//

#include "pch.h"
#include "assembly.h"
#include "afxdialogex.h"
#include "CPuckCreateDlg.h"


// Диалоговое окно CPuckCreateDlg

IMPLEMENT_DYNAMIC(CPuckCreateDlg, CDialog)

CPuckCreateDlg::CPuckCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CPuckCreateDlg, pParent)
{

}

CPuckCreateDlg::~CPuckCreateDlg()
{
}

void CPuckCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO2, m_cbPuckThick);
	DDX_Control(pDX, IDC_COMBO3, m_cbPuckR);
}


BEGIN_MESSAGE_MAP(CPuckCreateDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPuckCreateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CPuckCreateDlg


void CPuckCreateDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	pDoc->m_PuckRO = pDoc->PuckSizes[m_cbPuckR.GetCurSel()].RO;
	pDoc->m_PuckThick = pDoc->PuckSizes[m_cbPuckThick.GetCurSel()].Thick;
	CDialog::OnOK();
}


BOOL CPuckCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	for (int i = 0; i < pDoc->SizesLength; i++)
	{
		CString str;
		str.Format(_T("%d"), pDoc->NutSizes[i].RO); // Преобразование числа в строку
		m_cbPuckR.AddString(str); // Добавление строки в комбобокс

		str.Format(_T("%d"), pDoc->NutSizes[i].HexagonThick); // Преобразование числа в строку
		m_cbPuckThick.AddString(str); // Добавление строки в комбобокс

	}
	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
