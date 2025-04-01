// CPressureNutCreateDlg.cpp: файл реализации
//

#include "pch.h"
#include "assembly.h"
#include "afxdialogex.h"
#include "CPressureNutCreateDlg.h"


// Диалоговое окно CPressureNutCreateDlg

IMPLEMENT_DYNAMIC(CPressureNutCreateDlg, CDialog)

CPressureNutCreateDlg::CPressureNutCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CPressureNutCreateDlg, pParent)
{

}

CPressureNutCreateDlg::~CPressureNutCreateDlg()
{
}

void CPressureNutCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cbNutR);
	DDX_Control(pDX, IDC_COMBO2, m_cbNutHexagonThick);
	DDX_Control(pDX, IDC_COMBO3, m_cbNutHexagonR);
}


BEGIN_MESSAGE_MAP(CPressureNutCreateDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPressureNutCreateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений CPressureNutCreateDlg


void CPressureNutCreateDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	
	pDoc->m_NutRO = pDoc->NutSizes[m_cbNutR.GetCurSel()].RO;
	pDoc->m_NutHexagonThick = pDoc->NutSizes[m_cbNutHexagonThick.GetCurSel()].HexagonThick;
	pDoc->m_NutHexagonR = pDoc->NutSizes[m_cbNutHexagonR.GetCurSel()].HexagonR;
	CDialog::OnOK();
}


BOOL CPressureNutCreateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	for (int i = 0; i < pDoc->SizesLength; i++)
	{
		CString str;
		str.Format(_T("%d"), pDoc->NutSizes[i].RO); // Преобразование числа в строку
		m_cbNutR.AddString(str); // Добавление строки в комбобокс

		str.Format(_T("%d"), pDoc->NutSizes[i].HexagonThick); // Преобразование числа в строку
		m_cbNutHexagonThick.AddString(str); // Добавление строки в комбобокс

		str.Format(_T("%f"), pDoc->NutSizes[i].HexagonR); // Преобразование числа в строку
		m_cbNutHexagonR.AddString(str); // Добавление строки в комбобокс
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // Исключение: страница свойств OCX должна возвращать значение FALSE
}
