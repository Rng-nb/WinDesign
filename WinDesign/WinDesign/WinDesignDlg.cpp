#pragma once
#include "pch.h"
#include "framework.h"
#include "WinDesign.h"
#include "WinDesignDlg.h"
#include "afxdialogex.h"
#include "CResultDlg.h"
#include "Dispach.h"
#include <string>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx {
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

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX) {
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

CWinDesignDlg::CWinDesignDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_WINDESIGN_DIALOG, pParent) {
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
	aim = 1;
	time = 100;
	sta_num = 50;
	dispachlenth = 20.0;
	dispachnum = 8;
	thoughoutjain = 1;
	dispachtype = 1;
}

void CWinDesignDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Daikuanvalue, Dk_value);
	DDX_Control(pDX, IDC_RTnumvalue, Rnum_value);
	DDX_Control(pDX, IDC_COMBO1, Dispachtime);
	DDX_Control(pDX, IDC_COMBO2, Dispachlenth);
	DDX_Control(pDX, IDC_COMBO3, Dispachnum);
	DDX_Control(pDX, IDC_COMBO4, Aim);
	DDX_Control(pDX, IDC_COMBO5, ThoughoutJain);
	DDX_Control(pDX, IDC_COMBO6, Dispachtype);
}

BEGIN_MESSAGE_MAP(CWinDesignDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CWinDesignDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Exit, &CWinDesignDlg::OnBnClickedExit)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CWinDesignDlg::OnCbnSelchangeDispachtime)
	ON_CBN_SELCHANGE(IDC_Daikuanvalue, &CWinDesignDlg::OnCbnSelchangeDaikuanvalue)
	ON_CBN_SELCHANGE(IDC_RTnumvalue, &CWinDesignDlg::OnCbnSelchangeRtnumvalue)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CWinDesignDlg::OnCbnSelchangeDispachlenth)
	ON_CBN_SELCHANGE(IDC_COMBO3, &CWinDesignDlg::OnCbnSelchangeDispachnum)
	ON_CBN_SELCHANGE(IDC_COMBO4, &CWinDesignDlg::OnCbnSelchangeAim)
	ON_CBN_SELCHANGE(IDC_COMBO5, &CWinDesignDlg::OnCbnSelchangeThoughJain)
	ON_CBN_SELCHANGE(IDC_COMBO6, &CWinDesignDlg::OnCbnSelchangeDispachtype)
END_MESSAGE_MAP()


// CWinDesignDlg 消息处理程序

