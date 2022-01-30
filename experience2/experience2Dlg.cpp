
// experience2Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "experience2.h"
#include "experience2Dlg.h"
#include "afxdialogex.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// Cexperience2Dlg 对话框



Cexperience2Dlg::Cexperience2Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXPERIENCE2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cexperience2Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, regularExp_edit);
    DDX_Control(pDX, IDC_LIST2, nfa_list);
    DDX_Control(pDX, IDC_LIST3, dfa_list);
    DDX_Control(pDX, IDC_LIST4, minimized_dfa_list);
    DDX_Control(pDX, IDC_EDIT3, code_edit);
}

BEGIN_MESSAGE_MAP(Cexperience2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON2, &Cexperience2Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &Cexperience2Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &Cexperience2Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// Cexperience2Dlg 消息处理程序

BOOL Cexperience2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void Cexperience2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cexperience2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cexperience2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cexperience2Dlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
    //文件类型过滤
    const TCHAR pszFilter[] = _T("Any Files (*.*)|*.*|");
    //第一个参数为TRUE是打开文件，为FALSE是文件另存为
    CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        pszFilter, this);

    dlg.m_ofn.lpstrInitialDir = _T("c:\\WINDOWS\\"); //设置对话框默认呈现的路径
    CString cstrFilePath;
    if (dlg.DoModal() == IDOK)
    {
        //获取选中的文件的路径
        cstrFilePath = dlg.GetPathName();
    }
    string strFilePath;
    strFilePath = (LPCSTR)(CStringA)(cstrFilePath);
    ifstream in;
    in.open(strFilePath);
    string file_regular;
    in >> file_regular;
    CString cstr_file_regular(file_regular.c_str());
    regularExp_edit.SetWindowTextW(cstr_file_regular);
    in.close();
}


void Cexperience2Dlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
    //文件类型过滤
    const TCHAR pszFilter[] = _T("Any Files (*.*)|*.*|");
    //第一个参数为TRUE是打开文件，为FALSE是文件另存为
    CFileDialog dlg(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
        pszFilter, this);

    dlg.m_ofn.lpstrInitialDir = _T("c:\\WINDOWS\\"); //设置对话框默认呈现的路径
    CString cstrFilePath;
    if (dlg.DoModal() == IDOK)
    {
        //获取选中的文件的路径
        cstrFilePath = dlg.GetPathName();
    }
    string strFilePath;
    strFilePath = (LPCSTR)(CStringA)(cstrFilePath);
    ofstream out;
    out.open(strFilePath);
    string file_regular;
    CString cstr_file_regular;
    regularExp_edit.GetWindowTextW(cstr_file_regular);
    file_regular = (LPCSTR)(CStringA)(cstr_file_regular);
    out << file_regular;
    out.close();
}

class NFAStateTransitionTable
{
public:
    NFAStateTransitionTable();
    NFAStateTransitionTable(char c)
    {
        state_num = 2;
        initial_state = 1;
        final_state = 2;
        symbol_num = 2;
        id[c] = 1;
        symbol[1] = c;
        table = vector<vector<vector<int>>>(2, vector<vector<int>>(2, vector<int>()));
        table[0][1].push_back(2);
    }

    NFAStateTransitionTable(int row, int col)
    {
        table = vector<vector<vector<int>>>(row, vector<vector<int>>(col, vector<int>()));
    }

    int state_num;
    int initial_state;
    int final_state;
    int symbol_num;
    map<int, char> symbol;
    map<char, int> id;
    vector<vector<vector<int>>> table;

