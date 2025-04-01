
// assemblyDoc.cpp: реализация класса CassemblyDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "assembly.h"
#endif


#include "assemblyDoc.h"
#include "COilSealSocketCreateDlg.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "MyTreeView.h"
#include "assemblyView.h"

#include "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\Include\ksConstants.h"
#include "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\Include\ksConstants3D.h"
#include <string>
#include "CPressureNutCreateDlg.h"
#include "CPuckCreateDlg.h"

#import "C:\Program Files\ASCON\KOMPAS-3D v23 Study\SDK\lib\kAPI5.tlb"

//#include <string>


using namespace Kompas6API5;

KompasObjectPtr pKompasApp5;
// CassemblyDoc

IMPLEMENT_DYNCREATE(CassemblyDoc, CDocument)

BEGIN_MESSAGE_MAP(CassemblyDoc, CDocument)
	ON_UPDATE_COMMAND_UI(ID_assemblyOilSealSocket, &CassemblyDoc::OnUpdateAssemblyoilsealsocket)
	ON_COMMAND(ID_assemblyPressureNut, &CassemblyDoc::OnAssemblypressurenut)
	ON_UPDATE_COMMAND_UI(ID_assemblyPressureNut, &CassemblyDoc::OnUpdateAssemblypressurenut)
	ON_COMMAND(ID_assemblyPuck, &CassemblyDoc::OnAssemblypuck)
	ON_UPDATE_COMMAND_UI(ID_assemblyPuck, &CassemblyDoc::OnUpdateAssemblypuck)
	ON_COMMAND(DLG_SEAL_SET, &CassemblyDoc::OnDlgSealSet)
	ON_COMMAND(BTN_OILSEALSOCKET_CREATE, &CassemblyDoc::OnBtnOilsealsocketCreate)
	ON_COMMAND(ID_SEAL_CREATE, &CassemblyDoc::OnSealCreate)
	ON_COMMAND(ID_NUT_CREATE, &CassemblyDoc::OnNutCreate)
	ON_COMMAND(DLG_NUT_SET, &CassemblyDoc::OnDlgNutSet)
	ON_COMMAND(DLG_PUCK_SET, &CassemblyDoc::OnDlgPuckSet)
	ON_COMMAND(ID_PUCK_CREATE, &CassemblyDoc::OnPuckCreate)
	ON_COMMAND(ID_ASSEMBLE_CREATE, &CassemblyDoc::OnAssembleCreate)
//	ON_COMMAND(DLG_ASSEMBLE_CREATE, &CassemblyDoc::OnDlgAssembleCreate)
ON_COMMAND(DLG_ASSEMBLE_SET, &CassemblyDoc::OnDlgAssembleSet)
END_MESSAGE_MAP()


// Создание или уничтожение CassemblyDoc

CassemblyDoc::CassemblyDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CassemblyDoc::~CassemblyDoc()
{
}

