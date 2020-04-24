#pragma once
#include "pch.h"
#include "Dispach.h"
#include <string>

Dispach::Dispach() {
	aim = 1;
	type = 1;
	time = 200;
	sta_num = 50;
	dispachnum = 8;
	dispachedtime = 0;
	dispachlenth = 20.0;
	dkvalue = 20;
	sta_info.clear();
	sta_info_init.clear();
	privity.clear();
	dispach_id.clear();
	speed.clear();
	info.clear();
	cost.clear();
	thoughtout_vector.clear();
	jain_vector.clear();
}

Dispach::~Dispach() {
}

void Dispach::setDispach(int time, int dispachnum, double dispachlenth) {
	this->time = time;
	this->dispachnum = dispachnum;
	this->dispachlenth = dispachlenth;
}

void Dispach::startDispach(int type) {
	
	switch (type) {
	case 1:
		this->aim = 1;
		this->type = type;
		function1();//������ƽ���ȣ�������ƽ�Ż�
		break;
	case 2:
		this->aim = 1;
		this->type = type;
		function2();//��ѯ���ȣ�������ƽ�Ż�
		break;
	case 3:
		this->aim = 1;
		this->type = type;
		function3();//������������ȣ�������ƽ�Ż�
		break;
	case 4:
		this->aim = 2;
		this->type = type;
		function1();//������ƽ���ȣ�����������Ż�
		break;
	case 5:
		this->aim = 2;
		this->type = type;
		function2();//��ѯ����,����������Ż�
		break;
	case 6:
		this->aim = 2;
		this->type = type;
		function3();//�������������,����������Ż�
		break;
	default:
		break;
	}
}

void Dispach::produceInfo(int dkvalue) {
	this->dkvalue = dkvalue;
	std::ofstream data("data.txt");
	for (int i = 0; i < 100; ++i) {
		STA *sta = new STA();
		sta->produceInfo();
		sta_info_init.push_back(sta);
		data << "STA " << i << std::endl;//����д���ļ�
		for (int j = 0; j < sta->info_produce.size(); ++j) {
			data << "time:" << sta->info_produce[j].time << " speed:" << sta->info_produce[j].info_speed << " num:" << sta->info_produce[j].info_num << std::endl;
		}
		data << std::endl;
	}
	data.close();
}

void Dispach::clearInfo() {
	sta_info.clear();
	sta_info_init.clear();
	info.clear();
	speed.clear();
	cost.clear();
	thoughtout_vector.clear();
	jain_vector.clear();
}

void Dispach::initInfo(int sta_num) {
	this->sta_num = sta_num;
	sta_info.clear();
	if (dkvalue == -1) {
		int dkvalue_list[3] = {20, 40, 80};
		for (int i = 0; i < 3; ++i) {
			int n = dkvalue_list[i] / 20;
			for (int k = 0; k < sta_num; ++k) {
				STA *tmp = new STA();
				for (int j = 0; j < sta_info_init[k]->info_produce.size(); ++j) {
					Info tmp_info = sta_info_init[k]->info_produce[j];
					tmp_info.info_speed *= n;
					tmp->info_produce.push_back(tmp_info);
				}
				sta_info.push_back(tmp);
			}
		}
	}
	else {
		int n = dkvalue / 20;
		for (int i = 0; i < sta_num; ++i) {
			STA *tmp = new STA();
			for (int j = 0; j < sta_info_init[i]->info_produce.size(); ++j) {
				Info tmp_info = sta_info_init[i]->info_produce[j];
				tmp_info.info_speed *= n;
				tmp->info_produce.push_back(tmp_info);
			}
			sta_info.push_back(tmp);
		}
	}	
}

void Dispach::getPrivityRR(int i) {//��ѯ�����������ȼ�
	int j = 0;
	double privity_tmp = 0.0;
	if (aim == 1)
		privity_tmp = sta_info[i]->getPrivity_f1(dispachedtime);//������ƽ
	else
		privity_tmp = sta_info[i]->getPrivity_f2(dispachedtime);//���������
	for (j = 0; j < privity.size(); ++j) {
		if (privity_tmp > privity[j].second)
			break;
	}
	privity.insert(privity.begin() + j, std::pair<int, double>(i, privity_tmp));
}

void Dispach::getPrivityPF(int i) {//������ƽ�������ȼ�
	int j = 0;
	double privity_tmp = 0.0;
	privity_tmp = sta_info[i]->getPrivity_f1(dispachedtime);
	for (j = 0; j < privity.size(); ++j) {
		if (privity_tmp > privity[j].second)
			break;
	}
	privity.insert(privity.begin() + j, std::pair<int, double>(i, privity_tmp));
}