    void toList(CListCtrl& nfa_list)
    {
        //初始化
        nfa_list.DeleteAllItems();
        CHeaderCtrl* pHeaderCtrl = nfa_list.GetHeaderCtrl();
        if (pHeaderCtrl != NULL)
        {
            int nColumnCount = pHeaderCtrl->GetItemCount();
            for (int i = 0; i < nColumnCount; i++)
            {
                nfa_list.DeleteColumn(0);
            }
        }
        //设置表头
        nfa_list.InsertColumn(0, TEXT("状态\\字符"), LVCFMT_LEFT, 100);
        nfa_list.InsertColumn(1, TEXT("ε"), LVCFMT_LEFT, 100);
        CString cstr;
        for (int i = 2; i <= symbol_num; i++)
        {
            cstr = "";
            cstr.AppendChar(symbol[i - 1]);
            nfa_list.InsertColumn(i, cstr, LVCFMT_LEFT, 100);
        }
        nfa_list.SetExtendedStyle(nfa_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        //设置内容
        for (int line = 0; line < table.size(); line++)
        {
            cstr.Format(_T("%d"), line +1);
            nfa_list.InsertItem(line, cstr);
            for (int j = 1; j <= symbol_num; j++)
            {
                CString cstr2;
                for (int k = 0; k < table[line][j - 1].size(); k++)
                {
                    cstr.Format(_T("%d"), table[line][j - 1][k]);
                    if (k!=0)
                        cstr2 += ',';
                    cstr2 += cstr;
                }
                nfa_list.SetItemText(line, j, cstr2);
            }
        }
    }

    void toString()
    {
        cout << "状态数为：" << state_num << endl;
        cout << "初态为：" << initial_state << endl;
        cout << "终态为：" << final_state << endl;
        cout << "字符数为：" << symbol_num << endl;
        cout << "字符为：";
        for (int i = 1; i < symbol_num; i++)
            cout << symbol[i] << ' ';
        cout << endl;
        cout << "状态转移表为：" << endl;
        for (int i = 0; i < state_num; i++)
        {
            for (int j = 0; j < symbol_num; j++)
            {
                if (table[i][j].size() == 0)
                    cout << 0;

                for (int k = 0; k < table[i][j].size(); k++)
                {
                    cout << table[i][j][k] << ',';
                }
                cout << ' ';
            }
            cout << endl;
        }
    }
};

class DFAStateTransitionTable
{
public:
    int initial_state;
    int final_state;
    int symbol_num;
    map<int, char> symbol;
    map<char, int> id;
    vector<vector<set<int>>> table;

    void toList(CListCtrl& dfa_list)
    {
        //初始化
        dfa_list.DeleteAllItems();
        CHeaderCtrl* pHeaderCtrl = dfa_list.GetHeaderCtrl();
        if (pHeaderCtrl != NULL)
        {
            int nColumnCount = pHeaderCtrl->GetItemCount();
            for (int i = 0; i < nColumnCount; i++)
            {
                dfa_list.DeleteColumn(0);
            }
        }
        //设置表头
        dfa_list.InsertColumn(0, TEXT("状态\\字符"), LVCFMT_LEFT, 100);
        CString cstr;
        for (int i = 1; i <= symbol_num; i++)
        {
            cstr = "";
            cstr.AppendChar(symbol[i]);
            dfa_list.InsertColumn(i, cstr, LVCFMT_LEFT, 100);
        }
        dfa_list.SetExtendedStyle(dfa_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        //设置内容
        for (int line = 0; line < table.size(); line++)
        {
            cstr.Format(_T("%d"), line + 1);
            dfa_list.InsertItem(line, cstr);
            for (int j = 0; j <= symbol_num; j++)
            {
                CString cstr2;
                for (set<int>::iterator k = table[line][j].begin(); k != end(table[line][j]); k++)
                {
                    cstr.Format(_T("%d"), *k);
                    if (k != table[line][j].begin())
                        cstr2 += ',';
                    cstr2 += cstr;
                }
                dfa_list.SetItemText(line, j, cstr2);
            }
        }
    }

    void toString()
    {
        cout << "初态为：" << initial_state << endl;
        cout << "终态为：" << final_state << endl;
        cout << "字符数为：" << symbol_num << endl;
        cout << "字符为：";
        for (int i = 1; i <= symbol_num; i++)
            cout << symbol[i] << ' ';
        cout << endl;
        cout << "状态转移表为：" << endl;
        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j <= symbol_num; j++)
            {
                if (table[i][j].size() == 0)
                    cout << 0;

                for (set<int>::iterator k = table[i][j].begin(); k != end(table[i][j]); k++)
                {
                    cout << *k << ',';
                }
                cout << ' ';
            }
            cout << endl;
        }
    }
};

class minimizedDFAStateTransitionTable
{
public:
    int initial_state;
    set<int> final_state;
    int symbol_num;
    map<int, char> symbol;
    map<char, int> id;
    vector<vector<vector<int>>> table;

