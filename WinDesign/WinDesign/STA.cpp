#include "pch.h"
#include "STA.h"

STA::STA() {
	std::uniform_real_distribution<double> random_un(1, 5);//1-5���ȷֲ������double
	lambda_ex_time = random_un(random);//�趨һ������ĳ�ʼ��ֵ
	lambda_po_info = random_un(random);//�趨һ������ĳ�ʼ��ֵ
	info_dispached.clear();
}

STA::~STA() {
}

void STA::produceInfo() {
	int i = 500;//����Դ������
	bool flag_first = true; //��־��һ����Ϣ����
	double time_tmp = 0.0;
	std::exponential_distribution<double> random_time(lambda_ex_time);//ʱ�������ϲ���Ϊlambda1��ָ���ֲ�
	std::poisson_distribution<int> random_info(lambda_po_info);//ʱ����t�ڵ����������ϲ���Ϊlambda2*t�Ĳ��ɷֲ�
	std::uniform_int_distribution<int> random_un(1, 8);//���һ���ٶ�ֵ
	while (i--) {
		double time_rand = random_time(random);//���һ��ʱ����

		double lambda = lambda_po_info * time_rand * 1000; //��t�ʲ��ɷֲ�
		
		int info_rand = random_info(random);//���һ�����ݰ�����

		channel_speed = speed[random_un(random) - 1];

		Info info_tmp; //�洢������һ�������Ϣ
		flag_first == true ? info_tmp.time = 0.0, flag_first = false : info_tmp.time = time_tmp + time_rand * 10, time_tmp += time_rand * 10;
		info_tmp.info_speed = channel_speed * 4;
		info_tmp.info_num = info_rand;
		info_produce.push_back(info_tmp);
	}
}

//������ƽ�����ȼ�
double STA::getPrivity_f1(int timenow) {
	if (info_produce.front().time > (timenow - 1) * 10)
		return 0.0;
	double privity = 0.0;
	if (info_dispached.empty()) {//���û�б����ȹ����Ե�ǰ�ٶ�Ϊ���ȼ�
		privity = info_produce.front().info_speed;
	}
	else {//���������ȼ��㵱ǰ�ٶȳ���ƽ����Ϊ���ȼ�
		int sum_info = 0;
		double speed_now = info_produce.front().info_speed;
		double sum_time = 0.0;
		for (int j = 0; j < info_dispached.size(); ++j) {
			sum_info += info_dispached[j].info_num;
			sum_time += info_dispached[j].time;
		}
		privity = speed_now / (sum_info * 1.0 / sum_time);
	}
	return privity;
}

double STA::getPrivity_f2(int timenow) {
	if (info_produce.front().time > (timenow - 1) * 10)
		return 0.0;
	double privity = 0.0;
	privity = info_produce.front().info_speed;
	return privity;
}

void STA::getDispach(double &timeleft) {//�ȷ���1ms,������ʣ��ʱ����з���
	Info info_tmp;
	Info dispached;
	info_tmp = info_produce.front();
	info_produce.pop_front();
	dispached.info_speed = info_tmp.info_speed;
	int num_trans = (int)info_tmp.info_speed * 1000000.0 * 0.001 / 8.0 / 512.0;//����1ms�Ե�ǰ�ٶ��ܴ����������Ϊ���

	if (num_trans == info_tmp.info_num) {//1ms�������
		dispached.time = 1.0;
		dispached.info_num = num_trans;
	}
	else if (num_trans > info_tmp.info_num) {//1ms�ò���
		double time = info_tmp.info_num * 8.0 * 512.0 * 1000 / 1000000.0 / info_tmp.info_speed;//����Ϊms
		dispached.time = time;
		dispached.info_num = info_tmp.info_num;
	}
	else {//1ms������
		if (timeleft > 0) {//�����ȼ�ʣ��ʱ��������STA����
			int num_trans_now = (int)info_tmp.info_speed * 1000000.0 * (timeleft + 1) / 1000.0 / 8.0 / 512.0;//����ʣ����ʱ���Ե�ǰ�ٶ��ܴ����������Ϊ���

			if (num_trans_now == info_tmp.info_num) {
				dispached.time = timeleft + 1.0;
				dispached.info_num = num_trans;
			}
			else if (num_trans_now > info_tmp.info_num) {
				double time = info_tmp.info_num * 8.0 * 512.0 * 1000.0 / 1000000.0 / info_tmp.info_speed;//����Ϊms
				dispached.time = time;
				dispached.info_num = info_tmp.info_num;
				timeleft -= time;
			}
			else {
				info_tmp.info_num = info_tmp.info_num - num_trans_now;//ʣ�µ���Ϣ��
				dispached.info_num = num_trans_now;
				dispached.time = timeleft + 1;
				//���»��������׵���Ϣ
				std::uniform_int_distribution<int> random_un(1, 8);//���һ���ٶ�ֵ
				channel_speed = speed[random_un(random) - 1];
				info_tmp.info_speed = channel_speed * 4;
				info_produce.push_front(info_tmp);
				timeleft = 0.0;
			}
		}
		else {//�����ȼ���ʱ������
			info_tmp.info_num = info_tmp.info_num - num_trans;//ʣ�µ���Ϣ��
			dispached.info_num = num_trans;
			dispached.time = 1.0;
			//���»��������׵���Ϣ
			std::uniform_int_distribution<int> random_un(1, 8);//���һ���ٶ�ֵ
			channel_speed = speed[random_un(random) - 1];
			info_tmp.info_speed = channel_speed * 4;
			info_produce.push_front(info_tmp);
		}
	}
	info_dispached.push_back(dispached);
}
