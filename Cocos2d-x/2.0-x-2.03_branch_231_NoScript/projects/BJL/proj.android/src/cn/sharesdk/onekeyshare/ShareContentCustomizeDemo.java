package cn.sharesdk.onekeyshare;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.Platform.ShareParams;
import cn.sharesdk.onekeyshare.ShareContentCustomizeCallback;

/**
 * 快捷分享项目现在添加为不同的平台添加不同分享内容的方法。
 *本类用于演示如何区别新浪微博的分享内容和其他平台分享内容。
 *本类会在{@link DemoPage#showShare(boolean, String)}方法
 *中被调用。
 */
public class ShareContentCustomizeDemo implements ShareContentCustomizeCallback {

	public void onShare(Platform platform, ShareParams paramsToShare) {
		
		//PDF.SendMainMessage(ClientActivity.MM_CHANGE_VIEW, ClientActivity.MS_SERVER, null);
	}

}
