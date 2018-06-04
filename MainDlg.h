
// MainDlg.h : файл заголовка
//
#include <vector>

#pragma once


// диалоговое окно CMyDlg
class CMyDlg : public CDialogEx
{
// Создание
public:
	CMyDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENGLISH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_static;
	afx_msg void OnBnClickedBtnGenerate();
	CString m_enter_word;
	afx_msg void OnBnClickedAdd();
	CString m_static_answer;

	afx_msg void EditWord(); //функция для изменения типа слов
	afx_msg void CheckWords(CString str);

	CMenu m_menu;
	CBitmap bitmap_save;
	CFile file; //объявление объекта класса для работы с файлами в MFC
	

	afx_msg void OnMenuFile_Quit();
	afx_msg void OnMenuFile_New();
	afx_msg void OnMenuFile_LoadFile();
	afx_msg void OnBnClickedCheckShowAnswer();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileClose();

	//---------------------------------------------my
	int num; //номер рандомного слова
	int on_check; //для проверки, 0 = begin
	int typefile; //определение типа файла (с картинкими и без)
	std::vector<int> word_number;
	std::vector<std::string> words_rus;
	std::vector<std::string> words_eng;

	void add(int arr_size); //функция для создания рандомных слов
};