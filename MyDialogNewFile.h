#pragma once


// ���������� ���� CMyDialogNewFile

class CMyDialogNewFile : public CDialogEx
{
	DECLARE_DYNAMIC(CMyDialogNewFile)

public:
	CMyDialogNewFile(CWnd* pParent = NULL);   // ����������� �����������
	virtual ~CMyDialogNewFile();

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MENU_NEW_FILE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // ��������� DDX/DDV

	DECLARE_MESSAGE_MAP()
};