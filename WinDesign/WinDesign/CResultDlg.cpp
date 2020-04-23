// CResultDlg.cpp: 实现文件
//

#include "pch.h"
#include "WinDesign.h"
#include "CResultDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include <string>
#include <math.h>
// CResultDlg 对话框

IMPLEMENT_DYNAMIC(CResultDlg, CDialogEx)

CResultDlg::CResultDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_Result, pParent) {
	aim = 0;
	time = 0;
	sta_num = 0;
	dispachnum = 0;
	thoughoutjain = 0;
	dispachtype = 0;
	dispachlenth = 0;
	data_show.clear();
	paint_info = nullptr;
}

CResultDlg::~CResultDlg() {
}

void CResultDlg::Drawxy(CPaintDC *dc,int width,int height) {
	dc->MoveTo(50, height - 50);
	dc->LineTo(50, 50);
	dc->MoveTo(50, 50);
	dc->LineTo(40, 70);
	dc->MoveTo(50, 50);
	dc->LineTo(60, 70);
	dc->MoveTo(50, height - 50);
	dc->LineTo(width - 50, height - 50);
	dc->MoveTo(width - 50, height - 50);
	dc->LineTo(width - 70, height - 60);
	dc->MoveTo(width - 50, height - 50);
	dc->LineTo(width - 70, height - 40);
}


void CResultDlg::DoDataExchange(CDataExchange* pDX) {
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResultDlg, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CResultDlg 消息处理程序


void CResultDlg::OnPaint() {
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);//获得绘画区的大小

	Drawxy(&dc, rect.right, rect.bottom);
	std::string aim_str[2] = { "比例公平", "最大吞吐量" };
	std::string thoughoutjain_str[2] = { "Thoughout", "Jain" };
	std::string dispachtype_str[3] = { "比例公平调度", "轮询调度", "最大MCS调度" };
	std::string str1; 
	std::string str2; 

	if (sta_num == -1) {
		str1 = "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num) 
			+ " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同STA数量对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			}
			else if(i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			}
			dc.SelectObject(&pen);
			setxy(rect.right - 100, rect.bottom - 100);
			dc.Polyline(paint_info, data_show.size());
		}
	}
	else if (time == -1) {
		str1 = "优化目标:" + aim_str[aim - 1] + " STA数量:" + std::to_string(sta_num) + " 调度数量:" + std::to_string(dispachnum)
			+ " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度时间对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int lenlen = 0;
		std::vector<double> tmp;
		tmp = data_show; 
		int time_list[3] = { 100, 200, 500 };
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			int len = time_list[i];
			for (int j = lenlen; j < lenlen + len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			}
			dc.SelectObject(&pen);
			setxy(rect.right - 100, rect.bottom - 100);
			dc.Polyline(paint_info, data_show.size());
			lenlen += len;
			std::string  str = std::to_string(data_show.size());
			CString strtest(str.c_str());
			MessageBox(strtest, _T("test"));
		}
	}
	else if (dispachnum == -1) {
		str1 = "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num)
			+ " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度数量对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			}
			dc.SelectObject(&pen);
			setxy(rect.right - 100, rect.bottom - 100);
			dc.Polyline(paint_info, data_show.size());
		}
	}
	else if (dispachlenth == -1) {
		str1 = "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num)
			+ " 调度数量:" + std::to_string(dispachnum);
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度周期对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			}
			dc.SelectObject(&pen);
			setxy(rect.right - 100, rect.bottom - 100);
			dc.Polyline(paint_info, data_show.size());
		}
	}
	else if (dispachtype == -1) {
		str1 = "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num)
			+ " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度机制对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
			}
			dc.SelectObject(&pen);
			setxy(rect.right - 100, rect.bottom - 100);
			dc.Polyline(paint_info, data_show.size());
		}
	}
	else {
		str1 = "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) +
			"T" + " STA数量:" + std::to_string(sta_num) + " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		dc.SelectObject(&pen);
		setxy(rect.right - 100, rect.bottom - 100);
		dc.Polyline(paint_info, data_show.size());
	}
	
	CString csout1(str1.c_str());
	SetTextAlign(dc, VTA_CENTER);
	dc.TextOutW(rect.right / 2, 0, csout1);

	CString csout2(str2.c_str());
	SetTextAlign(dc, VTA_CENTER);
	dc.TextOutW(rect.right / 2, 20, csout2);
}


BOOL CResultDlg::OnInitDialog() {
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect temp(0,0,1200,600);//设置窗口大小
	CDialogEx::SetWindowPos(NULL, 0, 0, temp.Width(), temp.Height(), SWP_NOZORDER | SWP_NOMOVE);
	CDialogEx::CenterWindow();
	return TRUE;  
}
void CResultDlg::setxy(double w, double l) {
	double max = 0.0;
	int basex_size = 0;
	int basey_size = 0;
	for (int i = 0; i < data_show.size(); ++i) {
		data_show[i] > max ? max = data_show[i] : max = max;
	}

	basex_size = std::ceil(w / data_show.size());
	basey_size = std::ceil(l / std::ceil(max));
	paint_info = new CPoint[data_show.size()];
	for (int i = 0; i < data_show.size(); ++i) {
		CPoint p;
		p.x = i * basex_size + 50;
		p.y = l - std::ceil(data_show[i] * basey_size) + 50;
		paint_info[i] = p;
	}
}