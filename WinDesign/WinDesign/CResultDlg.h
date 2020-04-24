#pragma once
#include "pch.h"
#include <vector>

// CResultDlg 对话框

class CResultDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CResultDlg)

public:
	CResultDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CResultDlg();
	void Drawxy(CPaintDC & dc,int width,int height, double maxy, int maxx);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Result };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
public:
	int aim;
	int time;
	int sta_num;
	int dispachnum;
	int thoughoutjain;
	int dispachtype;
	int dkvalue;
	double dispachlenth;
	std::vector<double> data_show;
	CPoint * paint_info;
public:
	void setxy(double w, double l, int basex, int basey);
	void DrawXY(CPaintDC & dc,int w, int l, double maxy, int maxx);
};