void CassemblyDoc::CreateOilSealSocket()
{
	ksDocument3DPtr pDoc;
	CComPtr<IUnknown> pKompasAppUnk = nullptr;

	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pDoc = pKompasApp5->ActiveDocument3D();
	ksPartPtr pPart = pDoc->GetPart(pTop_Part);
	ksDocument2DPtr p2DDoc;
	// Гнездо Сальника

	ksEntityPtr proll_Sketch = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = proll_Sketch->GetDefinition();
	pSketch1Def->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	proll_Sketch->Create();

	p2DDoc = pSketch1Def->BeginEdit();
	p2DDoc->ksLineSeg(0, 4, 0, 6, 1);
	p2DDoc->ksLineSeg(0, 6, 5, 6, 1);
	p2DDoc->ksLineSeg(5, 6, 5, m_SealRO, 1);
	p2DDoc->ksLineSeg(5, m_SealRO, m_SealLength, m_SealRO, 1);
	p2DDoc->ksLineSeg(m_SealLength, m_SealRO, m_SealLength, m_SealRI, 1);
	p2DDoc->ksLineSeg(m_SealLength, m_SealRI, 7, m_SealRI, 1);
	p2DDoc->ksLineSeg(7, m_SealRI, 7, 4, 1);
	p2DDoc->ksLineSeg(7, 4, 0, 4, 1);
	p2DDoc->ksLineSeg(0, 0, 30, 0, 3);
	pSketch1Def->EndEdit();

	ksEntityPtr pRotate1 = pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRot1Def = pRotate1->GetDefinition();
	pRot1Def->SetSketch(proll_Sketch);
	pRot1Def->SetSideParam(TRUE, 360);
	pRotate1->Create();

	ksEntityPtr pThread = pPart->NewEntity(o3d_thread);
	ksThreadDefinitionPtr pThreadDef = pThread->GetDefinition();
	pThreadDef->Putlength(9);
	pThreadDef->PutautoDefinDr(TRUE);
	ksEntityCollectionPtr pFaces = pPart->EntityCollection(o3d_face);
	for (int i = 0; i < pFaces->GetCount(); i++)
	{
		ksEntityPtr face = pFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();
		if (def->GetOwnerEntity() == pRotate1)
		{
			if (def->IsCylinder()) {
				double h = 16, r = 7;
				def->GetCylinderParam(&h, &r);
				if (r == 7) {
					face->Putname(L"SCREW_BODY");
					face->Update();
					pThreadDef->SetBaseObject(face);
				}
			}
		}
	}
	pThread->Create();


	ksEntityPtr pChamfer1 = pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer1Def = pChamfer1->GetDefinition();
	pChamfer1Def->tangent = true;
	pChamfer1Def->SetChamferParam(true, 1, 1);
	ksEntityCollectionPtr pEdges = pPart->EntityCollection(o3d_edge);
	ksEntityCollectionPtr pChamfers = pChamfer1Def->array();
	pChamfers->Clear();
	pEdges->SelectByPoint(0, 4, 0);
	pChamfers->Add(pEdges->GetByIndex(0));
	pChamfer1->Create();

	ksEntityPtr pChamfer2 = pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer2Def = pChamfer2->GetDefinition();
	pChamfer2Def->tangent = true;
	pChamfer2Def->SetChamferParam(true, 1, 1);
	pEdges = pPart->EntityCollection(o3d_edge);
	pChamfers = pChamfer2Def->array();
	pChamfers->Clear();
	pEdges->SelectByPoint(m_SealLength, 7, 0);
	pChamfers->Add(pEdges->GetByIndex(0));
	pChamfer2->Create();


	CString path = CString("C:\\Users\\Ксения\\Desktop\\ВУЗ\\Прога в САПР\\2 курс\\Курсовая\\assembly\\assembly\\Детали\\Seal.m3d");
	CString name = CString("Seal.m3d");

	pDoc->fileName = _bstr_t(name);
	pDoc->SaveAs(_bstr_t(path));
}

