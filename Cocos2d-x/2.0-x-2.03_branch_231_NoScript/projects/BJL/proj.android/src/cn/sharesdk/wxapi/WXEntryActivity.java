package cn.sharesdk.wxapi;

import cn.sharesdk.wechat.utils.WXAppExtendObject;
import cn.sharesdk.wechat.utils.WXMediaMessage;
import cn.sharesdk.wechat.utils.WechatHandlerActivity;
import android.content.Intent;
import android.widget.Toast;

public class WXEntryActivity extends WechatHandlerActivity {

	/**
	 * ����΢�ŷ������������Ӧ������app message
	 * <p>
	 * ��΢�ſͻ����е�����ҳ���С���ӹ��ߡ������Խ���Ӧ�õ�ͼ����ӵ�����
	 * �˺���ͼ�꣬����Ĵ���ᱻִ�С�Demo����ֻ�Ǵ��Լ����ѣ������
	 * �������������飬�������������κ�ҳ��
	 */
	public void onGetMessageFromWXReq(WXMediaMessage msg) {
		Intent iLaunchMyself = getPackageManager().getLaunchIntentForPackage(getPackageName());
		startActivity(iLaunchMyself);
	}

	/**
	 * ����΢���������Ӧ�÷������Ϣ
	 * <p>
	 * �˴��������մ�΢�ŷ��͹�������Ϣ���ȷ�˵��demo��wechatpage�������
	 * Ӧ��ʱ���Բ�����Ӧ���ļ���������һ��Ӧ�õ��Զ�����Ϣ�����ܷ���΢��
	 * �ͻ��˻�ͨ������������������Ϣ���ͻؽ��շ��ֻ��ϵı�demo�У�����
	 * �ص���
	 * <p>
	 * ��Demoֻ�ǽ���Ϣչʾ������������������������飬��������ֻ��Toast
	 */
	public void onShowMessageFromWXReq(WXMediaMessage msg) {
		if (msg != null && msg.mediaObject != null
				&& (msg.mediaObject instanceof WXAppExtendObject)) {
			WXAppExtendObject obj = (WXAppExtendObject) msg.mediaObject;
			Toast.makeText(this, obj.extInfo, Toast.LENGTH_SHORT).show();
		}
	}

}
