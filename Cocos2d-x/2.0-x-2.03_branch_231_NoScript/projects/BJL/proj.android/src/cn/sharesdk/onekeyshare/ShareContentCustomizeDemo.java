package cn.sharesdk.onekeyshare;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.Platform.ShareParams;
import cn.sharesdk.onekeyshare.ShareContentCustomizeCallback;

/**
 * ��ݷ�����Ŀ�������Ϊ��ͬ��ƽ̨��Ӳ�ͬ�������ݵķ�����
 *����������ʾ�����������΢���ķ������ݺ�����ƽ̨�������ݡ�
 *�������{@link DemoPage#showShare(boolean, String)}����
 *�б����á�
 */
public class ShareContentCustomizeDemo implements ShareContentCustomizeCallback {

	public void onShare(Platform platform, ShareParams paramsToShare) {
		
		//PDF.SendMainMessage(ClientActivity.MM_CHANGE_VIEW, ClientActivity.MS_SERVER, null);
	}

}