void CassemblyDoc::CreatePressureNut()
{
	ksDocument3DPtr pDoc;
	CComPtr<IUnknown> pKompasAppUnk = nullptr;

	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pDoc = pKompasApp5->ActiveDocument3D();
	ksPartPtr pPart = pDoc->GetPart(pTop_Part);
	ksDocument2DPtr p2DDoc;

	ksEntityPtr pg_Sketch = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch1Def = pg_Sketch->GetDefinition();
	pSketch1Def->SetPlane(pPart->GetDefaultEntity(o3d_planeYOZ));
	pg_Sketch->Create();

	p2DDoc = pSketch1Def->BeginEdit();
	p2DDoc->ksLineSeg(0, 0, 6, 0, 1);
	p2DDoc->ksLineSeg(6, 0, 6, 3, 1);
	p2DDoc->ksLineSeg(6, 3, m_NutRO, 3, 1);
	p2DDoc->ksLineSeg(m_NutRO, 3, m_NutRO, 13, 1);
	p2DDoc->ksLineSeg(m_NutRO, 13, 0, 13, 1);
	p2DDoc->ksLineSeg(0, 13, 0, 0, 1);
	p2DDoc->ksLineSeg(0, 0, 0, 30, 3);
	pSketch1Def->EndEdit();

	ksEntityPtr pRotate1 = pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRot1Def = pRotate1->GetDefinition();
	pRot1Def->SetSketch(pg_Sketch);
	pRot1Def->SetSideParam(TRUE, 360);
	pRotate1->Create();

	double R = m_NutHexagonR;
	double r = R * sqrt(3) / 2;

	double x1 = 0;
	double y1 = R / 2;
	double x2 = r / 2;
	double y2 = R / 4;
	double x3 = r / 2;
	double y3 = -R / 4;
	double x4 = 0;
	double y4 = -R / 2;
	double x5 = -r / 2;
	double y5 = -R / 4;
	double x6 = -r / 2;
	double y6 = R / 4;
	ksEntityPtr pSketch2 = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch2Def = pSketch2->GetDefinition();
	pSketch2Def->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pSketch2->Create();
	p2DDoc = pSketch2Def->BeginEdit();
	p2DDoc->ksLineSeg(x1, y1, x2, y2, 1);
	p2DDoc->ksLineSeg(x2, y2, x3, y3, 1);
	p2DDoc->ksLineSeg(x3, y3, x4, y4, 1);
	p2DDoc->ksLineSeg(x4, y4, x5, y5, 1);
	p2DDoc->ksLineSeg(x5, y5, x6, y6, 1);
	p2DDoc->ksLineSeg(x6, y6, x1, y1, 1);
	pSketch2Def->EndEdit();

	ksEntityPtr pExtrude1 = pPart->NewEntity(o3d_bossExtrusion);
	ksBossExtrusionDefinitionPtr Extrude1Def = pExtrude1->GetDefinition();
	Extrude1Def->SetSketch(pSketch2);
	Extrude1Def->PutdirectionType(dtNormal);
	Extrude1Def->SetSideParam(true, etBlind, m_NutHexagonThick, 0, true);
	pExtrude1->Create();

	ksEntityPtr pPlane1 = pPart->NewEntity(o3d_planeOffset);
	ksPlaneOffsetDefinitionPtr pSketch3 = pPlane1->GetDefinition();
	pSketch3->direction = false;
	pSketch3->offset = -17 + 15;
	pSketch3->SetPlane(pPart->GetDefaultEntity(o3d_planeXOZ));
	pPlane1->Create();

	ksEntityPtr p3Sketch = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketch3Def = p3Sketch->GetDefinition();
	pSketch3Def->SetPlane(pPlane1);
	p3Sketch->Create();
	p2DDoc = pSketch3Def->BeginEdit();
	p2DDoc->ksCircle(0, 0, 5, 1);
	pSketch3Def->EndEdit();

	ksEntityPtr p2Extrude = pPart->NewEntity(o3d_cutExtrusion);
	ksCutExtrusionDefinitionPtr Extrude2Def = p2Extrude->GetDefinition();
	Extrude2Def->SetSketch(p3Sketch);
	Extrude2Def->PutdirectionType(dtNormal);
	Extrude2Def->SetSideParam(true, etBlind, 15, 0, true);
	p2Extrude->Create();

	ksEntityPtr pThread = pPart->NewEntity(o3d_thread);
	ksThreadDefinitionPtr pThreadDef = pThread->GetDefinition();
	pThreadDef->PutallLength(TRUE);
	pThreadDef->PutautoDefinDr(TRUE);
	ksEntityCollectionPtr pFaces = pPart->EntityCollection(o3d_face);
	for (int i = 0; i < pFaces->GetCount(); i++)
	{
		ksEntityPtr face = pFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();
		if (def->GetOwnerEntity() == pRotate1)
		{
			if (def->IsCylinder()) {
				double h = 10, r = 8;
				def->GetCylinderParam(&h, &r);
				if (r == 8) {
					face->Putname(L"SCREW_BODY");
					face->Update();
					pThreadDef->SetBaseObject(face);
				}
			}
		}
	}
	pThread->Create();

	ksEntityPtr pChamfer1 = pPart->NewEntity(o3d_chamfer);
	ksChamferDefinitionPtr pChamfer1Def = pChamfer1->GetDefinition();
	pChamfer1Def->tangent = true;
	pChamfer1Def->SetChamferParam(true, 1, 1);
	ksEntityCollectionPtr pEdges = pPart->EntityCollection(o3d_edge);
	ksEntityCollectionPtr pChamfers = pChamfer1Def->array();
	pChamfers->Clear();
	pEdges->SelectByPoint(0, -13, 8);
	pChamfers->Add(pEdges->GetByIndex(0));
	pChamfer1->Create();

	CString path = CString("C:\\Users\\Ксения\\Desktop\\ВУЗ\\Прога в САПР\\2 курс\\Курсовая\\assembly\\assembly\\Детали\\Nut.m3d");
	CString name = CString("Nut.m3d");

	pDoc->fileName = _bstr_t(name);
	pDoc->SaveAs(_bstr_t(path));
}

