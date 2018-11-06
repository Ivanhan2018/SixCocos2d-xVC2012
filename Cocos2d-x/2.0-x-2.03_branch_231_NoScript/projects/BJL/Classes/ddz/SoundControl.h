//  [4/9/2014 xieyi]
#ifndef __SOUNDCONTROL__
#define __SOUNDCONTROL__
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;
USING_NS_CC;

//������Ч��Դ
namespace sound_name
{
	const static char s_bgMusic[] = "xyx_music/xyxbg.mp3";//��������
// 	//����
// 	const static char s_man_wav0[] = "soundeffect/man/wav0.wav";//������������
// 	const static char s_man_wav1[] = "soundeffect/man/wav1.wav";//������ٷ���������
// 	const static char s_man_wav2[] = "soundeffect/man/wav2.wav";//�ӵ���
// 	const static char s_man_wav3[] = "soundeffect/man/wav3.wav";//�Ʋ��ںá�����
// 	const static char s_man_wav4[] = "soundeffect/man/wav4.wav";//��Ҫ��ʼ�����ˡ�����
// 	const static char s_man_wav5[] = "soundeffect/man/wav5.wav";//���ߵ�̫��������
// 	const static char s_man_bujiabei[] = "soundeffect/man/bujiabei.wav";//���ӱ�
// 	const static char s_man_bujiao[] = "soundeffect/man/bujiao.wav";//����
// 	const static char s_man_buqiang[] = "soundeffect/man/buqiang.wav";//����
// 	const static char s_man_buyao[] = "soundeffect/man/buyao.wav";//��Ҫ
// 	const static char s_man_dani[] = "soundeffect/man/dani.wav";//����
// 	const static char s_man_feiji[] = "soundeffect/man/feiji.wav";//�ɻ�
// 	const static char s_man_guo[] = "soundeffect/man/guo.wav";//��
// 	const static char s_man_huojian[] = "soundeffect/man/huojian.wav";//huojian
// 	const static char s_man_jiabei[] = "soundeffect/man/jiabei.wav";//�ӱ�
// 	const static char s_man_jiaodizhu[] = "soundeffect/man/jiaodizhu.wav";//�е���
// 	const static char s_man_liandui[] = "soundeffect/man/liandui.wav";//����
// 	const static char s_man_mingpai[] = "soundeffect/man/mingpai.wav";//����
// 	const static char s_man_qiangdizhu[] = "soundeffect/man/qiangdizhu.wav";//������
// 	const static char s_man_sandaiyi[] = "soundeffect/man/sandaiyi.wav";//����һ
// 	const static char s_man_sandaier[] = "soundeffect/man/sandaier.wav";//����һ��
// 	const static char s_man_sanshun[] = "soundeffect/man/sanshun.wav";//��˳
// 	const static char s_man_sanzhang[] = "soundeffect/man/sanzhang.wav";//����
// 	const static char s_man_shunzi[] = "soundeffect/man/shunzi.wav";//˳��
// 	const static char s_man_sidaier[] = "soundeffect/man/sidaier.wav";//�Ĵ���
// 	const static char s_man_yasi[] = "soundeffect/man/yasi.wav";//ѹ��
// 	const static char s_man_yaobuqi[] = "soundeffect/man/yaobuqi.wav";//Ҫ����
// 	const static char s_man_yidui[] = "soundeffect/man/yidui.wav";//һ��
// 	const static char s_man_yizhang[] = "soundeffect/man/yizhang.wav";//һ��
// 	const static char s_man_zhadan[] = "soundeffect/man/zhadan.wav";//ը��

	//Ů��

// 	const static char s_woman_wav0[] = "soundeffect/woman/wav0.wav";//������������
// 	const static char s_woman_wav1[] = "soundeffect/woman/wav1.wav";//������ٷ���������
// 	const static char s_woman_wav2[] = "soundeffect/woman/wav2.wav";//�ӵ���
// 	const static char s_woman_wav3[] = "soundeffect/woman/wav3.wav";//�Ʋ��ںá�����
// 	const static char s_woman_wav4[] = "soundeffect/woman/wav4.wav";//��Ҫ��ʼ�����ˡ�����
// 	const static char s_woman_wav5[] = "soundeffect/woman/wav5.wav";//���ߵ�̫��������
// 	const static char s_woman_bujiabei[] = "soundeffect/woman/bujiabei.wav";//���ӱ�
// 	const static char s_woman_bujiao[] = "soundeffect/woman/bujiao.wav";//����
// 	const static char s_woman_buqiang[] = "soundeffect/woman/buqiang.wav";//����
// 	const static char s_woman_buyao[] = "soundeffect/woman/buyao.wav";//��Ҫ
// 	const static char s_woman_dani[] = "soundeffect/woman/dani.wav";//����
// 	const static char s_woman_feiji[] = "soundeffect/woman/feiji.wav";//�ɻ�
// 	const static char s_woman_guo[] = "soundeffect/woman/guo.wav";//��
// 	const static char s_woman_huojian[] = "soundeffect/woman/huojian.wav";//huojian
// 	const static char s_woman_jiabei[] = "soundeffect/woman/jiabei.wav";//�ӱ�
// 	const static char s_woman_jiaodizhu[] = "soundeffect/woman/jiaodizhu.wav";//�е���
// 	const static char s_woman_liandui[] = "soundeffect/woman/liandui.wav";//����
// 	const static char s_woman_mingpai[] = "soundeffect/woman/mingpai.wav";//����
// 	const static char s_woman_qiangdizhu[] = "soundeffect/woman/qiangdizhu.wav";//������
// 	const static char s_woman_sandaiyi[] = "soundeffect/woman/sandaiyi.wav";//����һ
// 	const static char s_woman_sandaier[] = "soundeffect/woman/sandaier.wav";//����һ��
// 	const static char s_woman_sanshun[] = "soundeffect/woman/sanshun.wav";//��˳
// 	const static char s_woman_sanzhang[] = "soundeffect/woman/sanzhang.wav";//����
// 	const static char s_woman_shunzi[] = "soundeffect/woman/shunzi.wav";//˳��
// 	const static char s_woman_sidaier[] = "soundeffect/woman/sidaier.wav";//�Ĵ���
// 	const static char s_woman_yasi[] = "soundeffect/woman/yasi.wav";//ѹ��
// 	const static char s_woman_yaobuqi[] = "soundeffect/woman/yaobuqi.wav";//Ҫ����
// 	const static char s_woman_yidui[] = "soundeffect/woman/yidui.wav";//һ��
// 	const static char s_woman_yizhang[] = "soundeffect/woman/yizhang.wav";//һ��
// 	const static char s_woman_zhadan[] = "soundeffect/woman/zhadan.wav";//ը��

	const static char s_wav0[] = "wav0.mp3";//������������
	const static char s_wav1[] = "wav1.mp3";//������ٷ���������
	const static char s_wav2[] = "wav2.mp3";//�ӵ���
	const static char s_wav3[] = "wav3.mp3";//�Ʋ��ںá�����
	const static char s_wav4[] = "wav4.mp3";//��Ҫ��ʼ�����ˡ�����
	const static char s_wav5[] = "wav5.mp3";//���ߵ�̫��������
	const static char s_bujiabei[] = "bujiabei.mp3";//���ӱ�
	const static char s_bujiao[] = "bujiao.mp3";//����
	const static char s_buqiang[] = "buqiang.mp3";//����
	const static char s_buyao[] = "buyao.mp3";//��Ҫ
	const static char s_dani[] = "dani.mp3";//����
	const static char s_feiji[] = "feiji.mp3";//�ɻ�
	const static char s_guo[] = "guo.mp3";//��
	const static char s_huojian[] = "huojian.mp3";//huojian
	const static char s_jiabei[] = "jiabei.mp3";//�ӱ�
	const static char s_jiaodizhu[] = "jiaodizhu.mp3";//�е���
	const static char s_liandui[] = "liandui.mp3";//����
	const static char s_mingpai[] = "mingpai.mp3";//����
	const static char s_qiangdizhu[] = "qiangdizhu.mp3";//������
	const static char s_sandaiyi[] = "sandaiyi.mp3";//����һ
	const static char s_sandaier[] = "sandaier.mp3";//����һ��
	const static char s_sanshun[] = "sanshun.mp3";//��˳
	const static char s_sanzhang[] = "sanzhang.mp3";//����
	const static char s_shunzi[] = "shunzi.mp3";//˳��
	const static char s_sidaier[] = "sidaier.mp3";//�Ĵ���
	const static char s_yasi[] = "yasi.mp3";//ѹ��
	const static char s_yaobuqi[] = "yaobuqi.mp3";//Ҫ����
	const static char s_yidui[] = "yidui.mp3";//һ��
	const static char s_yizhang[] = "yizhang.mp3";//һ��
	const static char s_zhadan[] = "zhadan.mp3";//ը��

	//������Ч
	const static char s_ct_fapai[] = "soundeffect/ct_fapai.mp3";//����
	const static char s_ct_feiji[] = "soundeffect/ct_feiji.mp3";//�ɻ�
	const static char s_ct_huojian[] = "soundeffect/ct_huojian.mp3";//���
	const static char s_ct_liandui[] = "soundeffect/ct_liandui.mp3";//����
	const static char s_ct_sanshun[] = "soundeffect/ct_sanshun.mp3";//��˳
	const static char s_ct_zhadan[] = "soundeffect/ct_zhadan.mp3";//ը��
	const static char s_ct_shunzi[] = "soundeffect/ct_shunzi.mp3";//˳��
	//������Ч
	const static char s_winner[] = "soundeffect/winner.mp3";//ʤ��
	const static char s_loser[] = "soundeffect/loser.mp3";//ʧ��
	//������Ч
	const static char s_warning[] = "soundeffect/warning.mp3";//����

}

class SoundControl
{
public:
	SoundControl();
	~SoundControl();
	static SoundControl * sharedSoundControl();		//��ò��������ĵ���
	void playSoundEffect(const char * soundName);	//������Ч
	void playBackGroundMusic(const char * soundName,bool loop);	//���ű�������
	void coloseBackGroundMusic();
	void setVoiceIsOpen(bool var);					//��������
	void setSoundEffVol(float vol);					//��Ч����
	void setMusicVol(float vol);						//������������

private:
	bool m_voiceIsOpen;		//true��ʾ�ر�����
	float m_soundEffVol;
	float m_musicVol;
};

struct Tag 
{
	unsigned int userId;//�û�id
	unsigned int gender;//�Ա�
};

class SoundEffect
{
public:
	SoundEffect();
	~SoundEffect();
	static SoundEffect * sharedSoundEffect();
	void playEffect(const char * soundName,int userId);
	void playPassEffect(int userId);
	void playDaPaiEffect(int userId);
	void initLeftTag(Tag left);
	void initRightTag(Tag right);
	void initSelfTag(Tag self);

public:
	Tag m_leftUser;//�ϼ�
	Tag m_self;//�Լ�
	Tag m_rightUser;//�¼�
};

#endif