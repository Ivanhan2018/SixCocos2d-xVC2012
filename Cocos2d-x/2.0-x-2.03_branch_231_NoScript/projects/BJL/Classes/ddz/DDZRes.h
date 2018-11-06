//  [3/18/2014 wucan]

#ifndef		__DDZ_RES__
#define		__DDZ_RES__
#include "common/Define.h"
//--Notification message
#define MESSAGE_JNICONTROL				"message_jnicontrol"
#define MESSAGE_TOVIEW						"message_toview"
#define MESSAGE_TOLOGIC					"message_tologic"
#define MESSAGE_MENUCLICKED			"message_menuclicked"		//按钮按下

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
	SCENE_start=1,			//大厅
	SCENE_game,
	SCENE_endAgain
};

namespace texture_name
{
	//所有图片资源
	//const static char s_cardTable[] = "cardtable.png";
	const static char s_cardTable[] = "myCardtable.png";
	const static char s_background[]="BJL/BJL_01.png";//背景pic
	const static char s_table[] = "table.png";//桌子pic
	const static char s_usericon[] = "manicon.png";//男玩家头像pic
	const static char s_womanIcon[] = "womanicon.png";//女玩家头像
	const static char s_bujiao[] = "btn_bujiao.png";//不叫地主btn
	const static char s_buqiang[] = "btn_buqiang.png";//不抢地主btn
	const static char s_one[] = "one.png";//倍数1 pic
	const static char s_two[] = "two.png";//2 pic
	const static char s_three[] = "three.png";//3 pic
	const static char s_four[] = "four.png";//4 pic
	const static char s_five[] = "five.png";//5 pic
	const static char s_times[] = "times.png";//倍字 pic
	const static char s_undouble[] = "btn_undouble.png";//不加倍 btn
	const static char s_timer[] = "BJL_24.png";//计时器 pic
	const static char s_timerNumber[] = "timernumber.png";//计时器数字 pic
	const static char s_ChipMagerNumber[] = "SCORE_NUMBER.png";//总注数字 pic
	const static char s_TIME_NUMBERScore[] = "TIME_NUMBER.png";//下注分数 pic
	const static char s_goldCoin[] = "goldcoin.png";//金币 pic
	const static char s_menubar[] = "menubar.png";// 菜单栏
	const static char s_recharge[] = "btn_recharge.png";//充值 btn
	//const static char s_exchange[] = "btn_exchange.png";//兑换 btn
	const static char s_coinNumber[]= "coinnumber.png";//金币字
	const static char s_coinNumber1[] = "coinnumber1.png";
	const static char s_bigCard[] = "bigcard.png";//牌大图 pic
	const static char s_showMenuBar[] = "showmenu.png";//菜单栏 btn
	const static char s_double[]= "btn_double.png";//加倍 btn
	const static char s_jiaodizhu[] = "btn_jiaodizhu.png";//叫地主
	const static char s_qiangdizhu[] = "btn_qdz.png";//抢地主
	const static char s_start[] = "btn_start.png";//开始游戏
	const static char s_visibleCard[] = "btn_visiblecard.png";//明牌
	const static char s_visibleStart[] = "btn_visiblestart.png";//明牌开始
	const static char s_settlementbg[] = "settlement_bg.png";//结算背景
	const static char s_changeTable[] = "btn_changetable.png";//换桌
	const static char s_again[] = "btn_again.png";//再来一局
	const static char s_hint[] = "btn_hint.png";//提示按钮
	const static char s_pass[] = "btn_pass.png";//不出
	const static char s_outCard[] = "btn_outcard.png";//出牌
	const static char s_font_bujiao[] = "font_bujiao.png";//不叫字
	const static char s_font_buqiang[] = "font_buqiang.png";//不抢字
	const static char s_font_jiaodizhu[] = "font_jiaodizhu.png";//叫地主字
	const static char s_font_pass[] = "font_pass.png";//不出字
	const static char s_font_qiangdizhu[] = "font_qiangdizhu.png";//抢地主字
	const static char s_font_visiblecard[] = "font_visiblecard.png";//明牌字
	const static char s_font_jiabei[] = "font_jiabei.png";//加倍字
	const static char s_font_hfd[] = "font_hfd.png";
	const static char s_x[] = "x.png";//X
	const static char s_menuBarBackground[] = "bg_menubar.png";//菜单栏背景
	const static char s_back[] = "btn_back.png";//返回按钮
	const static char s_options[] = "btn_options.png";//设置按钮
	const static char s_pull[] = "btn_pull.png";//菜单栏拉环
	const static char s_robot[] = "btn_robot.png";//托管按钮
	const static char s_talk[] = "btn_talk.png";//聊天按钮
	const static char s_task[] = "btn_task.png";//任务按钮
	const static char s_smallCard[] = "smallcard.png";//小扑克牌图片
	const static char s_hintCard[] = "hintcard.png";//盖着的扑克图片
	const static char s_settlementDetial[] = "settlementdetial.png";//查看明细btn
	const static char s_jiaBeiBar[] = "jbb_bj.png";//底牌加倍处的提示背景图片
	const static char s_twice[] = "twice.png";//二倍
	const static char s_thrice[] = "thrice.png";//三倍
	const static char s_fourfold[] = "fourfold.png";//四倍
	const static char s_fivefold[] = "fivefold.png";//五倍
	const static char s_nonuple[] = "nonuple.png";//九倍
	const static char s_sixfold[] = "sixfold.png";//六倍
	const static char s_diZhuTag[] = "dizhutag.png";//地主标签
	const static char s_showSelf[] = "showself.png";//结算，显示自己栏目时候的底图
	const static char s_ctDoubleLine[] = "ct_double_line.png";//连对
	const static char s_ctSingleLine[] = "ct_single_line.png";//顺子
	const static char s_ctThreeLine[] = "ct_sthree_line.png";//三顺
	const static char s_jiaBeiTag[] = "jiabeitag.png";//结算时的加倍标志
	const static char s_music[] = "music.png";//背景音乐图片
	const static char s_soundEffect[] = "soundeffect.png";//音效图片
	const static char s_off[] = "off.png";//关背景图片
	const static char s_on[] = "on.png";//开背景图片
	const static char s_on_off[] = "on_off.png";//开关图片
	const static char s_progress_bj[] = "progressbar0.png";//进度条背景
	const static char s_progress[] = "progressbar1.png";//进度条
	const static char s_setup_bg[] = "task_k.png";//设置底框
	const static char s_expression[] = "expression.png";//表情文字
	const static char s_voice[] = "voice.png";//语音文字
	//表情
	const static char s_faceCool[] = "face_0.png";//酷
	const static char s_faceHan[] = "face_1.png";//汗
	const static char s_faceHanlen[] = "face_2.png";//寒冷
	const static char s_faceKu[] = "face_3.png";//哭
	const static char s_faceNu[] = "face_4.png";//怒
	const static char s_faceNue[] = "face_5.png";//虐
	const static char s_faceQiu[] = "face_6.png";//糗
	const static char s_faceTu[] = "face_7.png";//吐
	const static char s_faceXiao[] = "face_8.png";//笑
	const static char s_faceYun[] = "face_9.png";//晕

