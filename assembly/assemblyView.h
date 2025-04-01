
// assemblyView.h: интерфейс класса CassemblyView
//

#pragma once
#include "assemblyDoc.h"
#include "COilSealSocketCreateDlg.h"

class CassemblyView : public CView
{
protected: // создать только из сериализации
	CassemblyView() noexcept;
	DECLARE_DYNCREATE(CassemblyView)

// Атрибуты
public:
	CBitmap m_bmpSeal;





	CassemblyDoc* GetDocument() const;

	COilSealSocketCreateDlg m_OilSealSocketCreate;
// Операции
public:

	int ImageCreate(CDC* pDC, int Width, CString name_file);

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Реализация
public:
	virtual ~CassemblyView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // версия отладки в assemblyView.cpp
inline CassemblyDoc* CassemblyView::GetDocument() const
   { return reinterpret_cast<CassemblyDoc*>(m_pDocument); }
#endif