void Dispach::getPrivityMCS(int i) {//���MCS�������ȼ�
	int j = 0;
	double privity_tmp = 0.0;
	privity_tmp = sta_info[i]->getPrivity_f2(dispachedtime);
	for (j = 0; j < privity.size(); ++j) {
		if (privity_tmp > privity[j].second)
			break;
	}
	privity.insert(privity.begin() + j, std::pair<int, double>(i, privity_tmp));
}

void Dispach::getThoughoutJain(double timeleft, double & thoughout, double & jain) {
	int info_sum = 0;
	int m = 0;
	double cost_sum = 0.0;
	double speedsum_x = 0.0;
	double speedsum_xx = 0.0;

	for (int i = 0; i < dispach_id.size(); ++i) {//���ȣ�ÿ�ε��ȵ���Сʱ�䵥λΪ1ms,ʣ��ʱ��������������ȼ�
		sta_info[dispach_id[i]]->getDispach(timeleft);
		cost.push_back(sta_info[dispach_id[i]]->info_dispached.back().time);
		info.push_back(sta_info[dispach_id[i]]->info_dispached.back().info_num);
		speed.push_back(sta_info[dispach_id[i]]->info_dispached.back().info_speed);
	}

	m = speed.size();
	for (int i = 0; i < m; ++i) {
		speedsum_x += speed[i];
		speedsum_xx += speed[i] * speed[i];
		info_sum += info[i];
		cost_sum += cost[i];
	}
	thoughout = info_sum * 512.0 * 8.0 / (cost_sum / 1000.0) / 1000000;
	jain = speedsum_x * speedsum_x / (m * 1.0) / speedsum_xx;
}

void Dispach::function1() { //������ƽ����
	std::string str1("function");
	std::string str2(".txt");
	std::ofstream fc1(str1 + std::to_string(type) + str2);
	int time_dispach = 0;
	double thoughout = 0.0;
	double jain = 0.0;
	double timeleft = 0.0;
	initInfo(sta_num);
	thoughtout_vector.clear();
	jain_vector.clear();
	if (dkvalue != -1) {
		dispachedtime = 0;
		time_dispach = time;
		while (time_dispach--) {
			++dispachedtime;
			for (int i = 0; i < sta_info.size(); ++i) {//�õ��������ȼ�
				getPrivityPF(i);
			}
			for (int i = 0; i < privity.size() && i < dispachnum; ++i) {//ѡ�����ȼ���ߵ�n������
				dispach_id.push_back(privity[i].first);
			}
			//�����Ż�Ŀ���������ȼ�
			if (aim == 2) {//����������Ż�������mcsֵ�������ȼ�������Դ
				std::vector<std::pair<int, double> > tmp;
				tmp.clear();
				for (int i = 0; i < dispach_id.size(); ++i) {
					int j = 0;
					double mcs_tmp = 0.0;
					mcs_tmp = sta_info[dispach_id[i]]->getPrivity_f2(dispachedtime);
					for (j = 0; j < tmp.size(); ++j) {
						if (mcs_tmp > tmp[j].second)
							break;
					}
					tmp.insert(tmp.begin() + j, std::pair<int, double>(dispach_id[i], mcs_tmp));
				}
				dispach_id.clear();
				for (int i = 0; i < tmp.size(); ++i) {//ѡ�����ȼ���ߵ�n������
					dispach_id.push_back(tmp[i].first);
				}
				tmp.clear();
			}

			timeleft = dispachlenth - dispachnum * 1.0;//��������
			speed.clear();
			cost.clear();
			info.clear();
			getThoughoutJain(timeleft, thoughout, jain);
			thoughtout_vector.push_back(thoughout);
			jain_vector.push_back(jain);
			fc1 << "��������" << thoughout << "Mb/s" << std::endl;
			fc1 << "Jain��" << jain << std::endl;
			privity.clear();
			dispach_id.clear();
		}
	}
	else {
		for (int m_t = 0; m_t < 3; ++m_t) {
			dispachedtime = 0;
			time_dispach = time;
			int len = sta_info.size() / 3;
			while (time_dispach--) {
				++dispachedtime;
				for (int i = len * m_t; i < len * (m_t + 1); ++i) {//�õ��������ȼ�
					getPrivityPF(i);
				}
				for (int i = 0; i < privity.size() && i < dispachnum; ++i) {//ѡ�����ȼ���ߵ�n������
					dispach_id.push_back(privity[i].first);
				}
				//�����Ż�Ŀ���������ȼ�
				if (aim == 2) {//����������Ż�������mcsֵ�������ȼ�������Դ
					std::vector<std::pair<int, double> > tmp;
					tmp.clear();
					for (int i = 0; i < dispach_id.size(); ++i) {
						int j = 0;
						double mcs_tmp = 0.0;
						mcs_tmp = sta_info[dispach_id[i]]->getPrivity_f2(dispachedtime);
						for (j = 0; j < tmp.size(); ++j) {
							if (mcs_tmp > tmp[j].second)
								break;
						}
						tmp.insert(tmp.begin() + j, std::pair<int, double>(dispach_id[i], mcs_tmp));
					}
					dispach_id.clear();
					for (int i = 0; i < tmp.size(); ++i) {//ѡ�����ȼ���ߵ�n������
						dispach_id.push_back(tmp[i].first);
					}
					tmp.clear();
				}

				timeleft = dispachlenth - dispachnum * 1.0;//��������
				speed.clear();
				cost.clear();
				info.clear();
				getThoughoutJain(timeleft, thoughout, jain);
				thoughtout_vector.push_back(thoughout);
				jain_vector.push_back(jain);
				fc1 << "��������" << thoughout << "Mb/s" << std::endl;
				fc1 << "Jain��" << jain << std::endl;
				privity.clear();
				dispach_id.clear();
			}
		}
	}
	speed.clear();
	cost.clear();
	info.clear();
	fc1.close();
}

