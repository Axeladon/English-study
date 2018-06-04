
// MainDlg.h : ���� ���������
//
#include <vector>

#pragma once


// ���������� ���� CMyDlg
class CMyDlg : public CDialogEx
{
// ��������
public:
	CMyDlg(CWnd* pParent = NULL);	// ����������� �����������

// ������ ����������� ����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ENGLISH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// ��������� DDX/DDV


// ����������
protected:
	HICON m_hIcon;

	// ��������� ������� ����� ���������
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

	afx_msg void EditWord(); //������� ��� ��������� ���� ����
	afx_msg void CheckWords(CString str);

	CMenu m_menu;
	CBitmap bitmap_save;
	CFile file; //���������� ������� ������ ��� ������ � ������� � MFC
	

	afx_msg void OnMenuFile_Quit();
	afx_msg void OnMenuFile_New();
	afx_msg void OnMenuFile_LoadFile();
	afx_msg void OnBnClickedCheckShowAnswer();
	afx_msg void OnHelpAbout();
	afx_msg void OnFileClose();

	//---------------------------------------------my
	int num; //����� ���������� �����
	int on_check; //��� ��������, 0 = begin
	int typefile; //����������� ���� ����� (� ���������� � ���)
	std::vector<int> word_number;
	std::vector<std::string> words_rus;
	std::vector<std::string> words_eng;

	void add(int arr_size); //������� ��� �������� ��������� ����
};