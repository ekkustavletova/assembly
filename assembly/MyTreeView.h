#pragma once
#include "afxcview.h"

// Просмотр MyTreeView
class CassemblyDoc;

class MyTreeView : public CTreeView
{
	DECLARE_DYNCREATE(MyTreeView)

protected:
	MyTreeView();           // защищенный конструктор, используемый при динамическом создании
	virtual ~MyTreeView();

public:
	CassemblyDoc* m_pDoc;

	HTREEITEM m_hAssembly, m_hOilSealSocket, m_hPressureNut, m_hPuck;

	void FillTree();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
//	afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult);
};