    void toList(CListCtrl& minimized_dfa_list)
    {
        //初始化
        minimized_dfa_list.DeleteAllItems();
        CHeaderCtrl* pHeaderCtrl = minimized_dfa_list.GetHeaderCtrl();
        if (pHeaderCtrl != NULL)
        {
            int nColumnCount = pHeaderCtrl->GetItemCount();
            for (int i = 0; i < nColumnCount; i++)
            {
                minimized_dfa_list.DeleteColumn(0);
            }
        }
        //设置表头
        minimized_dfa_list.InsertColumn(0, TEXT("状态\\字符"), LVCFMT_LEFT, 100);
        CString cstr;
        for (int i = 1; i <= symbol_num; i++)
        {
            cstr = "";
            cstr.AppendChar(symbol[i]);
            minimized_dfa_list.InsertColumn(i, cstr, LVCFMT_LEFT, 100);
        }
        minimized_dfa_list.SetExtendedStyle(minimized_dfa_list.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
        //设置内容
        for (int line = 0; line < table.size(); line++)
        {
            cstr.Format(_T("%d"), line + 1);
            minimized_dfa_list.InsertItem(line, cstr);
            for (int j = 0; j <= symbol_num; j++)
            {
                CString cstr2;
                for (int k = 0; k < table[line][j].size(); k++)
                {
                    cstr.Format(_T("%d"), table[line][j][k]);
                    if (k != 0)
                        cstr2 += ',';
                    cstr2 += cstr;
                }
                minimized_dfa_list.SetItemText(line, j, cstr2);
            }
        }
    }

    void toString()
    {
        cout << "初态为：" << initial_state << endl;
        cout << "终态为：";
        set<int>::iterator it;
        for (it = final_state.begin(); it != end(final_state); it++)
            cout << *it << ',';
        cout << endl;
        cout << "字符数为：" << symbol_num << endl;
        cout << "字符为：";
        for (int i = 1; i <= symbol_num; i++)
            cout << symbol[i] << ' ';
        cout << endl;
        cout << "状态转移表为：" << endl;
        for (int i = 0; i < table.size(); i++)
        {
            for (int j = 0; j <= symbol_num; j++)
            {
                if (table[i][j].size() == 0)
                    cout << 0;

                for (int k = 0; k < table[i][j].size(); k++)
                {
                    cout << table[i][j][k] << ',';
                }
                cout << ' ';
            }
            cout << endl;
        }
    }
};

NFAStateTransitionTable connet(NFAStateTransitionTable a, NFAStateTransitionTable b)//根据连接运算的状态表变化规律连接两个自动机
{
    int intersection_num = 0;
    for (int i = 1; i < a.symbol_num; i++)//计算相同字符的数量
    {
        if (b.id.find(a.symbol[i]) != b.id.end())
            intersection_num++;
    }
    NFAStateTransitionTable c(a.state_num + b.state_num, a.symbol_num + b.symbol_num - 1 - intersection_num);//新建储存结果的状态转移表
    c.state_num = a.state_num + b.state_num;
    c.initial_state = 1;
    c.final_state = a.state_num + b.state_num;
    c.symbol_num = a.symbol_num;
    c.symbol = a.symbol;//将a的符号集赋给c
    c.id = a.id;
    for (int i = 1; i < b.symbol_num; i++)//遍历b的符号集，若不在c中则加入到c
    {
        if (c.id.find(b.symbol[i]) == c.id.end())
        {
            c.symbol[c.symbol_num] = b.symbol[i];
            c.id[b.symbol[i]] = c.symbol_num;
            c.symbol_num++;
        }
    }
    /*根据连接运算时状态转移表的变化规律确定c的状态转移表*/
    for (int i = 0; i < a.state_num; i++)
    {
        for (int j = 0; j < a.symbol_num; j++)
        {
            for (int k = 0; k < a.table[i][j].size(); k++)
            {
                c.table[i][j].push_back(a.table[i][j][k]);
            }
        }
    }
    for (int i = 0; i < b.state_num; i++)
    {
        for (int k = 0; k < b.table[i][0].size(); k++)
        {
            c.table[i + a.state_num][0].push_back(b.table[i][0][k] + a.state_num);
        }
    }
    for (int i = 0; i < b.state_num; i++)
    {
        for (int j = 1; j < b.symbol_num; j++)
        {
            for (int k = 0; k < b.table[i][j].size(); k++)
            {
                c.table[i + a.state_num][c.id[b.symbol[j]]].push_back(b.table[i][j][k] + a.state_num);
            }
        }
    }
    c.table[a.final_state - 1][0].push_back(b.initial_state + a.state_num);
    return c;
}

NFAStateTransitionTable choose(NFAStateTransitionTable a, NFAStateTransitionTable b)//根据选择运算的状态表变化规律连接两个自动机
{
    int intersection_num = 0;
    for (int i = 1; i < a.symbol_num; i++)//计算相同字符的数量
    {
        if (b.id.find(a.symbol[i]) != b.id.end())
            intersection_num++;
    }
    NFAStateTransitionTable c(a.state_num + b.state_num + 2, a.symbol_num + b.symbol_num - 1 - intersection_num);//新建储存结果的状态转移表
    c.state_num = a.state_num + b.state_num + 2;
    c.initial_state = 1;
    c.final_state = a.state_num + b.state_num + 2;
    c.symbol_num = a.symbol_num;
    c.symbol = a.symbol;//将a的符号集赋给c
    c.id = a.id;
    for (int i = 1; i < b.symbol_num; i++)//遍历b的符号集，若不在c中则加入到c
    {
        if (c.id.find(b.symbol[i]) == c.id.end())
        {
            c.symbol[c.symbol_num] = b.symbol[i];
            c.id[b.symbol[i]] = c.symbol_num;
            c.symbol_num++;
        }
    }
    /*根据选择运算时状态转移表的变化规律确定c的状态转移表*/
    for (int i = 0; i < a.state_num; i++)
    {
        for (int j = 0; j < a.symbol_num; j++)
        {
            for (int k = 0; k < a.table[i][j].size(); k++)
            {
                c.table[i + 1][j].push_back(a.table[i][j][k] + 1);
            }
        }
    }
    for (int i = 0; i < b.state_num; i++)
    {
        for (int k = 0; k < b.table[i][0].size(); k++)
        {
            c.table[i + 1 + a.state_num][0].push_back(b.table[i][0][k] + 1 + a.state_num);
        }
    }
    for (int i = 0; i < b.state_num; i++)
    {
        for (int j = 1; j < b.symbol_num; j++)
        {
            for (int k = 0; k < b.table[i][j].size(); k++)
            {
                c.table[i + 1 + a.state_num][c.id[b.symbol[j]]].push_back(b.table[i][j][k] + 1 + a.state_num);
            }
        }
    }
    c.table[0][0].push_back(a.initial_state + 1);
    c.table[0][0].push_back(b.initial_state + 1 + a.state_num);
    c.table[a.final_state + 1 - 1][0].push_back(c.final_state);
    c.table[b.final_state + 1 + a.state_num - 1][0].push_back(c.final_state);
    return c;
}

NFAStateTransitionTable closure(NFAStateTransitionTable a)//根据闭包运算的状态表变化规律连接两个自动机
{
    NFAStateTransitionTable c(a.state_num + 2, a.symbol_num);//新建储存结果的状态转移表
    c.state_num = a.state_num + 2;
    c.initial_state = 1;
    c.final_state = a.state_num + 2;
    c.symbol_num = a.symbol_num;
    c.symbol = a.symbol;
    c.id = a.id;
    /*根据闭包运算时状态转移表的变化规律确定c的状态转移表*/
    for (int i = 0; i < a.state_num; i++)
    {
        for (int j = 0; j < a.symbol_num; j++)
        {
            for (int k = 0; k < a.table[i][j].size(); k++)
            {
                c.table[i + 1][j].push_back(a.table[i][j][k] + 1);
            }
        }
    }
    c.table[0][0].push_back(a.initial_state + 1);
    c.table[0][0].push_back(c.final_state);
    c.table[a.final_state + 1 - 1][0].push_back(c.final_state);
    c.table[a.final_state + 1 - 1][0].push_back(a.initial_state + 1);
    return c;
}

bool isOper(char c)
{
    if (c == '|' || c == '*' || c == '(' || c == ')')
        return true;
    else
        return false;
}

NFAStateTransitionTable regularExpToNFA(string regular)//计算中缀表达式
{
    stack<NFAStateTransitionTable> character;
    stack<char> oper;
    bool connet_char = false;
    int i = 0;
    while (i < regular.length())
    {
        if (connet_char)
        {
            oper.push('+');
            connet_char = false;
        }
        else if (!isOper(regular[i]))
        {
            NFAStateTransitionTable t(regular[i]);
            character.push(t);
            if (i + 1 < regular.length() && (!isOper(regular[i + 1]) || regular[i + 1] == '('))
                connet_char = true;
            i++;
        }
        else if (regular[i] == '*')
        {
            NFAStateTransitionTable t = closure(character.top());
            character.pop();
            character.push(t);
            i++;
        }
        else if (regular[i] == '|')
        {
            if (!oper.empty() && oper.top() == '+')
            {
                NFAStateTransitionTable t = character.top();
                character.pop();
                t = connet(character.top(), t);
                character.pop();
                character.push(t);
                oper.pop();
            }
            else
            {
                oper.push('|');
                i++;
            }
        }
        else if (regular[i] == '(')
        {
            oper.push('(');
            i++;
        }
        else if (regular[i] == ')')
        {
            while (oper.top() != '(')
            {
                if (oper.top() == '+')
                {
                    NFAStateTransitionTable t = character.top();
                    character.pop();
                    t = connet(character.top(), t);
                    character.pop();
                    character.push(t);
                    oper.pop();
                }
                else if (oper.top() == '|')
                {
                    NFAStateTransitionTable t = character.top();
                    character.pop();
                    t = choose(character.top(), t);
                    character.pop();
                    character.push(t);
                    oper.pop();
                }
            }
            oper.pop();
            if (i + 1 < regular.length() && (!isOper(regular[i + 1]) || regular[i + 1] == '('))
                connet_char = true;
            i++;
        }
    }
    while (!character.empty() && !oper.empty())
    {
        if (oper.top() == '+')
        {
            NFAStateTransitionTable t = character.top();
            character.pop();
            t = connet(character.top(), t);
            character.pop();
            character.push(t);
            oper.pop();
        }
        else if (oper.top() == '|')
        {
            NFAStateTransitionTable t = character.top();
            character.pop();
            t = choose(character.top(), t);
            character.pop();
            character.push(t);
            oper.pop();
        }
    }
    cout << oper.empty();
    return character.top();
}

void calculateClosure(set<int>& s, NFAStateTransitionTable& nfa, int state)//计算state的闭包，存放到s中
{
    if (s.find(state) == end(s))
    {
        s.insert(state);
        for (int i = 0; i < nfa.table[state - 1][0].size(); i++)
        {
            calculateClosure(s, nfa, nfa.table[state - 1][0][i]);//递归调用
        }
    }
}

void calculateClosureOfSet(set<int>& s, NFAStateTransitionTable& nfa)//计算s中所有元素的闭包，并添加到s中
{
    set<int>::iterator it;
    for (it = s.begin(); it != end(s); it++)
    {
        for (int i = 0; i < nfa.table[*it - 1][0].size(); i++)
        {
            calculateClosure(s, nfa, nfa.table[*it - 1][0][i]);
        }
    }
}

bool isNewState(set<int>& s, DFAStateTransitionTable& dfa)
{
    bool new_state = true;
    for (int i = 0; i < dfa.table.size(); i++)
    {
        if (dfa.table[i][0] == s)
        {
            new_state = false;
            break;
        }
    }
    return new_state;
}

DFAStateTransitionTable NFAToDFA(NFAStateTransitionTable nfa)
{
    DFAStateTransitionTable dfa;
    dfa.initial_state = nfa.initial_state;
    dfa.final_state = nfa.final_state;
    dfa.symbol_num = nfa.symbol_num - 1;
    dfa.symbol = nfa.symbol;
    dfa.id = nfa.id;
    queue<set<int>> state_sets;
    set<int> closure;
    calculateClosure(closure, nfa, nfa.initial_state);//计算初态的闭包，即状态集
    state_sets.push(closure);//初态闭包入栈
    while (!state_sets.empty())
    {
        if (isNewState(state_sets.front(), dfa))//如果栈顶的是新的状态集
        {
            vector<set<int>> t(nfa.symbol_num, set<int>());
            t[0] = state_sets.front();//加入将栈顶状态集
            state_sets.pop();
            dfa.table.push_back(t);
            /*计算该状态集转移后的状态*/
            for (int i = 1; i < nfa.symbol_num; i++)//对于每一个符号
            {
                for (set<int>::iterator j = dfa.table[dfa.table.size() - 1][0].begin(); j != end(dfa.table[dfa.table.size() - 1][0]); j++)//状态集中的每一个状态
                {
                    for (int k = 0; k < nfa.table[*j - 1][i].size(); k++)//将转移后的每一个状态
                    {
                        dfa.table[dfa.table.size() - 1][i].insert(nfa.table[*j - 1][i][k]);//加入
                    }
                    calculateClosureOfSet(dfa.table[dfa.table.size() - 1][i], nfa);//并计算转移后的状态集的闭包
                }
                if (isNewState(dfa.table[dfa.table.size() - 1][i], dfa) && dfa.table[dfa.table.size() - 1][i].size() != 0)//若转移后获得的状态集是新的
                {
                    state_sets.push(dfa.table[dfa.table.size() - 1][i]);//则入栈
                }
            }
        }
        else
            state_sets.pop();
    }
    return dfa;
}

bool states_equal(vector<vector<int>>& a, vector<vector<int>>& b, set<int>& non_final_state, set<int>& final_state)//判断两行中对应位置是否为终态的属性是否完全一致
{
    if (a.size() != b.size())//行的长度不同
        return false;//无法比较，判定为不一致
    bool equal = true;
    for (int i = 1; i < a.size(); i++)//逐个符号判断
    {
        if (a[i].empty() && !b[i].empty() || !a[i].empty() && b[i].empty())
            return false;
        else if (!a[i].empty() && !b[i].empty())
        {
            if (non_final_state.find(a[i][0]) == end(non_final_state) && non_final_state.find(b[i][0]) != end(non_final_state) || non_final_state.find(a[i][0]) != end(non_final_state) && non_final_state.find(b[i][0]) == end(non_final_state))
                return false;
            if (final_state.find(a[i][0]) == end(final_state) && final_state.find(b[i][0]) != end(final_state) || final_state.find(a[i][0]) != end(final_state) && final_state.find(b[i][0]) == end(final_state))
                return false;
        }
    }
    return equal;
}

void replace(vector<vector<vector<int>>>& table, int x, int y)//将table中所有x替换为y
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 1; j < table[i].size(); j++)
        {
            if (!table[i][j].empty() && table[i][j][0] == x)
                table[i][j][0] = y;
        }
    }
}

