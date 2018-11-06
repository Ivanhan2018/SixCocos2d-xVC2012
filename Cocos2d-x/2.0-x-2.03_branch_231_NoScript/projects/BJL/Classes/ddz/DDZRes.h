//  [3/18/2014 wucan]

#ifndef		__DDZ_RES__
#define		__DDZ_RES__
#include "common/Define.h"
//--Notification message
#define MESSAGE_JNICONTROL				"message_jnicontrol"
#define MESSAGE_TOVIEW						"message_toview"
#define MESSAGE_TOLOGIC					"message_tologic"
#define MESSAGE_MENUCLICKED			"message_menuclicked"		//��ť����

//--jnicontrol message
enum
{
	MSG_JNI_Share=1,
	MSG_JNI_Task,
	MSG_JNI_Start,
	MSG_JNI_Recharge,
};

//--game Scene
enum
{
	SCENE_start=1,			//����
	SCENE_game,
	SCENE_endAgain
};

namespace texture_name
{
	//����ͼƬ��Դ
	//const static char s_cardTable[] = "cardtable.png";
	const static char s_cardTable[] = "myCardtable.png";
	const static char s_background[]="BJL/BJL_01.png";//����pic
	const static char s_table[] = "table.png";//����pic
	const static char s_usericon[] = "manicon.png";//�����ͷ��pic
	const static char s_womanIcon[] = "womanicon.png";//Ů���ͷ��
	const static char s_bujiao[] = "btn_bujiao.png";//���е���btn
	const static char s_buqiang[] = "btn_buqiang.png";//��������btn
	const static char s_one[] = "one.png";//����1 pic
	const static char s_two[] = "two.png";//2 pic
	const static char s_three[] = "three.png";//3 pic
	const static char s_four[] = "four.png";//4 pic
	const static char s_five[] = "five.png";//5 pic
	const static char s_times[] = "times.png";//���� pic
	const static char s_undouble[] = "btn_undouble.png";//���ӱ� btn
	const static char s_timer[] = "BJL_24.png";//��ʱ�� pic
	const static char s_timerNumber[] = "timernumber.png";//��ʱ������ pic
	const static char s_ChipMagerNumber[] = "SCORE_NUMBER.png";//��ע���� pic
	const static char s_TIME_NUMBERScore[] = "TIME_NUMBER.png";//��ע���� pic
	const static char s_goldCoin[] = "goldcoin.png";//��� pic
	const static char s_menubar[] = "menubar.png";// �˵���
	const static char s_recharge[] = "btn_recharge.png";//��ֵ btn
	//const static char s_exchange[] = "btn_exchange.png";//�һ� btn
	const static char s_coinNumber[]= "coinnumber.png";//�����
	const static char s_coinNumber1[] = "coinnumber1.png";
	const static char s_bigCard[] = "bigcard.png";//�ƴ�ͼ pic
	const static char s_showMenuBar[] = "showmenu.png";//�˵��� btn
	const static char s_double[]= "btn_double.png";//�ӱ� btn
	const static char s_jiaodizhu[] = "btn_jiaodizhu.png";//�е���
	const static char s_qiangdizhu[] = "btn_qdz.png";//������
	const static char s_start[] = "btn_start.png";//��ʼ��Ϸ
	const static char s_visibleCard[] = "btn_visiblecard.png";//����
	const static char s_visibleStart[] = "btn_visiblestart.png";//���ƿ�ʼ
	const static char s_settlementbg[] = "settlement_bg.png";//���㱳��
	const static char s_changeTable[] = "btn_changetable.png";//����
	const static char s_again[] = "btn_again.png";//����һ��
	const static char s_hint[] = "btn_hint.png";//��ʾ��ť
	const static char s_pass[] = "btn_pass.png";//����
	const static char s_outCard[] = "btn_outcard.png";//����
	const static char s_font_bujiao[] = "font_bujiao.png";//������
	const static char s_font_buqiang[] = "font_buqiang.png";//������
	const static char s_font_jiaodizhu[] = "font_jiaodizhu.png";//�е�����
	const static char s_font_pass[] = "font_pass.png";//������
	const static char s_font_qiangdizhu[] = "font_qiangdizhu.png";//��������
	const static char s_font_visiblecard[] = "font_visiblecard.png";//������
	const static char s_font_jiabei[] = "font_jiabei.png";//�ӱ���
	const static char s_font_hfd[] = "font_hfd.png";
	const static char s_x[] = "x.png";//X
	const static char s_menuBarBackground[] = "bg_menubar.png";//�˵�������
	const static char s_back[] = "btn_back.png";//���ذ�ť
	const static char s_options[] = "btn_options.png";//���ð�ť
	const static char s_pull[] = "btn_pull.png";//�˵�������
	const static char s_robot[] = "btn_robot.png";//�йܰ�ť
	const static char s_talk[] = "btn_talk.png";//���찴ť
	const static char s_task[] = "btn_task.png";//����ť
	const static char s_smallCard[] = "smallcard.png";//С�˿���ͼƬ
	const static char s_hintCard[] = "hintcard.png";//���ŵ��˿�ͼƬ
	const static char s_settlementDetial[] = "settlementdetial.png";//�鿴��ϸbtn
	const static char s_jiaBeiBar[] = "jbb_bj.png";//���Ƽӱ�������ʾ����ͼƬ
	const static char s_twice[] = "twice.png";//����
	const static char s_thrice[] = "thrice.png";//����
	const static char s_fourfold[] = "fourfold.png";//�ı�
	const static char s_fivefold[] = "fivefold.png";//�屶
	const static char s_nonuple[] = "nonuple.png";//�ű�
	const static char s_sixfold[] = "sixfold.png";//����
	const static char s_diZhuTag[] = "dizhutag.png";//������ǩ
	const static char s_showSelf[] = "showself.png";//���㣬��ʾ�Լ���Ŀʱ��ĵ�ͼ
	const static char s_ctDoubleLine[] = "ct_double_line.png";//����
	const static char s_ctSingleLine[] = "ct_single_line.png";//˳��
	const static char s_ctThreeLine[] = "ct_sthree_line.png";//��˳
	const static char s_jiaBeiTag[] = "jiabeitag.png";//����ʱ�ļӱ���־
	const static char s_music[] = "music.png";//��������ͼƬ
	const static char s_soundEffect[] = "soundeffect.png";//��ЧͼƬ
	const static char s_off[] = "off.png";//�ر���ͼƬ
	const static char s_on[] = "on.png";//������ͼƬ
	const static char s_on_off[] = "on_off.png";//����ͼƬ
	const static char s_progress_bj[] = "progressbar0.png";//����������
	const static char s_progress[] = "progressbar1.png";//������
	const static char s_setup_bg[] = "task_k.png";//���õ׿�
	const static char s_expression[] = "expression.png";//��������
	const static char s_voice[] = "voice.png";//��������
	//����
	const static char s_faceCool[] = "face_0.png";//��
	const static char s_faceHan[] = "face_1.png";//��
	const static char s_faceHanlen[] = "face_2.png";//����
	const static char s_faceKu[] = "face_3.png";//��
	const static char s_faceNu[] = "face_4.png";//ŭ
	const static char s_faceNue[] = "face_5.png";//Ű
	const static char s_faceQiu[] = "face_6.png";//��
	const static char s_faceTu[] = "face_7.png";//��
	const static char s_faceXiao[] = "face_8.png";//Ц
	const static char s_faceYun[] = "face_9.png";//��

