package cn.sharesdk.onekeyshare;

import java.util.HashMap;
import cn.sharesdk.framework.Platform;
import cn.sharesdk.framework.PlatformActionListener;
import cn.sharesdk.onekeyshare.OnekeyShare;

/**
 * OneKeyShareCallback是快捷分享功能的一个“外部回调”示例。通过
 *{@link OnekeyShare#setCallback(PlatformActionListener)}将
 *本类的示例传递进快捷分享，分享操作结束后，快捷分享会将分享结果
 *回调到本类中来做自定义处理。
 */
public class OneKeyShareCallback implements PlatformActionListener {

	public void onComplete(Platform plat, int action, HashMap<String, Object> res) {
		System.out.println(res.toString());
		// 在这里添加分享成功的处理代码
	}

	public void onError(Platform plat, int action, Throwable t) {
		t.printStackTrace();
		// 在这里添加分享失败的处理代码
	}

	public void onCancel(Platform plat, int action) {
		// 在这里添加取消分享的处理代码
	}

}