minimizedDFAStateTransitionTable minimizeDFA(DFAStateTransitionTable dfa)
{
    minimizedDFAStateTransitionTable minimize_dfa;
    minimize_dfa.initial_state = dfa.initial_state;
    minimize_dfa.symbol_num = dfa.symbol_num;
    minimize_dfa.symbol = dfa.symbol;
    minimize_dfa.id = dfa.id;
    set<int> non_final_state;
    set<int> final_state;
    for (int i = 0; i < dfa.table.size(); i++)//判断状态集是否为终态
    {
        if (dfa.table[i][0].find(dfa.final_state) != end(dfa.table[i][0]))
            final_state.insert(i + 1);//加入到终态集合中
        else
            non_final_state.insert(i + 1);//加入到非终态集合中
    }
    vector<vector<vector<int>>> table(dfa.table.size(), vector<vector<int>>(dfa.symbol_num + 1, vector<int>()));//新建一个临时表，用于存储状态简化后的表
    for (int i = 0; i < dfa.table.size(); i++)//对转移后状态集进行化简，并将简化后的加入到临时表中
    {
        for (int j = 1; j <= dfa.symbol_num; j++)
        {
            for (int k = 0; k < dfa.table.size(); k++)
            {
                if (dfa.table[i][j] == dfa.table[k][0])
                {
                    table[i][j].push_back(k + 1);
                }
            }
        }
    }
    for (int i = 0; i < table.size(); i++)//对转移前状态集进行化简，并将简化后的加入到临时表中
        table[i][0].push_back(i + 1);

    for (int i = 0; i < table.size(); i++)//进行最小化，合并等价的状态
    {
        if (table[i][0].size() != 0)
        {
            for (int j = i + 1; j < table.size(); j++)
            {
                if (states_equal(table[i], table[j], non_final_state, final_state))
                {
                    replace(table, table[j][0][0], table[i][0][0]);
                    table[j][0].clear();
                }
            }
        }
    }

    for (int i = 0; i < table.size(); i++)//将结果存入最小化后的dfa状态转移表中
    {
        if (table[i][0].size() != 0)
        {
            minimize_dfa.table.push_back(table[i]);
            if (final_state.find(table[i][0][0]) != end(final_state))
                minimize_dfa.final_state.insert(table[i][0][0]);
        }
    }
    return minimize_dfa;
}

