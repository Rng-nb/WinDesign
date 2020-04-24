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
	dkvalue = 0;
	data_show.clear();
	paint_info = nullptr;
}

CResultDlg::~CResultDlg() {
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

	std::string aim_str[2] = { "比例公平", "最大吞吐量" };
	std::string thoughoutjain_str[2] = { "Thoughout", "Jain" };
	std::string dispachtype_str[3] = { "比例公平调度", "轮询调度", "最大MCS调度" };
	std::string dispachlenth_str[3] = {"10ms", "20ms", "30ms"};
	std::string sta_num_str[3] = {"30", "50", "70"};
	std::string dispachtime_str[3] = {"100T", "200T", "500T"};
	std::string dispachnum_str[3] = {"3", "5", "8"};
	std::string dkvalue_str[3] = {"20M", "40M", "80M"};
	std::string str1; 
	std::string str2; 

	if (sta_num == -1) {
		str1 = "带宽" + std::to_string(dkvalue) + "M" + "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num) 
			+ " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同STA数量对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;

		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / len);
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));

		std::ofstream out_thoughout_jain(str3 + ".txt");
		out_thoughout_jain << thoughoutjain_str[thoughoutjain - 1] << std::endl;
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			COLORREF color;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				color = RGB(255, 0, 0);
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				color = RGB(0, 0, 0);
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				color = RGB(0, 0, 255);
			}

			dc.SelectObject(&pen);
			std::string str = sta_num_str[i];

			out_thoughout_jain << str << std::endl;
			double sum_thoughout_jain = 0.0;
			for (int k_tmp = 0; k_tmp < data_show.size(); ++k_tmp) {
				sum_thoughout_jain += data_show[k_tmp];
			}
			out_thoughout_jain << sum_thoughout_jain / data_show.size() << std::endl;

			CString csout(str.c_str());
			SetTextAlign(dc, VTA_RIGHT);
			SetTextColor(dc, color);
			dc.TextOutW(rect.right - 200, 50 + 20 * i, csout);

			setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
			dc.Polyline(paint_info, data_show.size());

			DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), len);
		}
		out_thoughout_jain.close();
	}
	else if (time == -1) {
		str1 = "带宽" + std::to_string(dkvalue) + "M" + "优化目标:" + aim_str[aim - 1] + " STA数量:" + std::to_string(sta_num) + " 调度数量:" + std::to_string(dispachnum)
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

		int max_len = -1;

		for (int i = 0; i < 3; ++i) {
			time_list[i] > max_len ? max_len = time_list[i] : max_len = max_len;
		}
		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / max_len);
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));

		std::ofstream out_thoughout_jain(str3 + ".txt");
		out_thoughout_jain << thoughoutjain_str[thoughoutjain - 1] << std::endl;
		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			int len = time_list[i];
			for (int j = lenlen; j < lenlen + len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			COLORREF color;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				color = RGB(255, 0, 0);
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				color = RGB(0, 0, 0);
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				color = RGB(0, 0, 255);
			}

			dc.SelectObject(&pen);
			std::string str = dispachtime_str[i];
			out_thoughout_jain << str << std::endl;
			double sum_thoughout_jain = 0.0;
			for (int k_tmp = 0; k_tmp < data_show.size(); ++k_tmp) {
				sum_thoughout_jain += data_show[k_tmp];
			}
			out_thoughout_jain << sum_thoughout_jain / data_show.size() << std::endl;

			CString csout(str.c_str());
			SetTextAlign(dc, VTA_RIGHT);
			SetTextColor(dc, color);
			dc.TextOutW(rect.right - 200, 50 + 20 * i, csout);

			setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
			dc.Polyline(paint_info, data_show.size());
			lenlen += len;

			DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), max_len);
		}
	}
	else if (dispachnum == -1) {
		str1 = "带宽" + std::to_string(dkvalue) + "M" + "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num)
			+ " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度数量对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		
		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / len);
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));

		std::ofstream out_thoughout_jain(str3 + ".txt");
		out_thoughout_jain << thoughoutjain_str[thoughoutjain - 1] << std::endl;

		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			COLORREF color;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				color = RGB(255, 0, 0);
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				color = RGB(0, 0, 0);
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				color = RGB(0, 0, 255);
			}

			dc.SelectObject(&pen);
			std::string str = sta_num_str[i];
			out_thoughout_jain << str << std::endl;
			double sum_thoughout_jain = 0.0;
			for (int k_tmp = 0; k_tmp < data_show.size(); ++k_tmp) {
				sum_thoughout_jain += data_show[k_tmp];
			}
			out_thoughout_jain << sum_thoughout_jain / data_show.size() << std::endl;

			CString csout(str.c_str());
			SetTextAlign(dc, VTA_RIGHT);
			SetTextColor(dc, color);
			dc.TextOutW(rect.right - 200, 50 + 20 * i, csout);
			
			setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
			dc.Polyline(paint_info, data_show.size());

			DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), len);
		}
	}
	else if (dispachlenth == -1) {
		str1 = "带宽" + std::to_string(dkvalue) + "M" + "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num)
			+ " 调度数量:" + std::to_string(dispachnum);
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度周期对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		
		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / len);
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));

		std::ofstream out_thoughout_jain(str3 + ".txt");
		out_thoughout_jain << thoughoutjain_str[thoughoutjain - 1] << std::endl;

		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			COLORREF color;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				color = RGB(255, 0, 0);
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				color = RGB(0, 0, 0);
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				color = RGB(0, 0, 255);
			}

			dc.SelectObject(&pen);
			std::string str = dispachlenth_str[i];

			out_thoughout_jain << str << std::endl;
			double sum_thoughout_jain = 0.0;
			for (int k_tmp = 0; k_tmp < data_show.size(); ++k_tmp) {
				sum_thoughout_jain += data_show[k_tmp];
			}
			out_thoughout_jain << sum_thoughout_jain / data_show.size() << std::endl;

			CString csout(str.c_str());
			SetTextAlign(dc, VTA_RIGHT);
			SetTextColor(dc, color);
			dc.TextOutW(rect.right - 200, 50 + 20 * i, csout);

			setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
			dc.Polyline(paint_info, data_show.size());

			DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), len);
		}
	}
	else if (dispachtype == -1) {
		str1 = "带宽" + std::to_string(dkvalue) + "M" + "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) + "T" + " STA数量:" + std::to_string(sta_num)
			+ " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同调度机制对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;
		
		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / len);
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));
		
		std::ofstream out_thoughout_jain(str3 + ".txt");
		out_thoughout_jain << thoughoutjain_str[thoughoutjain - 1] << std::endl;

		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			COLORREF color;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				color = RGB(255, 0, 0);
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				color = RGB(0, 0, 0);
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				color = RGB(0, 0, 255);
			}
			
			dc.SelectObject(&pen);
			std::string str = dispachtype_str[i];
			
			out_thoughout_jain << str << std::endl;
			double sum_thoughout_jain = 0.0;
			for (int k_tmp = 0; k_tmp < data_show.size(); ++k_tmp) {
				sum_thoughout_jain += data_show[k_tmp];
			}
			out_thoughout_jain << sum_thoughout_jain / data_show.size() << std::endl;

			CString csout(str.c_str());
			SetTextAlign(dc, VTA_RIGHT);
			SetTextColor(dc, color);
			dc.TextOutW(rect.right - 200 , 50 + 20 * i, csout);
			
			setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
			dc.Polyline(paint_info, data_show.size());

			DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), len);
		}
	}
	else if (dkvalue == -1) {
		str1 =  "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) +
		"T" + " STA数量:" + std::to_string(sta_num) + " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		std::string	str3 = "不同带宽对比";
		CString csout3(str3.c_str());
		SetTextAlign(dc, VTA_CENTER);
		dc.TextOutW(rect.right / 2, 40, csout3);
		int len = data_show.size() / 3;
		std::vector<double> tmp;
		tmp = data_show;

		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / len);
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));

		std::ofstream out_thoughout_jain(str3 + ".txt");
		out_thoughout_jain << thoughoutjain_str[thoughoutjain - 1] << std::endl;

		for (int i = 0; i < 3; ++i) {
			data_show.clear();
			for (int j = i * len; j < (i + 1) * len; ++j) {
				data_show.push_back(tmp[j]);
			}
			CPen pen;
			COLORREF color;
			if (i == 0) {
				pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
				color = RGB(255, 0, 0);
			}
			else if (i == 1) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
				color = RGB(0, 0, 0);
			}
			else if (i == 2) {
				pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
				color = RGB(0, 0, 255);
			}

			dc.SelectObject(&pen);
			std::string str = dkvalue_str[i];

			out_thoughout_jain << str << std::endl;
			double sum_thoughout_jain = 0.0;
			for (int k_tmp = 0; k_tmp < data_show.size(); ++k_tmp) {
				sum_thoughout_jain += data_show[k_tmp];
			}
			out_thoughout_jain << sum_thoughout_jain / data_show.size() << std::endl;

			CString csout(str.c_str());
			SetTextAlign(dc, VTA_RIGHT);
			SetTextColor(dc, color);
			dc.TextOutW(rect.right - 200, 50 + 20 * i, csout);

			setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
			dc.Polyline(paint_info, data_show.size());
			
			DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), len);
		}
	}
	else {
		str1 = "带宽" + std::to_string(dkvalue) + "M" + "优化目标:" + aim_str[aim - 1] + " 调度时间:" + std::to_string(time) +
			"T" + " STA数量:" + std::to_string(sta_num) + " 调度数量:" + std::to_string(dispachnum) + " 调度周期" + std::to_string((int)dispachlenth) + "ms";
		str2 = " 调度机制:" + dispachtype_str[dispachtype - 1] + " 性能参数:" + thoughoutjain_str[thoughoutjain - 1];
		double max = 0.0;
		int basex_size = 0;
		int basey_size = 0;
		for (int i = 0; i < data_show.size(); ++i) {
			data_show[i] > max ? max = data_show[i] : max = max;
		}
		basex_size = std::floor((rect.right - 100) / data_show.size());
		basey_size = std::floor((rect.bottom - 100) / std::ceil(max));

		CPen pen;
		pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
		dc.SelectObject(&pen);

		setxy(rect.right - 100, rect.bottom - 100, basex_size, basey_size);
		dc.Polyline(paint_info, data_show.size());

		DrawXY(dc, rect.right - 100, rect.bottom - 100, std::ceil(max), data_show.size());
	}
	
	CString csout1(str1.c_str());
	SetTextAlign(dc, VTA_CENTER);
	SetTextColor(dc, RGB(0, 0, 0));
	dc.TextOutW(rect.right / 2, 0, csout1);

	CString csout2(str2.c_str());
	SetTextAlign(dc, VTA_CENTER);
	SetTextColor(dc, RGB(0, 0, 0));
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
void CResultDlg::setxy(double w, double l, int basex, int basey) {
	paint_info = new CPoint[data_show.size()];
	for (int i = 0; i < data_show.size(); ++i) {
		CPoint p;
		p.x = i * basex + 50;
		p.y = l - std::ceil(data_show[i] * basey) + 50;
		paint_info[i] = p;
	}
}

