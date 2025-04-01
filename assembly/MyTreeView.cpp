// MyTreeView.cpp: файл реализации
//

#include "pch.h"
#include "assembly.h"
#include "MyTreeView.h"
#include "assemblyDoc.h"
#include "assemblyView.h"
#include "MainFrm.h"
#include "CPressureNutCreateDlg.h"
#include "CPuckCreateDlg.h"
// MyTreeView

IMPLEMENT_DYNCREATE(MyTreeView, CTreeView)

MyTreeView::MyTreeView()
{

}

MyTreeView::~MyTreeView()
{
}

BEGIN_MESSAGE_MAP(MyTreeView, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
//	ON_NOTIFY_REFLECT(NM_DBLCLK, &MyTreeView::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &MyTreeView::OnNMDblclk)
END_MESSAGE_MAP()


// Диагностика MyTreeView

#ifdef _DEBUG
void MyTreeView::AssertValid() const
{
	CTreeView::AssertValid();
}

#ifndef _WIN32_WCE
void MyTreeView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// Обработчики сообщений MyTreeView


int MyTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES
		| TVS_HASBUTTONS
		| TVS_LINESATROOT
		| TVS_SHOWSELALWAYS;

	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Добавьте специализированный код создания

	return 0;
}

void MyTreeView::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();
	
	tree.DeleteAllItems();

	m_hAssembly = tree.InsertItem(L"Сальник односторонний типа СКРО", -1, -1, NULL, TVI_FIRST);

	m_hOilSealSocket = tree.InsertItem(L"Гнездо сальника типа СКРО", -1, -1, m_hAssembly, TVI_FIRST);
	m_hPressureNut = tree.InsertItem(L"Гайка нажимная", -1, -1, m_hAssembly, TVI_FIRST);
	m_hPuck = tree.InsertItem(L"Шайба", -1, -1, m_hAssembly, TVI_FIRST);

	tree.SetCheck(m_hOilSealSocket, m_pDoc->m_bOilSealSocket);
	tree.SetCheck(m_hPressureNut, m_pDoc->m_bPressureNut);
	tree.SetCheck(m_hPuck, m_pDoc->m_bPuck);

	tree.Expand(m_hAssembly, TVE_EXPAND);
}

void MyTreeView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	CTreeView::OnLButtonDown(nFlags, point);
	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;

	tree.GetItemRect(m_hAssembly, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hAssembly);
	}

	tree.GetItemRect(m_hOilSealSocket, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hOilSealSocket);
	}

	tree.GetItemRect(m_hPressureNut, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hPressureNut);
	}

	tree.GetItemRect(m_hPuck, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hPuck);
	}

	/*if (tree.GetSelectedItem() == m_hAssembly) {
		bool check = tree.GetCheck(m_hAssembly);

		tree.SetCheck(m_hOilSealSocket, check);
		tree.SetCheck(m_hPressureNut, check);
		tree.SetCheck(m_hPuck, check);

	}
	else {
		tree.SetCheck(m_hAssembly, false);
	} */
	if (tree.GetSelectedItem() == m_hAssembly)
	{
		m_pDoc->m_bOilSealSocket = FALSE;
		m_pDoc->m_bPuck = FALSE;
		m_pDoc->m_bPressureNut = FALSE;
		m_pDoc->m_bAssembly = TRUE;
	}
	if (tree.GetSelectedItem() == m_hOilSealSocket)
	{
		m_pDoc->m_bOilSealSocket = TRUE;
		m_pDoc->m_bPuck = FALSE;
		m_pDoc->m_bPressureNut = FALSE;
		m_pDoc->m_bAssembly = FALSE;
	}
	if (tree.GetSelectedItem() == m_hPressureNut)
	{
		m_pDoc->m_bOilSealSocket = FALSE;
		m_pDoc->m_bPuck = FALSE;
		m_pDoc->m_bPressureNut = TRUE;
		m_pDoc->m_bAssembly = FALSE;
	}
	if (tree.GetSelectedItem() == m_hPuck)
	{
		m_pDoc->m_bOilSealSocket = FALSE;
		m_pDoc->m_bPuck = TRUE;
		m_pDoc->m_bPressureNut = FALSE;
		m_pDoc->m_bAssembly = FALSE;
	}

	/*auto b1 = tree.GetCheck(m_hOilSealSocket);
	m_pDoc->m_bOilSealSocket = b1;
	m_pDoc->m_bPressureNut = tree.GetCheck(m_hPressureNut);
	m_pDoc->m_bPuck = tree.GetCheck(m_hPuck);*/

	m_pDoc->pView->Invalidate();
}




void MyTreeView::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: добавьте свой код обработчика уведомлений
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	//CListCtrl& listCtrl = CListView::GetListCtrl();

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (pNMItemActivate->iItem != -1)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
		CTreeCtrl& treeCtrl = GetTreeCtrl();

		// Получаем выбранный элемент
		HTREEITEM hSelectedItem = treeCtrl.GetSelectedItem();
		if (hSelectedItem == m_hPressureNut)
		{
			CPressureNutCreateDlg dlg;
			dlg.pDoc = m_pDoc;
			if (dlg.DoModal() == IDOK)
			{
				CWnd* pWnd = AfxGetMainWnd();

				pWnd->Invalidate();
				pWnd->UpdateWindow();
			}
		}
		if (hSelectedItem == m_hAssembly)
		{

		}
		if (hSelectedItem == m_hOilSealSocket)
		{
			COilSealSocketCreateDlg dlg;
			dlg.pDoc = m_pDoc;

			if (dlg.DoModal() == IDOK)
			{
				CWnd* pWnd = AfxGetMainWnd();

				pWnd->Invalidate();
				pWnd->UpdateWindow();
			}

		}
		if (hSelectedItem == m_hPuck)
		{
			CPuckCreateDlg dlg;
			dlg.pDoc = m_pDoc;

			if (dlg.DoModal() == IDOK)
			{
				CWnd* pWnd = AfxGetMainWnd();

				pWnd->Invalidate();
				pWnd->UpdateWindow();
			}

		}
	}
	
	
	*pResult = 0;
}

