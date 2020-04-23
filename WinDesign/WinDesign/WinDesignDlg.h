
// WinDesignDlg.h: 头文件
//

#pragma once
#include <vector>

// CWinDesignDlg 对话框
class CWinDesignDlg : public CDialogEx
{
// 构造
public:
	CWinDesignDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WINDESIGN_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedExit();
	CComboBox Dk_value;
	CComboBox Rnum_value;
	CComboBox Dispachtime;
	CComboBox Dispachlenth;
	CComboBox Dispachnum;
	void initDkvalue();
	void initNumvalue();
	void initDispachtime();
	void initDispachlenth();
	void initDispachnum();
	void initAim();
	void initThoughoutJain();
	void initDispachtype();
	void Dispachinfo();
	void getThoughtorJain(std::vector<double> & data);
	
	
	afx_msg void OnCbnSelchangeDispachtime();
	afx_msg void OnCbnSelchangeDaikuanvalue();
	afx_msg void OnCbnSelchangeRtnumvalue();
	afx_msg void OnCbnSelchangeDispachlenth();
	afx_msg void OnCbnSelchangeDispachnum();
private:
	int aim;
	int time;
	int sta_num;
	int dispachnum;
	int thoughoutjain;
	int dispachtype;
	double dispachlenth;
	int time_list[3] = {100, 200, 500};
	int sta_num_list[3] = { 30, 50, 70 };
	int dispachnum_list[3] = {3, 5, 8};
	int dispachtype_list[3] = {1, 2, 3};
	double dispachlenth_list[3] = {10.0, 20.0, 30.0};
	std::vector<double> info_data;
	
public:
	CComboBox Aim;
	CComboBox ThoughoutJain;
	CComboBox Dispachtype;
	afx_msg void OnCbnSelchangeAim();
	afx_msg void OnCbnSelchangeThoughJain();
	afx_msg void OnCbnSelchangeDispachtype();
};
