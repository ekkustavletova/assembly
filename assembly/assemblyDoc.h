
// assemblyDoc.h: интерфейс класса CassemblyDoc 
//


#pragma once
class MyTreeView;
class CassemblyView;

struct Seal {
	int RO;
	int RI;
	int Length;
};

struct Nut {
	int RO;
	int HexagonThick;
	float HexagonR;
};

struct Puck {
	int RO;
	int Thick;
};

class CassemblyDoc : public CDocument
{
protected: // создать только из сериализации
	CassemblyDoc() noexcept;
	DECLARE_DYNCREATE(CassemblyDoc)

// Атрибуты
public:
	int m_X, m_Y;

	CassemblyView* pView;
	MyTreeView* pTreeView;

	bool m_bAssembly, m_bOilSealSocket, m_bPressureNut, m_bPuck;

	Seal SealSizes[5] = {
		Seal{10, 7, 23},
		Seal{12, 9, 25},
		Seal{14, 11, 27},
		Seal{16, 13, 29},
		Seal{18, 15, 31}
	};

	int m_SealRO = SealSizes[0].RO;
	int m_SealRI = SealSizes[0].RI;
	int m_SealLength = SealSizes[0].Length;
	

	Nut NutSizes[5] = {
		Nut {8, 5, 21.9},
		Nut {10, 9, 25.4},
		Nut {12, 11, 36.9},
		Nut {14, 13, 41.6},
		Nut {18, 15, 53}
	};

	int m_NutRO = NutSizes[0].RO;
	int m_NutHexagonThick = NutSizes[0].HexagonThick;
	int m_NutHexagonR = NutSizes[0].HexagonR;



	Puck PuckSizes[5] = {
		Puck{5, 1},
		Puck{1, 1},
		Puck{1, 1},
		Puck{1, 1},
		Puck{1, 1}
	};

	int m_PuckRI = 7;
	int m_PuckRO = PuckSizes[0].RO;
	int m_PuckThick = PuckSizes[0].Thick;


	int SizesLength = 5;

	//int m_NutR;
	//int m_PuckR;



// Операции
public:
	void CreateOilSealSocket();
	void CreatePressureNut();
	void CreatePuck();
	void CreateAssemble();

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CassemblyDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnUpdateAssemblyoilsealsocket(CCmdUI* pCmdUI);
	afx_msg void OnAssemblypressurenut();
	afx_msg void OnUpdateAssemblypressurenut(CCmdUI* pCmdUI);
	afx_msg void OnAssemblypuck();
	afx_msg void OnUpdateAssemblypuck(CCmdUI* pCmdUI);
	afx_msg void OnDlgSealSet();
	afx_msg void OnBtnOilsealsocketCreate();
	afx_msg void OnSealCreate();
	afx_msg void OnNutCreate();
	afx_msg void OnDlgNutSet();
	afx_msg void OnDlgPuckSet();
	afx_msg void OnPuckCreate();
	afx_msg void OnAssembleCreate();
	afx_msg void OnDlgAssembleSet();
};
