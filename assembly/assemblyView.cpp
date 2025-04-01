
// assemblyView.cpp: реализация класса CassemblyView
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "assembly.h"
#endif

#include "assemblyDoc.h"
#include "assemblyView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CassemblyView

IMPLEMENT_DYNCREATE(CassemblyView, CView)

BEGIN_MESSAGE_MAP(CassemblyView, CView)
	// Стандартные команды печати
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// Создание или уничтожение CassemblyView

CassemblyView::CassemblyView() noexcept
{
	// TODO: добавьте код создания

}

CassemblyView::~CassemblyView()
{
}

BOOL CassemblyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CassemblyView

int CassemblyView::ImageCreate(CDC* pDC, int Width, CString name_file)
{

	CImage image;
	image.Load(name_file);

	if (image.IsNull())
	{
		AfxMessageBox(L"Ошибка загрузки картинки");
		return 10;
	}

	int imageWidth = image.GetWidth();		//Ширина картинки
	int imageHeight = image.GetHeight();	//Высота картинки

	image.StretchBlt
	(
		pDC->GetSafeHdc(), Width / 2.f - imageWidth / 2.f, 0,
		imageWidth, imageHeight, 0, 0,
		imageWidth, imageHeight, SRCCOPY
	);

	return imageHeight;
}

void CassemblyView::OnDraw(CDC* pDC)
{
	//CassemblyView::OnDraw(pDC);

	CassemblyDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);

	int Height = clientRect.Height();
	int Width = clientRect.Width();

	// TODO: добавьте здесь код отрисовки для собственных данных

	if (pDoc->m_bAssembly) {
		//pDC->LineTo(500, 500);


		int imageHeight = ImageCreate(pDC, Width, L"res\\assemble.bmp");
	}
	if (pDoc->m_bOilSealSocket) {
		/*pDC->MoveTo(0, 250);
		pDC->LineTo(250, 250);*/
		
		//m_bmpSeal.LoadBitmapW(BMP_SEAL);
		//// Создание совместимого контекста устройства
		//CDC memDC;
		//memDC.CreateCompatibleDC(pDC);

		//// Выбор изображения в контекст устройства
		//CBitmap* pOldBitmap = memDC.SelectObject(&m_bmpSeal);

		//// Получение размеров изображения
		//BITMAP bm;
		//m_bmpSeal.GetBitmap(&bm);

		//// Отображение изображения
		//pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &memDC, 0, 0, SRCCOPY);

		//// Восстановление старого объекта
		//memDC.SelectObject(pOldBitmap);

 		int imageHeight = ImageCreate(pDC, Width, L"res\\seal.bmp");
	}
	if (pDoc->m_bPressureNut) {
		/*pDC->MoveTo(0, 125);
		pDC->LineTo(125, 125);*/


		int imageHeight = ImageCreate(pDC, Width, L"res\\nut.bmp");
	}
	if (pDoc->m_bPuck) {
		/*pDC->MoveTo(0, 50);
		pDC->LineTo(50, 50);*/


		int imageHeight = ImageCreate(pDC, Width, L"res\\puck.bmp");
	}
}


// Печать CassemblyView

BOOL CassemblyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// подготовка по умолчанию
	return DoPreparePrinting(pInfo);
}

void CassemblyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте дополнительную инициализацию перед печатью
}

void CassemblyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: добавьте очистку после печати
}


// Диагностика CassemblyView

#ifdef _DEBUG
void CassemblyView::AssertValid() const
{
	CView::AssertValid();
}

void CassemblyView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CassemblyDoc* CassemblyView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CassemblyDoc)));
	return (CassemblyDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CassemblyView


void CassemblyView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного

	ClientToScreen(&point);
	CCmdUI state;

	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(3);

	state.m_pMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < state.m_nIndexMax; i++)
	{
		state.m_nIndex = i;
		state.m_nID = pMenu->GetMenuItemID(i);
		state.DoUpdate(this, FALSE);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	CView::OnRButtonDown(nFlags, point);

}
