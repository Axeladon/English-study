
// MainDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "English.h"
#include "MainDlg.h"
#include "afxdialogex.h"
#include <vector>
#include <algorithm>
#include <string>
#include "MyDialogNewFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    //support DDX/DDV

// realisation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// dialog window CMyDlg

CMyDlg::CMyDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_ENGLISH_DIALOG, pParent)
	, m_static(_T(""))
	, m_enter_word(_T(""))
	, m_static_answer(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	num = -1; //random word number
	on_check = 0;
}

void CMyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WORD, m_static);
	DDX_Text(pDX, IDC_EDIT1, m_enter_word);
	DDX_Text(pDX, IDC_ANSWER, m_static_answer);
}

BEGIN_MESSAGE_MAP(CMyDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_GENERATE, &CMyDlg::OnBnClickedBtnGenerate)
	ON_BN_CLICKED(ID_ADD, &CMyDlg::OnBnClickedAdd)
	ON_COMMAND(ID_FILE_QUIT, &CMyDlg::OnMenuFile_Quit)
	ON_COMMAND(ID_FILE_NEW, &CMyDlg::OnMenuFile_New)
	ON_COMMAND(ID_FILE_LOADWORDS, &CMyDlg::OnMenuFile_LoadFile)
	ON_BN_CLICKED(IDC_CHECK_SHOW_ANSWER, &CMyDlg::OnBnClickedCheckShowAnswer)
	ON_COMMAND(ID_HELP_ABOUT, &CMyDlg::OnHelpAbout)
	ON_COMMAND(ID_FILE_CLOSE, &CMyDlg::OnFileClose)
END_MESSAGE_MAP()


// message handlers CMyDlg

BOOL CMyDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add item "About the program..." in the system menu.

	// IDM_ABOUTBOX must be within the system command.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			//pSysMenu->AppendMenu(MF_SEPARATOR);									 //removed the sub-items from the system menu
			//pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Specifies the icon for this dialog box. The environment does this automatically
	//  if the main application window is not interactive
	SetIcon(m_hIcon, TRUE);			// Large icon
	SetIcon(m_hIcon, FALSE);		// Small icon

	// TODO: add additional initialization

	m_menu.LoadMenu(IDR_MENU1); //bind a menu from resources to a variable
	SetMenu(&m_menu); //display the menu in the program
	bitmap_save.LoadBitmapW(IDB_BITMAP1);
	m_menu.SetMenuItemBitmaps(ID_MFILE_SAVE, MF_BYCOMMAND, &bitmap_save, &bitmap_save);
	GetDlgItem(IDC_CHECK_SHOW_ANSWER)->EnableWindow(FALSE);

	return TRUE;  //return TRUE if focus is not passed to the control
}

void CMyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CMyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // drawing device context

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Align the icon to the center of the client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw an icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}
// The system calls this function to get the cursor display when moving the minimized window.
HCURSOR CMyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMyDlg::add(int arr_size) //function for creating random words
{
	if (on_check == 0)
	{
		word_number.reserve(arr_size);
		for (int i = 0; i < word_number.capacity(); i++) //filling the vector with numbers of fixed-number question words for further sorting
		{
			word_number.insert(word_number.begin() + i, i); 
		}
		srand(int(time(0)));
		std::random_shuffle(word_number.begin(), word_number.end());
		while (num == word_number.front()) //mix again if the last past and first future match
			std::random_shuffle(word_number.begin(), word_number.end());
		num = word_number.front();
		on_check++;
	}
	else if (on_check > 0 && on_check < arr_size)
	{
		num = word_number[on_check];
		on_check++;
	}
	else if (on_check >= arr_size)
	{
		srand(int(time(0)));
		std::random_shuffle(word_number.begin(), word_number.end());
		num = word_number.front();
		on_check = 1;
	}
}

void CMyDlg::OnBnClickedBtnGenerate()
{
	if (words_rus.size() == 0)
	{
		MessageBox(L"No file selected", L"Error", MB_OK | MB_ICONERROR);
	}
	else
	{
		GetDlgItem(IDC_EDIT1)->EnableWindow(TRUE);
		GetDlgItem(ID_ADD)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SHOW_ANSWER)->EnableWindow(TRUE);

		add(words_rus.size());
		if (typefile == 1)
		{
			std::string temp;
			temp = words_rus[num];
			m_static = temp.c_str();
			UpdateData(FALSE);
		}
		else if (typefile == 2)
		{
			std::string temp;
			temp = words_rus[num];
			CString file_path;
			file_path = temp.c_str();

			CImage img; //loading a picture
			img.Load(file_path);
			CDC *dc = AfxGetMainWnd()->GetDC();
			dc->Rectangle(1, 37, 590, 365); //draws a rectangle so that the images do not overlap one another
			HDC hdc = *dc;
			img.Draw(hdc, 2, 38, 587, 324);
		}

		if (IsDlgButtonChecked(IDC_CHECK_SHOW_ANSWER)) //output the response when the checkbox is on
		{
			CString temp;
			temp = words_eng[num].c_str();
			m_static_answer = temp;
			UpdateData(FALSE);
		}
		else
		{
			m_static_answer = " ";
			UpdateData(FALSE);
		}
	}
}

void CMyDlg::EditWord()
{
	GetDlgItem(IDC_BTN_GENERATE)->EnableWindow(TRUE); //on word generation buttons
	GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE); //off input line
	GetDlgItem(ID_ADD)->EnableWindow(FALSE); //off input buttons
	m_static = " "; //remove the word if the word type is changed
	m_static_answer.Empty(); //clear the "program response"
	m_enter_word.Empty(); //clear input line
	UpdateData(FALSE); //output from variables to controls (screen)
	on_check = 0; //reset the counter
	word_number.erase(word_number.begin(), word_number.end()); //completely clean the array
	std::vector<int>(word_number).swap(word_number); //need to free unnecessary memory
}