void Dispach::function2() {//��ѯ����
	std::string str1("function");
	std::string str2(".txt");
	std::ofstream fc2(str1 + std::to_string(type) + str2);
	int start = 0;
	int end = dispachnum;
	int time_dispach = 0;
	double thoughout = 0.0;
	double jain = 0.0;
	double timeleft = 0.0;
	initInfo(sta_num);
	thoughtout_vector.clear();
	jain_vector.clear();
	if (dkvalue != -1) {
		dispachedtime = 0;
		time_dispach = time;
		while (time_dispach--) {
			++dispachedtime;
			if (start < end) {
				for (int i = start; i < end; ++i) {//�õ��������ȼ�
					getPrivityRR(i);//�����Ż�Ŀ���������ȼ�
				}
			}
			else {
				for (int i = start; i < sta_num; ++i) {
					getPrivityRR(i);
				}
				for (int i = 0; i < end; ++i) {
					getPrivityRR(i);
				}
			}
			for (int i = 0; i < privity.size() && i < dispachnum; ++i) {
				dispach_id.push_back(privity[i].first);
			}
			//���ȣ�ÿ�ε��ȵ���Сʱ�䵥λΪ1ms,ʣ��ʱ��������������ȼ�

			timeleft = dispachlenth - dispachnum * 1.0;
			speed.clear();
			cost.clear();
			info.clear();
			getThoughoutJain(timeleft, thoughout, jain);
			thoughtout_vector.push_back(thoughout);
			jain_vector.push_back(jain);
			fc2 << "��������" << thoughout << "Mb/s" << std::endl;
			fc2 << "Jain��" << jain << std::endl;
			start = (start + dispachnum) % sta_num;
			end = (end + dispachnum) % sta_num;
			privity.clear();
			dispach_id.clear();
		}
	}
	else {
		for (int m_t = 0; m_t < 3; ++m_t) {
			dispachedtime = 0;
			time_dispach = time;
			int len = sta_info.size() / 3;
			while (time_dispach--) {
				++dispachedtime;
				if (start < end) {
					for (int i = start; i < end; ++i) {//�õ��������ȼ�
						getPrivityRR(i + len * m_t);//�����Ż�Ŀ���������ȼ�
					}
				}
				else {
					for (int i = start; i < sta_num; ++i) {
						getPrivityRR(i + len * m_t);
					}
					for (int i = 0; i < end; ++i) {
						getPrivityRR(i + len * m_t);
					}
				}
				for (int i = 0; i < privity.size() && i < dispachnum; ++i) {
					dispach_id.push_back(privity[i].first);
				}
				//���ȣ�ÿ�ε��ȵ���Сʱ�䵥λΪ1ms,ʣ��ʱ��������������ȼ�

				timeleft = dispachlenth - dispachnum * 1.0;
				speed.clear();
				cost.clear();
				info.clear();
				getThoughoutJain(timeleft, thoughout, jain);
				thoughtout_vector.push_back(thoughout);
				jain_vector.push_back(jain);
				fc2 << "��������" << thoughout << "Mb/s" << std::endl;
				fc2 << "Jain��" << jain << std::endl;
				start = (start + dispachnum) % sta_num;
				end = (end + dispachnum) % sta_num;
				privity.clear();
				dispach_id.clear();
			}
		}
	}
	speed.clear();
	cost.clear();
	info.clear();
	fc2.close();
}