BOOL CWinDesignDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr) {
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty()) {
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	initDkvalue();
	initNumvalue();
	initDispachtime();
	initDispachlenth();
	initDispachnum();
	initAim();
	initThoughoutJain();
	initDispachtype();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CWinDesignDlg::OnSysCommand(UINT nID, LPARAM lParam) {
	if ((nID & 0xFFF0) == IDM_ABOUTBOX) {
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else {
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CWinDesignDlg::OnPaint() {
	if (IsIconic()) {
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
	else {
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CWinDesignDlg::OnQueryDragIcon() {
	return static_cast<HCURSOR>(m_hIcon);
}



void CWinDesignDlg::OnBnClickedOk() {
	// TODO: 在此添加控件通知处理程序代码
	Dispachinfo();
	CResultDlg result;
	result.aim = aim;
	result.time = time;
	result.sta_num = sta_num;
	result.dispachnum = dispachnum;
	result.thoughoutjain = thoughoutjain;
	result.dispachtype = dispachtype;
	result.dispachlenth = dispachlenth;
	for (int i = 0; i < info_data.size(); ++i) {
		result.data_show.push_back(info_data[i]);
	}
	info_data.clear();
	result.DoModal();
}

void CWinDesignDlg::OnBnClickedExit() {
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CWinDesignDlg::initDkvalue() {
	Dk_value.AddString(_T("请选择"));
	Dk_value.AddString(_T("20M"));
	Dk_value.AddString(_T("40M"));
	Dk_value.AddString(_T("80M"));
	Dk_value.AddString(_T("不同带宽对比"));
	Dk_value.SetCurSel(0);//从位置0开始显示
}

void CWinDesignDlg::OnCbnSelchangeDaikuanvalue() {
	CString str;
	int index = 0;
	index = Dk_value.GetCurSel();
	Dk_value.GetLBText(index, str);
	if (str == "20M")
		dkvalue = 20;
	else if (str == "40M")
		dkvalue = 40;
	else if (str == "80M")
		dkvalue = 80;
	else if (str == "不同带宽对比")
		dkvalue = -1;
	else
		MessageBox(_T("请选择带宽"), _T("提示"));
}

void CWinDesignDlg::initNumvalue() {
	Rnum_value.AddString(_T("请选择"));
	Rnum_value.AddString(_T("30"));
	Rnum_value.AddString(_T("50"));
	Rnum_value.AddString(_T("70"));
	Rnum_value.AddString(_T("不同STA数量对比"));
	Rnum_value.SetCurSel(0);//从位置0开始显示
}

void CWinDesignDlg::OnCbnSelchangeRtnumvalue() {
	CString str;
	int index = 0;
	index = Rnum_value.GetCurSel();
	Rnum_value.GetLBText(index, str);
	if (str == "30")
		sta_num = 30;
	else if (str == "50")
		sta_num = 50;
	else if (str == "70")
		sta_num = 70;
	else if (str == "不同STA数量对比")
		sta_num = -1;
	else
		MessageBox(_T("请选择STA数量"), _T("提示"));
}

void CWinDesignDlg::initDispachtime() {
	Dispachtime.AddString(_T("请选择"));
	Dispachtime.AddString(_T("100T"));
	Dispachtime.AddString(_T("200T"));
	Dispachtime.AddString(_T("500T"));
	Dispachtime.AddString(_T("不同调度时间对比"));
	Dispachtime.SetCurSel(0);
}

void CWinDesignDlg::OnCbnSelchangeDispachtime() {//下拉框事件改变
	CString str;
	int index = 0;
	index = Dispachtime.GetCurSel();
	Dispachtime.GetLBText(index, str);
	if (str == "100T")
		time = 100;
	else if (str == "200T")
		time = 200;
	else if (str == "500T")
		time = 500;
	else if (str == "不同调度时间对比")
		time = -1;
	else
		MessageBox(_T("请选择仿真时间"), _T("提示"));
}

void CWinDesignDlg::initDispachlenth() {
	int index = 0;
	Dispachlenth.AddString(_T("请选择"));
	Dispachlenth.AddString(_T("10ms"));
	Dispachlenth.AddString(_T("20ms"));
	Dispachlenth.AddString(_T("30ms"));
	Dispachlenth.AddString(_T("不同调度周期对比"));
	Dispachlenth.SetCurSel(0);
}

void CWinDesignDlg::OnCbnSelchangeDispachlenth() {
	CString str;
	int index = 0;
	index = Dispachlenth.GetCurSel();
	Dispachlenth.GetLBText(index, str);
	if (str == "10ms")
		dispachlenth = 10.0;
	else if (str == "20ms")
		dispachlenth = 20.0;
	else if (str == "30ms")
		dispachlenth = 30.0;
	else if (str == "不同调度周期对比")
		dispachlenth = -1.0;
	else
		MessageBox(_T("请选择调度周期"), _T("提示"));
}

void CWinDesignDlg::initDispachnum() {
	Dispachnum.AddString(_T("请选择"));
	Dispachnum.AddString(_T("3"));
	Dispachnum.AddString(_T("5"));
	Dispachnum.AddString(_T("8"));
	Dispachnum.AddString(_T("不同调度数量对比"));
	Dispachnum.SetCurSel(0);
}

void CWinDesignDlg::OnCbnSelchangeDispachnum() {
	CString str;
	int index = 0;
	index = Dispachnum.GetCurSel();
	Dispachnum.GetLBText(index, str);
	if (str == "3") 
		dispachnum = 3;
	else if (str == "5")
		dispachnum = 5;
	else if (str == "8")
		dispachnum = 8;
	else if (str == "不同调度数量对比")
		dispachnum = -1;
	else
		MessageBox(_T("请选择调度数量"), _T("提示"));
}

void CWinDesignDlg::initAim() {
	Aim.AddString(_T("请选择"));
	Aim.AddString(_T("比例公平"));
	Aim.AddString(_T("最大吞吐量"));
	Aim.SetCurSel(0);
}

void CWinDesignDlg::OnCbnSelchangeAim()
{
	CString str;
	int index = 0;
	index = Aim.GetCurSel();
	Aim.GetLBText(index, str);
	if (str == "比例公平")
		aim = 1;
	else if (str == "最大吞吐量")
		aim = 2;
	else
		MessageBox(_T("请选择优化目标"), _T("提示"));
}

void CWinDesignDlg::initThoughoutJain() {
	ThoughoutJain.AddString(_T("请选择"));
	ThoughoutJain.AddString(_T("Thoughout"));
	ThoughoutJain.AddString(_T("Jain"));
	ThoughoutJain.SetCurSel(0);
}

void CWinDesignDlg::OnCbnSelchangeThoughJain()
{
	CString str;
	int index = 0;
	index = ThoughoutJain.GetCurSel();
	ThoughoutJain.GetLBText(index, str);
	if (str == "Thoughout")
		thoughoutjain = 1;
	else if (str == "Jain")
		thoughoutjain = 2;
	else
		MessageBox(_T("请选择性能指标"), _T("提示"));
}

void CWinDesignDlg::initDispachtype() {
	Dispachtype.AddString(_T("请选择"));
	Dispachtype.AddString(_T("比例公平调度"));
	Dispachtype.AddString(_T("轮询调度"));
	Dispachtype.AddString(_T("最大MCS调度"));
	Dispachtype.AddString(_T("不同调度机制对比"));
	Dispachtype.SetCurSel(0);
}

void CWinDesignDlg::OnCbnSelchangeDispachtype()
{
	CString str;
	int index = 0;
	index = Dispachtype.GetCurSel();
	Dispachtype.GetLBText(index, str);
	if (str == "比例公平调度")
		dispachtype = 1;
	else if (str == "轮询调度")
		dispachtype = 2;
	else if (str == "最大MCS调度")
		dispachtype = 3;
	else if (str == "不同调度机制对比")
		dispachtype = -1;
	else
		MessageBox(_T("请选择调度机制"), _T("提示"));
}

void CWinDesignDlg::getThoughtorJain(std::vector<double> & data) {
	for (int i = 0; i < data.size(); ++i) {
		info_data.push_back(data[i]);
	}	
}

void CWinDesignDlg::Dispachinfo() {
	Dispach dispach; 
	dispach.produceInfo();
	if (sta_num == -1) {
		for (int i = 0; i < 3; ++i) {
			dispach.initInfo(sta_num_list[i]);
			dispach.setDispach(time, dispachnum, dispachlenth);
			dispach.startDispach(aim * dispachtype);
			if (thoughoutjain == 1)
				getThoughtorJain(dispach.thoughtout_vector);
			else 
				getThoughtorJain(dispach.jain_vector);
		}
	} 
	else if (time == -1) {
		for (int i = 0; i < 3; ++i) {
			dispach.initInfo(sta_num);
			dispach.setDispach(time_list[i], dispachnum, dispachlenth);
			dispach.startDispach(aim * dispachtype);
			if (thoughoutjain == 1)
				getThoughtorJain(dispach.thoughtout_vector);
			else
				getThoughtorJain(dispach.jain_vector);
		}
	}
	else if (dispachnum == -1) {
		for (int i = 0; i < 3; ++i) {
			dispach.initInfo(sta_num);
			dispach.setDispach(time, dispachnum_list[i], dispachlenth);
			dispach.startDispach(aim * dispachtype);
			if (thoughoutjain == 1)
				getThoughtorJain(dispach.thoughtout_vector);
			else
				getThoughtorJain(dispach.jain_vector);
		}
	}
	else if (dispachlenth == -1) {
		for (int i = 0; i < 3; ++i) {
			dispach.initInfo(sta_num);
			dispach.setDispach(time, dispachnum, dispachlenth_list[i]);
			dispach.startDispach(aim * dispachtype);
			if (thoughoutjain == 1)
				getThoughtorJain(dispach.thoughtout_vector);
			else
				getThoughtorJain(dispach.jain_vector);
		}
	} 
	else if (dispachtype == -1) {
		for (int i = 0; i < 3; ++i) {
			dispach.initInfo(sta_num);
			dispach.setDispach(time, dispachnum, dispachlenth);
			dispach.startDispach(aim * dispachtype_list[i]);
			if (thoughoutjain == 1)
				getThoughtorJain(dispach.thoughtout_vector);
			else
				getThoughtorJain(dispach.jain_vector);
		}
	}
	else if (dkvalue == -1) {
		for (int i = 0; i < 3; ++i) {
			dispach.initInfo(sta_num);
			dispach.setDispach(time, dispachnum, dispachlenth);
			dispach.startDispach(aim * dispachtype);
			if (thoughoutjain == 1)
				getThoughtorJain(dispach.thoughtout_vector);
			else
				getThoughtorJain(dispach.jain_vector);
		}
	}
	else {
		dispach.initInfo(sta_num);
		dispach.setDispach(time, dispachnum, dispachlenth);
		dispach.startDispach(aim * dispachtype);
		if (thoughoutjain == 1)
			getThoughtorJain(dispach.thoughtout_vector);
		else
			getThoughtorJain(dispach.jain_vector);
	}
	
	//1 - 比例公平调度 比例公平优化
	//2 - 轮询调度 比例公平优化
	//3 - 最大MCS调度 比例公平优化
	//4 - 比例公平调度 最大吞吐量优化
	//5 - 轮询调度 最大吞吐量优化
	//6 - 最大MCS调度 最大吞吐量优化
	
	dispach.clearInfo();
	dispach.~Dispach();
	/*
	std::string  str = "Aim:" + std::to_string(aim) + "tjain:" + std::to_string(thoughoutjain) + "distype:" + std::to_string(dispachtype);
	CString strtest(str.c_str());
	MessageBox(strtest, _T("test"));
	*/
}