void CassemblyDoc::CreatePuck() 
{
	ksDocument3DPtr pDoc;
	CComPtr<IUnknown> pKompasAppUnk = nullptr;

	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pDoc = pKompasApp5->ActiveDocument3D();
	ksPartPtr pPart = pDoc->GetPart(pTop_Part);
	ksDocument2DPtr p2DDoc;

	ksEntityPtr pSketch = pPart->NewEntity(o3d_sketch);
	ksSketchDefinitionPtr pSketchDef = pSketch->GetDefinition();
	pSketchDef->SetPlane(pPart->GetDefaultEntity(o3d_planeXOY));
	pSketch->Create();

	auto X1 = m_PuckRO;
	auto X2 = m_PuckRI;
	auto Y = m_PuckThick;

	p2DDoc = pSketchDef->BeginEdit();
	p2DDoc->ksLineSeg(X1, 0, X1, Y, 1);
	p2DDoc->ksLineSeg(X1, Y, X2, Y, 1);
	p2DDoc->ksLineSeg(X2, Y, X2, 0, 1);
	p2DDoc->ksLineSeg(X2, 0, X1, 0, 1);

	p2DDoc->ksLineSeg(0, 10, 0, 0, 3);
	pSketchDef->EndEdit();

	//вращение
	ksEntityPtr pRot = pPart->NewEntity(o3d_bossRotated);
	ksBossRotatedDefinitionPtr pRotDef = pRot->GetDefinition();
	pRotDef->SetSketch(pSketch);
	pRotDef->SetSideParam(FALSE, 360);
	pRot->Create();

	ksEntityCollectionPtr flFaces = pPart->EntityCollection(o3d_face);
	for (int i = 0; i < flFaces->GetCount(); i++) {
		ksEntityPtr face = flFaces->GetByIndex(i);
		ksFaceDefinitionPtr def = face->GetDefinition();
		if (def->GetOwnerEntity() == pRot) {
			if (def->IsPlanar()) {
				face->Putname("Face4Assembly3");
				face->Update();
				continue;
			}
			if (def->IsCylinder()) {
				double h, r;
				def->GetCylinderParam(&h, &r);
				if (r == m_PuckRI) {
					face->Putname("Cylinder4Assembly3");
					face->Update();
				}
			}
		}
	}


	CString path = CString("C:\\Users\\Ксения\\Desktop\\ВУЗ\\Прога в САПР\\2 курс\\Курсовая\\assembly\\assembly\\Детали\\Puck.m3d");
	CString name = CString("Puck.m3d");

	pDoc->fileName = _bstr_t(name);
	pDoc->SaveAs(_bstr_t(path));

}

void CassemblyDoc::CreateAssemble()
{
	ksDocument3DPtr pDoc;
	CComPtr<IUnknown> pKompasAppUnk = nullptr;

	if (!pKompasApp5)
	{
		// Получаем CLSID для Компас
		CLSID InvAppClsid;
		HRESULT hRes = CLSIDFromProgID(L"Kompas.Application.5", &InvAppClsid);
		if (FAILED(hRes)) {
			pKompasApp5 = nullptr;
			return;
		}

		// Проверяем есть ли запущенный экземпляр Компас
		//если есть получаем IUnknown
		hRes = ::GetActiveObject(InvAppClsid, NULL, &pKompasAppUnk);
		if (FAILED(hRes)) {
			// Приходится запускать Компас самим так как работающего нет
			// Также получаем IUnknown для только что запущенного приложения Компас
			TRACE(L"Could not get hold of an active Inventor, will start a new session\n");
			hRes = CoCreateInstance(InvAppClsid, NULL, CLSCTX_LOCAL_SERVER, __uuidof(IUnknown), (void**)&pKompasAppUnk);
			if (FAILED(hRes)) {
				pKompasApp5 = nullptr;
				return;
			}
		}

		// Получаем интерфейс приложения Компас
		hRes = pKompasAppUnk->QueryInterface(__uuidof(KompasObject), (void**)&pKompasApp5);
		if (FAILED(hRes)) {
			return;
		}
	}

	pKompasApp5->Visible = true;

	pDoc = pKompasApp5->Document3D();
	pDoc->Create(false, true);
	pDoc = pKompasApp5->ActiveDocument3D();
	ksPartPtr pPart = pDoc->GetPart(pTop_Part);
	ksDocument2DPtr p2DDoc;
	
	CString path = CString("C:\\Users\\Ксения\\Desktop\\ВУЗ\\Прога в САПР\\2 курс\\Курсовая\\assembly\\assembly\\Детали\\Assemble.m3d");
	CString name = CString("Assemble.m3d");

	pDoc->fileName = _bstr_t(name);
	pDoc->SaveAs(_bstr_t(path));

}