void DFAToCode(minimizedDFAStateTransitionTable minimize_dfa,CEdit& code_edit)
{
    ofstream out;
    out.open("\code.txt");
    int accept_state = 1;
    out << "bool lexicalAnalysis(string s)" << endl;
    out << "{" << endl;
    out << "    int i = 0;" << endl;
    out << "    int state = 1;" << endl;
    out << "    while (";
    for (int i = 0; i < minimize_dfa.table.size(); i++)
    {
        if (i != 0)
            out << " || ";
        out << "state == " << minimize_dfa.table[i][0][0];
        if (minimize_dfa.table[i][0][0] == accept_state)
            accept_state++;
    }
    out << ")" << endl;
    out << "    {" << endl;
    out << "        switch (state)" << endl;
    out << "        {" << endl;
    for (int i = 0; i < minimize_dfa.table.size(); i++)
    {
        bool first_if = true;
        out << "        case " << minimize_dfa.table[i][0][0] << ":" << endl;
        for (int j = 1; j <= minimize_dfa.symbol_num; j++)
        {
            if (!minimize_dfa.table[i][j].empty())
            {
                if (!first_if)
                    out << "            else if (s[i] == '" << minimize_dfa.symbol[j] << "')" << endl;
                else
                {
                    out << "            if (s[i] == '" << minimize_dfa.symbol[j] << "')" << endl;
                    first_if = false;
                }
                out << "            {" << endl;
                out << "                i++;" << endl;
                out << "                state = " << minimize_dfa.table[i][j][0] << ";" << endl;
                out << "            }" << endl;
            }
        }
        out << "            else" << endl;
        if (minimize_dfa.final_state.find(minimize_dfa.table[i][0][0]) == end(minimize_dfa.final_state))
            out << "                state = " << accept_state + 1 << ";" << endl;
        else
            out << "                state = " << accept_state << ";" << endl;
        out << "            break;" << endl;
    }
    out << "        default:" << endl;
    out << "            break;" << endl;
    out << "        }" << endl;
    out << "    }" << endl;
    out << "    if (state == " << accept_state << ")" << endl;
    out << "        return true;" << endl;
    out << "    else" << endl;
    out << "        return false;" << endl;
    out << "}" << endl;
    out.close();
    ifstream in;
    in.open("\code.txt");
    string str;
    CString cstr_all;
    while (getline(in, str))
    {
        CString cstr(str.c_str());
        cstr_all += cstr;
        cstr_all += "\r\n";
    }
    code_edit.SetWindowTextW(cstr_all);
    in.close();
}

void Cexperience2Dlg::OnBnClickedButton4()
{
    CString cstr;
    regularExp_edit.GetWindowTextW(cstr);
    string regular;
    regular = (LPCSTR)(CStringA)(cstr);
    NFAStateTransitionTable NFA = regularExpToNFA(regular);
    NFA.toString();
    NFA.toList(nfa_list);
    DFAStateTransitionTable DFA = NFAToDFA(NFA);
    DFA.toString();
    DFA.toList(dfa_list);
    minimizedDFAStateTransitionTable minimizedDFA = minimizeDFA(DFA);
    minimizedDFA.toString();
    minimizedDFA.toList(minimized_dfa_list);
    DFAToCode(minimizedDFA, code_edit);
}
