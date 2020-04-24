#pragma once
#include "STA.h"

class  Dispach {
public:
	std::vector<double> jain_vector;
	std::vector<double> thoughtout_vector;
private:
	int aim;
	int type;
	int time;
	int dkvalue;
	int sta_num;
	int dispachnum;
	int dispachedtime;
	double dispachlenth;
	std::vector<STA*> sta_info;//储存信息源
	std::vector<STA*> sta_info_init;
	std::vector<std::pair<int, double>> privity;//存储一次调度的各个优先级
	std::vector<int> dispach_id;//存储一个调度选择的id
	std::vector<int> info;
	std::vector<double> speed;//存储Jain计算的系数
	std::vector<double> cost;

public:
	Dispach();
	~Dispach();
	void produceInfo();
	void clearInfo();
	void initInfo(int sta_num);
	void startDispach(int type);
	void setDispach(int time, int dispachnum, double dispachlenth);

private:
	void getPrivityRR(int i);
	void getPrivityPF(int i);
	void getPrivityMCS(int i);
	void getThoughoutJain(double timeleft, double &thoughout, double &jain);
	void function1();//比例公平调度
	void function2();//轮询调度
	void function3();//以最大吞吐量为基准调度
};