BOOL CassemblyDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	m_bAssembly = m_bOilSealSocket = m_bPressureNut = m_bPuck = false;

	pTreeView->FillTree();
	pView->m_bmpSeal.LoadBitmapW(BMP_SEAL);

	return TRUE;
}




// Сериализация CassemblyDoc

void CassemblyDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CassemblyDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CassemblyDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CassemblyDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CassemblyDoc

#ifdef _DEBUG
void CassemblyDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CassemblyDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CassemblyDoc
void CassemblyDoc::OnUpdateAssemblyoilsealsocket(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bOilSealSocket);
}


void CassemblyDoc::OnAssemblypressurenut()
{
	// TODO: добавьте свой код обработчика команд
	m_bPressureNut = !m_bPressureNut;
	pView->Invalidate();

	pTreeView->FillTree();
}


void CassemblyDoc::OnUpdateAssemblypressurenut(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bPressureNut);
}


void CassemblyDoc::OnAssemblypuck()
{
	// TODO: добавьте свой код обработчика команд
	m_bPuck = !m_bPuck;
	pView->Invalidate();

	pTreeView->FillTree();
}


void CassemblyDoc::OnUpdateAssemblypuck(CCmdUI* pCmdUI)
{
	// TODO: добавьте свой код обработчика ИП обновления команд
	pCmdUI->SetCheck(m_bPuck);
}


void CassemblyDoc::OnDlgSealSet()
{
	COilSealSocketCreateDlg dlg;
	dlg.pDoc = this;

	if (dlg.DoModal() == IDOK)
	{
		CWnd* pWnd = AfxGetMainWnd();

		pWnd->Invalidate();
		pWnd->UpdateWindow();
	}
}


void CassemblyDoc::OnBtnOilsealsocketCreate()
{
}


void CassemblyDoc::OnSealCreate()
{
	CreateOilSealSocket();
}


void CassemblyDoc::OnNutCreate()
{
	// TODO: добавьте свой код обработчика команд
	CreatePressureNut();
}


void CassemblyDoc::OnDlgNutSet()
{
	// TODO: добавьте свой код обработчика команд
	CPressureNutCreateDlg dlg;
	dlg.pDoc = this;

	if (dlg.DoModal() == IDOK)
	{
		CWnd* pWnd = AfxGetMainWnd();

		pWnd->Invalidate();
		pWnd->UpdateWindow();
	}
}


void CassemblyDoc::OnDlgPuckSet()
{
	// TODO: добавьте свой код обработчика команд
	CPuckCreateDlg dlg;
	dlg.pDoc = this;

	if (dlg.DoModal() == IDOK)
	{
		CWnd* pWnd = AfxGetMainWnd();

		pWnd->Invalidate();
		pWnd->UpdateWindow();
	}
}


void CassemblyDoc::OnPuckCreate()
{
	// TODO: добавьте свой код обработчика команд
	CreatePuck();
}


void CassemblyDoc::OnAssembleCreate()
{
	// TODO: добавьте свой код обработчика команд
	CreateAssemble();
}


void CassemblyDoc::OnDlgAssembleSet()
{
	// TODO: добавьте свой код обработчика команд
}
