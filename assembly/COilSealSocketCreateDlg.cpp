// COilSealSocketCreate.cpp: файл реализации
//

#include "pch.h"
#include "assembly.h"
#include "afxdialogex.h"
#include "COilSealSocketCreateDlg.h"


// Диалоговое окно COilSealSocketCreate

IMPLEMENT_DYNAMIC(COilSealSocketCreateDlg, CDialog)

COilSealSocketCreateDlg::COilSealSocketCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
{

}

COilSealSocketCreateDlg::~COilSealSocketCreateDlg()
{
}

void COilSealSocketCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SEAL_R, m_cbSealR);
	DDX_Control(pDX, IDC_SEAL_R_INNER, m_cbSealRInner);
	DDX_Control(pDX, IDC_SEAL_LENGTH, m_cbSealLength);
}

// Обработчики сообщений COilSealSocketCreate
BEGIN_MESSAGE_MAP(COilSealSocketCreateDlg, CDialog)
	ON_BN_CLICKED(BTN_OILSEALSOCKET_CREATE, &COilSealSocketCreateDlg::OnClickedBtnOilsealsocketCreate)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDOK, &COilSealSocketCreateDlg::OnBnClickedOk)
	ON_COMMAND(ID_NUT_CREATE, &COilSealSocketCreateDlg::OnNutCreate)
	ON_COMMAND(DLG_NUT_SET, &COilSealSocketCreateDlg::OnDlgNutSet)
END_MESSAGE_MAP()


void COilSealSocketCreateDlg::OnClickedBtnOilsealsocketCreate()
{
	// TODO: добавьте свой код обработчика уведомлений
}


void COilSealSocketCreateDlg::OnClose()
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CDialog::OnClose();
}


void COilSealSocketCreateDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	pDoc->m_SealRO = pDoc->SealSizes[m_cbSealR.GetCurSel()].RO;
	pDoc->m_SealRI = pDoc->SealSizes[m_cbSealRInner.GetCurSel()].RI;
	pDoc->m_SealLength = pDoc->SealSizes[m_cbSealLength.GetCurSel()].Length;
	CDialog::OnOK();
}


BOOL COilSealSocketCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию

	for (int i = 0; i < pDoc->SizesLength; i++)
	{
		CString str;
		str.Format(_T("%d"), pDoc->SealSizes[i].RO); // Преобразование числа в строку
		m_cbSealR.AddString(str); // Добавление строки в комбобокс

		str.Format(_T("%d"), pDoc->SealSizes[i].RI); // Преобразование числа в строку
		m_cbSealRInner.AddString(str); // Добавление строки в комбобокс

		str.Format(_T("%d"), pDoc->SealSizes[i].Length); // Преобразование числа в строку
		m_cbSealLength.AddString(str); // Добавление строки в комбобокс
	}

	

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}



void COilSealSocketCreateDlg::OnNutCreate()
{
	// TODO: добавьте свой код обработчика команд
}


void COilSealSocketCreateDlg::OnDlgNutSet()
{
	// TODO: добавьте свой код обработчика команд
}