	const static char s_confirm[] = "btn_confirm.png";//ȷ����ť
	const static char s_faceBg[] = "face_bg.png";//����򱳾�
	//const static char s_xlt[] = "xlt.png";//������
	const static char s_yyk[] = "yyk.png";//������
	const static char s_banshou[] = "banshou.png";//�����˰���
	const static char s_cancleRobot[] = "btn_cancelrobot.png";//ȡ���й�
	const static char s_eye[]= "eye.png";//�������۾�
	const static char s_robot_pic[] = "robot.png";//������ͼƬ
	const static char s_paiBei0[] = "paibei0.png";//�Ʊ�0
	const static char s_paiBei1[] = "paibei1.png";//�Ʊ�1
	const static char s_plane[] = "plane.png";//�ɻ�
	const static char s_lxj0[] = "lxj0.png";//������0
	const static char s_lxj1[] = "lxj1.png";//������1
	const static char s_planeyy[] = "planeyy.png";//�ɻ��������Ӱ
	const static char s_bomb[] = "bomb.png";//ը����
	const static char s_bomb0[] = "bomb0.png";//ը������0
	const static char s_bomb1[] = "bomb1.png";//ը������1
	const static char s_bomb2[] = "bomb2.png";//ը������2
	const static char s_bomb3[] = "bomb3.png";//ը������3
	const static char s_bomb4[] = "bomb4.png";//ը������4
	const static char s_bomb5[] = "bomb5.png";//ը������5
	const static char s_bomb6[] = "bomb6.png";//ը������6
	const static char s_bomb7[] = "bomb7.png";//ը������7
	const static char s_yanwu0[] = "yanwu0.png";//��������任����
	const static char s_yanwu1[] = "yanwu1.png";
	const static char s_yanwu2[] = "yanwu2.png";
	const static char s_yanwu3[] = "yanwu3.png";
	const static char s_yanwu4[] = "yanwu4.png";
	const static char s_dizhu_man[] = "dizhu_man.png";//�е���
	const static char s_farmer_man[] = "farmer_man.png";//��ũ��
	const static char s_dizhu_woman[] = "dizhu_woman.png";//Ů����
	const static char s_farmer_woman[] = "farmer_woman.png";//Ůũ��
	const static char s_btn_cancle[] = "btn_cancle.png";//ȡ����ť
	const static char s_huojian[] = "huojian.png";//���
	const static char s_huoyan[] = "huoyan.png";//����
	const static char s_yun0[] = "yun0.png";//�����
	const static char s_yun1[] = "yun1.png";
	const static char s_yun2[] = "yun2.png";
	const static char s_yun3[] = "yun3.png";
	const static char s_paizi[] = "paizi.png";//���˶�����ͼ
	const static char s_font_deng[] = "font_deng.png";//��
	const static char s_font_dai[] = "font_dai.png";//��
	const static char s_font_qi[] = "font_qi.png";//��
	const static char s_font_ta[] = "font_ta.png";//��
	const static char s_font_wan[] = "font_wan.png";//��
	const static char s_font_jia[] = "font_jia.png";//��
	const static char s_font_zhong[] = "font_zhong.png";//��
	const static char s_zawu[] = "zawu.png";//����
	const static char s_jingbao0[] = "jingbao0.png";//��������
	const static char s_jingbao1[] = "jingbao1.png";
	const static char s_jingbao2[] = "jingbao2.png";
	const static char s_jingbao3[] = "jingbao3.png";
	const static char s_jingbao4[] = "jingbao4.png";
	const static char s_jingbao5[] = "jingbao5.png";
	const static char s_loser[] = "loser.png";//ʧ�ܶ���
	const static char s_winner[] = "winner.png";//ʤ������
	const static char s_notify[] = "notify.png";//��Ϸ��������ʾ��Ϣ����
	const static char s_task_d[] = "task_d.png";//�������ֵ�
	const static char s_task_k[] = "task_k.png";//�����

	//���Сͷ��
	const static char s_man_head_icon[] = "man_head_icon.png";
	const static char s_woman_head_icon[] = "woman_head_icon.png";
	const static char s_userMessage[] = "usermessage.png";//�û���Ϣ��
	const static char s_dizhuCardTag[] = "dizhucardtag.png";//�������һ�ſ�Ƭ���Ͻ�ͼ��

	const static char s_xyx_headIcon[] = "xyx_headicon.png";//С��Ϸ�Լ�����ǰ���ͼ��
	const static char s_showCardTag[] = "showcardtag.png";//���Ʊ�־
	const static char s_difenTimesNum[] = "difentimesnum.png";//�׷ֱ�������
	//գ��ͼƬ
	const static char s_dz_m_eye0[] = "dz_m_eye0.png";//�е���գ��
	const static char s_dz_m_eye1[] = "dz_m_eye1.png";
	const static char s_dz_m_eye2[] = "dz_m_eye2.png";
	const static char s_dz_wm_eye0[] = "dz_wm_eye0.png";//Ů����գ��
	const static char s_dz_wm_eye1[] = "dz_wm_eye1.png";
	const static char s_dz_wm_eye2[] = "dz_wm_eye2.png";
	const static char s_fm_m_eye0[] = "fm_m_eye0.png";//��ũ��գ��
	const static char s_fm_m_eye1[] = "fm_m_eye1.png";
	const static char s_fm_m_eye2[] = "fm_m_eye2.png";
	const static char s_fm_wm_eye0[] = "fm_wm_eye0.png";//Ůũ��գ��
	const static char s_fm_wm_eye1[] = "fm_wm_eye1.png";
	const static char s_fm_wm_eye2[] = "fm_wm_eye2.png";
	const static char s_m_eye0[] = "m_eye0.png";//�к�գ��
	const static char s_m_eye1[] = "m_eye1.png";
	const static char s_m_eye2[] = "m_eye2.png";
	const static char s_wm_eye0[] = "wm_eye0.png";//Ů����գ��
	const static char s_wm_eye1[] = "wm_eye1.png";
	const static char s_wm_eye2[] = "wm_eye2.png";

	const static char s_font_difen[] = "font_difen.png";//�׷�ͼƬ

	const static char s_back_fen0[] = "back_fen0.png";//����
	const static char s_back_fen1[] = "back_fen1.png";
	const static char s_back_fen2[] = "back_fen2.png";

	const static char s_card_big_baiban[] = "card_big_baiban.png";//�˿��ƣ��󣩰װ�
	const static char s_card_small_baiban[] = "card_small_baiban.png";//�װ壨С��
	const static char s_card_color[] = "card_color.png";//�˿��ƻ�ɫ���ں췽÷��
	const static char s_card_num_black[] = "card_num_black.png";//�˿����ֺ�
	const static char s_card_num_red[] = "card_num_red.png";//�˿��ƺ�
	const static char s_joker[] = "joker.png";	//ͼƬ��СΪ pic
	const static char s_card[] ="card.png";//�˿���
	//������Դ
	const static char s_font_back[] = "font_back.png";//����
	const static char s_font_chat[] = "font_chat.png";//����
	const static char s_font_robot[] = "font_robot.png";//�й�
	const static char s_font_setup[] = "font_setup.png";//����
	const static char s_font_task[] = "font_task.png";//����
	const static char s_bubble[] = "bubble.png";//����
}
#endif