	const static char s_confirm[] = "btn_confirm.png";//确定按钮
	const static char s_faceBg[] = "face_bg.png";//表情框背景
	//const static char s_xlt[] = "xlt.png";//下拉条
	const static char s_yyk[] = "yyk.png";//语音框
	const static char s_banshou[] = "banshou.png";//机器人扳手
	const static char s_cancleRobot[] = "btn_cancelrobot.png";//取消托管
	const static char s_eye[]= "eye.png";//机器人眼睛
	const static char s_robot_pic[] = "robot.png";//机器人图片
	const static char s_paiBei0[] = "paibei0.png";//牌背0
	const static char s_paiBei1[] = "paibei1.png";//牌背1
	const static char s_plane[] = "plane.png";//飞机
	const static char s_lxj0[] = "lxj0.png";//螺旋桨0
	const static char s_lxj1[] = "lxj1.png";//螺旋桨1
	const static char s_planeyy[] = "planeyy.png";//飞机下面的阴影
	const static char s_bomb[] = "bomb.png";//炸弹坑
	const static char s_bomb0[] = "bomb0.png";//炸弹火焰0
	const static char s_bomb1[] = "bomb1.png";//炸弹火焰1
	const static char s_bomb2[] = "bomb2.png";//炸弹火焰2
	const static char s_bomb3[] = "bomb3.png";//炸弹火焰3
	const static char s_bomb4[] = "bomb4.png";//炸弹火焰4
	const static char s_bomb5[] = "bomb5.png";//炸弹火焰5
	const static char s_bomb6[] = "bomb6.png";//炸弹火焰6
	const static char s_bomb7[] = "bomb7.png";//炸弹火焰7
	const static char s_yanwu0[] = "yanwu0.png";//人物形象变换烟雾
	const static char s_yanwu1[] = "yanwu1.png";
	const static char s_yanwu2[] = "yanwu2.png";
	const static char s_yanwu3[] = "yanwu3.png";
	const static char s_yanwu4[] = "yanwu4.png";
	const static char s_dizhu_man[] = "dizhu_man.png";//男地主
	const static char s_farmer_man[] = "farmer_man.png";//男农民
	const static char s_dizhu_woman[] = "dizhu_woman.png";//女地主
	const static char s_farmer_woman[] = "farmer_woman.png";//女农民
	const static char s_btn_cancle[] = "btn_cancle.png";//取消按钮
	const static char s_huojian[] = "huojian.png";//火箭
	const static char s_huoyan[] = "huoyan.png";//火焰
	const static char s_yun0[] = "yun0.png";//火箭云
	const static char s_yun1[] = "yun1.png";
	const static char s_yun2[] = "yun2.png";
	const static char s_yun3[] = "yun3.png";
	const static char s_paizi[] = "paizi.png";//搜人动画底图
	const static char s_font_deng[] = "font_deng.png";//等
	const static char s_font_dai[] = "font_dai.png";//待
	const static char s_font_qi[] = "font_qi.png";//其
	const static char s_font_ta[] = "font_ta.png";//他
	const static char s_font_wan[] = "font_wan.png";//玩
	const static char s_font_jia[] = "font_jia.png";//家
	const static char s_font_zhong[] = "font_zhong.png";//中
	const static char s_zawu[] = "zawu.png";//杂物
	const static char s_jingbao0[] = "jingbao0.png";//警报动画
	const static char s_jingbao1[] = "jingbao1.png";
	const static char s_jingbao2[] = "jingbao2.png";
	const static char s_jingbao3[] = "jingbao3.png";
	const static char s_jingbao4[] = "jingbao4.png";
	const static char s_jingbao5[] = "jingbao5.png";
	const static char s_loser[] = "loser.png";//失败动画
	const static char s_winner[] = "winner.png";//胜利动画
	const static char s_notify[] = "notify.png";//游戏最上面提示信息背景
	const static char s_task_d[] = "task_d.png";//任务文字低
	const static char s_task_k[] = "task_k.png";//任务框

