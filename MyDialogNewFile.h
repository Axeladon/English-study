#pragma once


// диалоговое окно CMyDialogNewFile

class CMyDialogNewFile : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogNewFile)

public:
	CMyDialogNewFile(CWnd* pParent = NULL);   // стандартный конструктор
	virtual ~CMyDialogNewFile();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU_NEW_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
};