void CMyDlg::OnBnClickedAdd()
{
	CString temp;
	temp = words_eng[num].c_str();
	CheckWords(temp);
}

void CMyDlg::CheckWords(CString str)
{
	UpdateData(); //write from control to variable

	if (str == m_enter_word)
	{
		m_static_answer = " ";
		m_enter_word.Empty(); //clear input line
		OnBnClickedBtnGenerate(); //generate a new word
	}
	else
	{
		UpdateData(FALSE);
		MessageBox(L"Here is an error, try again", L"hint", MB_OK | MB_ICONEXCLAMATION);
	}
}

//menu handler
void CMyDlg::OnMenuFile_Quit()
{
	CDialogEx::OnCancel();
}

void CMyDlg::OnMenuFile_New()
{
	CMyDialogNewFile dlg;
	dlg.DoModal();
}

void CMyDlg::OnMenuFile_LoadFile()
{
	CFileDialog dlg(TRUE);
	INT_PTR response = dlg.DoModal();
	if (response == IDOK)
	{
		if (!file.Open(dlg.m_ofn.lpstrFile, CFile::modeRead))
		{
			MessageBox(L"File can not be opened");
		}
		else
		{
			//zeroing of vectors for words
			ULONGLONG file_length = file.GetLength(); //get the number of characters in the file (its size)
			int special_char = NULL, counter = NULL;
			char temp_word[100]; //memory area for character formation in words
			UINT readed_char = 2; //number of characters read from file
			char buff_char; //memory area for one character to read from a file

			file.Read(&buff_char, sizeof(buff_char)); //read the first character
			if (buff_char == '/') //reading special characters
			{
				file.Read(&buff_char, sizeof(buff_char)); //read the digit (file format)
				if (buff_char == '1')
					typefile = 1;
				else if (buff_char == '2')
					typefile = 2;
			}
			do
			{
				file.Read(&buff_char, sizeof(buff_char)); //single character reading
				if (buff_char == '|')
				{
					special_char++;
					readed_char++;
					if (special_char != 1)
					{
						std::string str_temp; //word formation 
						for (int i = 0; i < counter; i++)
						{
							str_temp += temp_word[i];
						}
						if (special_char == 2) //rus
						{
							words_rus.insert(words_rus.end(), str_temp);
						}
						else if (special_char == 3) //eng
						{
							words_eng.insert(words_eng.end(), str_temp);
							special_char = 0;
						}
						counter = 0; //if a special character has been encountered, it means that you have switched to another language 
						//and you need to reset the counter of letters to zero
					}
				}
				else if (buff_char == '\r' || buff_char == '\n')
				{
					readed_char++;
				}
				else
				{
					readed_char++;
					temp_word[counter] = buff_char;
					counter++;
				}
			} while (file_length != readed_char);
		}
		m_menu.ModifyMenuW(ID_FILE_CLOSE, MF_BYCOMMAND | MF_ENABLED, ID_FILE_CLOSE, L"Close"); //on menu close

		m_menu.ModifyMenuW(ID_FILE_OPEN32771, MF_BYCOMMAND | MF_DISABLED, ID_FILE_OPEN32771, L"Open"); //off menu open
		m_menu.ModifyMenuW(ID_FILE_NEW, MF_BYCOMMAND | MF_DISABLED, ID_FILE_NEW, L"New"); //off menu new
		m_menu.ModifyMenuW(ID_FILE_LOADWORDS, MF_BYCOMMAND | MF_DISABLED, ID_FILE_LOADWORDS, L"Load file"); //off menu load
	}
	else if (response == IDCANCEL)
	{
		MessageBox(L"Could not upload file", L"Error", MB_OK | MB_ICONERROR);
	}
}


void CMyDlg::OnBnClickedCheckShowAnswer() //output the answer when clicking on the checkbox
{
	//TODO click where not load file
	if (IsDlgButtonChecked(IDC_CHECK_SHOW_ANSWER))
	{
		CString temp;
		temp = words_eng[num].c_str();
		m_static_answer = temp;
		UpdateData(FALSE);
	}
	else
	{
		m_static_answer = " ";
		UpdateData(FALSE);
	}
}


void CMyDlg::OnHelpAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CMyDlg::OnFileClose()
{
	file.Close(); //close file

	words_rus.clear(); //clears an array
	std::vector<std::string>(words_rus).swap(words_rus); //frees reserved memory
	words_eng.clear(); //clears an array
	std::vector<std::string>(words_eng).swap(words_eng); //frees reserved memory
	word_number.clear();
	std::vector<int>(word_number).swap(word_number); // frees reserved memory

	on_check = 0; //you need to feed "random" numbers
	m_static = " ";
	m_static_answer = " ";
	UpdateData(FALSE);

	m_menu.ModifyMenuW(ID_FILE_OPEN32771, MF_BYCOMMAND | MF_ENABLED, ID_FILE_OPEN32771, L"Open"); //on menu open
	m_menu.ModifyMenuW(ID_FILE_NEW, MF_BYCOMMAND | MF_ENABLED, ID_FILE_NEW, L"New"); //on menu new
	m_menu.ModifyMenuW(ID_FILE_LOADWORDS, MF_BYCOMMAND | MF_ENABLED, ID_FILE_LOADWORDS, L"Load file"); //on menu load
	m_menu.ModifyMenuW(ID_FILE_CLOSE, MF_BYCOMMAND | MF_DISABLED, ID_FILE_CLOSE, L"Close"); //off menu close
}