	//玩家小头像
	const static char s_man_head_icon[] = "man_head_icon.png";
	const static char s_woman_head_icon[] = "woman_head_icon.png";
	const static char s_userMessage[] = "usermessage.png";//用户信息框
	const static char s_dizhuCardTag[] = "dizhucardtag.png";//地主最后一张卡片右上角图标

	const static char s_xyx_headIcon[] = "xyx_headicon.png";//小游戏自己名字前面的图标
	const static char s_showCardTag[] = "showcardtag.png";//明牌标志
	const static char s_difenTimesNum[] = "difentimesnum.png";//底分倍率数字
	//眨眼图片
	const static char s_dz_m_eye0[] = "dz_m_eye0.png";//男地主眨眼
	const static char s_dz_m_eye1[] = "dz_m_eye1.png";
	const static char s_dz_m_eye2[] = "dz_m_eye2.png";
	const static char s_dz_wm_eye0[] = "dz_wm_eye0.png";//女地主眨眼
	const static char s_dz_wm_eye1[] = "dz_wm_eye1.png";
	const static char s_dz_wm_eye2[] = "dz_wm_eye2.png";
	const static char s_fm_m_eye0[] = "fm_m_eye0.png";//男农民眨眼
	const static char s_fm_m_eye1[] = "fm_m_eye1.png";
	const static char s_fm_m_eye2[] = "fm_m_eye2.png";
	const static char s_fm_wm_eye0[] = "fm_wm_eye0.png";//女农民眨眼
	const static char s_fm_wm_eye1[] = "fm_wm_eye1.png";
	const static char s_fm_wm_eye2[] = "fm_wm_eye2.png";
	const static char s_m_eye0[] = "m_eye0.png";//男孩眨眼
	const static char s_m_eye1[] = "m_eye1.png";
	const static char s_m_eye2[] = "m_eye2.png";
	const static char s_wm_eye0[] = "wm_eye0.png";//女孩子眨眼
	const static char s_wm_eye1[] = "wm_eye1.png";
	const static char s_wm_eye2[] = "wm_eye2.png";

	const static char s_font_difen[] = "font_difen.png";//底分图片

	const static char s_back_fen0[] = "back_fen0.png";//风筝
	const static char s_back_fen1[] = "back_fen1.png";
	const static char s_back_fen2[] = "back_fen2.png";

	const static char s_card_big_baiban[] = "card_big_baiban.png";//扑克牌（大）白板
	const static char s_card_small_baiban[] = "card_small_baiban.png";//白板（小）
	const static char s_card_color[] = "card_color.png";//扑克牌花色（黑红方梅）
	const static char s_card_num_black[] = "card_num_black.png";//扑克牌字黑
	const static char s_card_num_red[] = "card_num_red.png";//扑克牌红
	const static char s_joker[] = "joker.png";	//图片大小为 pic
	const static char s_card[] ="card.png";//扑克牌
	//气泡资源
	const static char s_font_back[] = "font_back.png";//返回
	const static char s_font_chat[] = "font_chat.png";//聊天
	const static char s_font_robot[] = "font_robot.png";//托管
	const static char s_font_setup[] = "font_setup.png";//设置
	const static char s_font_task[] = "font_task.png";//任务
	const static char s_bubble[] = "bubble.png";//气泡
}
#endif