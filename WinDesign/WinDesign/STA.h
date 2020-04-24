#include <map>
#include <deque>
#include <vector>
#include <random>
#include <fstream>
#include <iostream>
typedef struct {
	double time;
	double info_speed;
	int info_num;
}Info;

class STA {
public:
	STA();
	~STA();
	void produceInfo();
	void getDispach(double &timeleft);//��STA���ڶ��ֵ���
	double getPrivity_f1(int timenow);//��ø�STA��ǰ�����ȼ�,������ƽ
	double getPrivity_f2(int timenow);//���������

	std::deque<Info> info_produce;//��Ų�������Ϣ
	std::vector<Info> info_dispached;//��ŵ��ȹ�����Ϣ

private:
	double speed[8] = { 1.5, 2.25, 3, 4.5, 6, 9, 12, 13.5 };//�ٶ���Ϣ
	double lambda_ex_time;//ʱ�����ָ���ֲ�
	double lambda_po_info;//���ݷ��ϲ��ɷֲ�
	double channel_speed;//�ٶ�

	std::random_device rd;//���������һ��������ӣ���Ȼÿ�����������ʱ��ͬ
	std::default_random_engine random{ rd() };//���������
};

