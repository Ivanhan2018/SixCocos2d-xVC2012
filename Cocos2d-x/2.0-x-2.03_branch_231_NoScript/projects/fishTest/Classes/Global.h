#pragma once
#include <vector>
const int pkWidth = 71;//�ƵĿ�
const int pkHeight = 96;//�Ƶĸ�
const int pkJianJu = 20;//������֮��ļ��
//��ɫ
enum HuaSe	
{
	HeiTao = 0,
	HongTao,
	MeiHua,
	FangKuai,
	Gui,
	HuaSeBM = 4     //��ɫ����
};
//�ƺ�
enum PaiHao
{
	San = 0,Si,Wu,Liu,Qi,Ba,Jiu,Shi,ShiYi,ShiEr,ShiSan,Yi,Er,XiaoGui,DaGui,
	PaiHaoBM=2 //�ƺű���
};
//��ǩ
enum BiaoQian
{
	FenShu,
	NpcTwoBuChu,
	NpcOneBuChu
};
//����������13������
enum CARD_TYPE
{
	SINGLE_CARD = 1,		//����-
	DOUBLE_CARD,			//����-
	THREE_CARD,				//3����-
	BOMB_CARD,				//ը��
	THREE_ONE_CARD,			//3��1-
	THREE_TWO_CARD,			//3��2-
	BOMB_TWO_CARD,			//�ĸ���2�ŵ���
	BOMB_TWOOO_CARD,		//�ĸ���2��
	CONNECT_CARD,			//����-
	COMPANY_CARD,			//����-
	AIRCRAFT_CARD,			//�ɻ�����-
	AIRCRAFT_SINGLE_CARD,	//�ɻ�������-
	AIRCRAFT_DOBULE_CARD,	//�ɻ�������-
	ERROR_CARD				//���������
} ;
struct CRAD_INDEX//�����ɻ����Ĵ���
{
	std::vector<int> single_index;//����
	std::vector<int> duble_index;//˫��
	std::vector<int> three_index;//����
	std::vector<int> four_index;//����
};