void CResultDlg::DrawXY(CPaintDC & dc, int w, int l, double maxy, int maxx) {
	SetTextColor(dc, RGB(0, 0, 0));
	std::string	str;
	if (thoughoutjain == 1)
		str = "吞吐量(Mb/s)";
	else
		str = "Jain系数";
	CString cs1(str.c_str());
	SetTextAlign(dc, VTA_CENTER);
	dc.TextOutW(50, 30, cs1);
	
	str = std::to_string(0);
	CString cs2(str.c_str());
	dc.TextOutW(50, 55 + l, cs2);

	str = "调度时间(T)";
	CString cs3(str.c_str());
	dc.TextOutW(50 + w, 60 + l, cs3);

	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	dc.SelectObject(&pen);
	Drawxy(dc, w, l, maxy, maxx);
}

void CResultDlg::Drawxy(CPaintDC & dc, int width, int height, double maxy, int maxx) {
	SetTextColor(dc, RGB(0, 0, 0));
	dc.MoveTo(50, height + 50);
	dc.LineTo(50, 50);
	dc.MoveTo(50, 50);
	dc.LineTo(40, 70);
	dc.MoveTo(50, 50);
	dc.LineTo(60, 70);
	dc.MoveTo(50, height + 50);
	dc.LineTo(width + 50, height + 50);
	dc.MoveTo(width + 50, height + 50);
	dc.LineTo(width + 30, height + 60);
	dc.MoveTo(width + 50, height + 50);
	dc.LineTo(width + 30, height + 40);
	for (int i = 1; i < 5; ++i) {
		dc.MoveTo(50, 50 + height / 5 * i);
		dc.LineTo(55, 50 + height / 5 * i);
		std::string	str = std::to_string((std::ceil(maxy) / 5 * (5 - i)));
		CString cs1(str.c_str());
		int p_point = cs1.ReverseFind('.');
		cs1 = cs1.Left(cs1.GetLength() - p_point - 2);
		SetTextAlign(dc, TA_RIGHT);
		dc.TextOutW(50, 40 + height / 5 * i, cs1);
	}
	for (int i = 1; i < 10; ++i) {
		dc.MoveTo(50 + width / 10 * i, 50 + height);
		dc.LineTo(50 + width / 10 * i, 45 + height);
		std::string	str = std::to_string(maxx / 10 * i);
		CString cs1(str.c_str());
		SetTextAlign(dc, TA_CENTER);
		dc.TextOutW(50 + width / 10 * i, 55 + height, cs1);
	}
}