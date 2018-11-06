/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package com.hapi.DDZClient;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;
import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.plugin.PluginWrapper;

import cn.sharesdk.ShareSDKUtils;

import cn.sharesdk.onekeyshare.OnekeyShare;
//import cn.sharesdk.onekeyshare.ShareContentCustomizeDemo;

import android.app.Activity;
import android.content.ContentResolver;
import android.content.res.Resources;
import android.os.Bundle;
import android.view.KeyEvent;

public class DDZClient extends Cocos2dxActivity{

	private static Activity me = null;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		me = this;
	}
    
protected void onStart()
{
	super.onStart();
	
}
@Override  
public boolean onKeyDown(int keyCode, KeyEvent event) {  
    // TODO Auto-generated method stub  
    if(keyCode == KeyEvent.KEYCODE_MENU)  
       {    
    	//showShare(false, null);
       }  
    return false;  
}  
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// HelloCpp should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
		//PluginWrapper.init(this);
		//PluginWrapper.setGLSurfaceView(glSurfaceView);
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     

  //实现浏览器模块的调用
   public static void openURL(String url) 
     { 
           //Intent i = new Intent(Intent.ACTION_VIEW);  
           //i.setData(Uri.parse(url));
           //me.startActivity(i);
     }

  	// ===========================================================
  	// Inner and Anonymous Classes
  	// ===========================================================
   
	//public static void showShare(boolean silent, String platform) {
  /* public void showShare(boolean silent, String platform) {
		final OnekeyShare oks = new OnekeyShare();
		String app_name = "伸手要钱";
		String evenote_title = "伸手要钱";
		String share = "伸出你的手要钱去";
		oks.setNotification(R.drawable.icon, app_name);
		oks.setTitle(evenote_title);
		oks.setTitleUrl("http://www.fl567.com");
		oks.setText("飞龙官方网址：http://fl567.com \n随时随地，让游戏更加有味");
		 final Resources r = getResources();
		//oks.setImagePath("file:\\\\android_assets\\sprite2.png");
		oks.setUrl("http://www.fl567.com");
		oks.setComment(share);
		oks.setSite(app_name);
		oks.setSiteUrl("http://www.fl567.com");
		oks.setSilent(silent);
		if (platform != null) {
			oks.setPlatform(platform);
		}
		oks.setShareContentCustomizeCallback(new ShareContentCustomizeDemo());
		oks.show(this.getApplicationContext());
	}
*/
	/*public  void pay(String payCode) {
		if (bxPay == null)
			bxPay = new BXPay(this);
		Map<String, String> devPrivate = new HashMap<String, String>();
		devPrivate.put("acc", ClientActivity.GetLogonAccounts());
		devPrivate.put("uid",	String.valueOf(m_ClientKernel.GetMeUserItem().GetUserID()));
		bxPay.setDevPrivate(devPrivate);
		bxPay.pay(payCode, new PayCallback() {
			@Override
			public void pay(Map resultInfo) {	
				String result= (String) resultInfo.get("result");
				String payType=(String)resultInfo.get("payType");
				String price= (String)resultInfo.get("price");
				String logCode=(String)resultInfo.get("logCode");
				String showMsg=(String)resultInfo.get("showMsg");

				if ("success".equals(result) && price != null) {
					AlertDialog.Builder result_dialog = new AlertDialog.Builder(ClientActivity.GetPlazzInstance());
					result_dialog.setTitle("充值提示");
					result_dialog.setMessage("您花费￥ " + price + " 元购买会员服务，赠送" + ClientActivity.GetCZScore(price) + "金豆！"+"<br>"+
					"<br>"+"支付类型："+payType+"<br>"+"订单编号："+logCode+"<br>"+"支付结果描述："+showMsg);
					result_dialog.setInverseBackgroundForced(true);
					result_dialog.setNegativeButton("关  闭",
							new DialogInterface.OnClickListener() {
								@Override
								public void onClick(DialogInterface dialog,int which) {
									dialog.dismiss();
								}
							});
					result_dialog.create().show();
			}
		}
		});
	}*/
  }