void Dispach::function3() { //���mcs����
	std::string str1("function");
	std::string str2(".txt");
	std::ofstream fc3(str1 + std::to_string(type) + str2);
	int time_dispach = 0;
	double thoughout = 0.0;
	double jain = 0.0;
	double timeleft = 0.0;
	initInfo(sta_num);
	thoughtout_vector.clear();
	jain_vector.clear();
	if (dkvalue != -1) {
		dispachedtime = 0;
		time_dispach = time;
		while (time_dispach--) {
			++dispachedtime;
			for (int i = 0; i < sta_info.size(); ++i) {//�õ��������ȼ�
				getPrivityMCS(i);
			}
			for (int i = 0; i < privity.size() && i < dispachnum; ++i) {//ѡ�����ȼ���ߵ�n������
				dispach_id.push_back(privity[i].first);
			}
			//�����Ż�Ŀ���������ȼ�
			if (aim == 1) {//������ƽ�Ż������ݱ�����ƽϵ���������ȼ�������Դ
				std::vector<std::pair<int, double> > tmp;
				tmp.clear();
				for (int i = 0; i < dispach_id.size(); ++i) {
					int j = 0;
					double mcs_tmp = 0.0;
					mcs_tmp = sta_info[dispach_id[i]]->getPrivity_f1(dispachedtime);
					for (j = 0; j < tmp.size(); ++j) {
						if (mcs_tmp > tmp[j].second)
							break;
					}
					tmp.insert(tmp.begin() + j, std::pair<int, double>(dispach_id[i], mcs_tmp));
				}
				dispach_id.clear();
				for (int i = 0; i < tmp.size(); ++i) {//ѡ�����ȼ���ߵ�n������
					dispach_id.push_back(tmp[i].first);
				}
				tmp.clear();
			}

			timeleft = dispachlenth - dispachnum * 1.0;//��������
			speed.clear();
			cost.clear();
			info.clear();
			getThoughoutJain(timeleft, thoughout, jain);
			thoughtout_vector.push_back(thoughout);
			jain_vector.push_back(jain);
			fc3 << "��������" << thoughout << "Mb/s" << std::endl;
			fc3 << "Jain��" << jain << std::endl;
			privity.clear();
			dispach_id.clear();
		}
	}
	else {
		for (int m_t = 0; m_t < 3; ++m_t) {
			dispachedtime = 0;
			time_dispach = time;
			int len = sta_info.size() / 3;
			while (time_dispach--) {
				for (int i = len * m_t; i < len * (m_t + 1); ++i) {//�õ��������ȼ�
					getPrivityMCS(i);
				}
				for (int i = 0; i < privity.size() && i < dispachnum; ++i) {//ѡ�����ȼ���ߵ�n������
					dispach_id.push_back(privity[i].first);
				}
				//�����Ż�Ŀ���������ȼ�
				if (aim == 1) {//������ƽ�Ż������ݱ�����ƽϵ���������ȼ�������Դ
					std::vector<std::pair<int, double> > tmp;
					tmp.clear();
					for (int i = 0; i < dispach_id.size(); ++i) {
						int j = 0;
						double mcs_tmp = 0.0;
						mcs_tmp = sta_info[dispach_id[i]]->getPrivity_f1(dispachedtime);
						for (j = 0; j < tmp.size(); ++j) {
							if (mcs_tmp > tmp[j].second)
								break;
						}
						tmp.insert(tmp.begin() + j, std::pair<int, double>(dispach_id[i], mcs_tmp));
					}
					dispach_id.clear();
					for (int i = 0; i < tmp.size(); ++i) {//ѡ�����ȼ���ߵ�n������
						dispach_id.push_back(tmp[i].first);
					}
					tmp.clear();
				}

				timeleft = dispachlenth - dispachnum * 1.0;//��������
				speed.clear();
				cost.clear();
				info.clear();
				getThoughoutJain(timeleft, thoughout, jain);
				thoughtout_vector.push_back(thoughout);
				jain_vector.push_back(jain);
				fc3 << "��������" << thoughout << "Mb/s" << std::endl;
				fc3 << "Jain��" << jain << std::endl;
				privity.clear();
				dispach_id.clear();
			}
		}
	}
	speed.clear();
	cost.clear();
	info.clear();
	fc3.close();
}