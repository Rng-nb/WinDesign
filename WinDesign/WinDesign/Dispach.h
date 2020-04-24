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
	std::vector<STA*> sta_info;//������ϢԴ
	std::vector<STA*> sta_info_init;
	std::vector<std::pair<int, double>> privity;//�洢һ�ε��ȵĸ������ȼ�
	std::vector<int> dispach_id;//�洢һ������ѡ���id
	std::vector<int> info;
	std::vector<double> speed;//�洢Jain�����ϵ��
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
	void function1();//������ƽ����
	void function2();//��ѯ����
	void function3();//�����������Ϊ��׼����
};