// MyDialogNewFile.cpp: файл реализации
//

#include "stdafx.h"
#include "English.h"
#include "MyDialogNewFile.h"
#include "afxdialogex.h"


// диалоговое окно CMyDialogNewFile

IMPLEMENT_DYNAMIC(CMyDialogNewFile, CDialogEx)

CMyDialogNewFile::CMyDialogNewFile(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MENU_NEW_FILE, pParent)
{
	
}

CMyDialogNewFile::~CMyDialogNewFile()
{
}

void CMyDialogNewFile::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CMyDialogNewFile, CDialogEx)
END_MESSAGE_MAP()


// обработчики сообщений CMyDialogNewFile
