/****************************************************************************
Name：CCJNIHandler.java
Desc：C++<=>JNI消息处理
Auth：Cool.Cat@2013-09-25
****************************************************************************/
package com.sixdivisions.framework;

import java.lang.ref.WeakReference;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.R;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.os.Handler;
import android.os.Message;

public class CCJNIHandler extends Handler {
	// ===========================================================
	// Constants
	// ===========================================================	
	public final static int HANDLER_SHOW_MESSAGEBOXYESORNO = 1;
	
	// ===========================================================
	// Fields
	// ===========================================================
	private WeakReference<Cocos2dxActivity> mActivity;
	
	// ===========================================================
	// Constructors
	// ===========================================================
	public CCJNIHandler(Cocos2dxActivity activity) {
		this.mActivity = new WeakReference<Cocos2dxActivity>(activity);
	}
	
	// ===========================================================
	// Getter & Setter
	// ===========================================================

	// ===========================================================
	// Methods for/from SuperClass/Interfaces
	// ===========================================================
	
	// ===========================================================
	// Methods
	// ===========================================================
	public void handleMessage(Message msg) {
		switch (msg.what) {
		case CCJNIHandler.HANDLER_SHOW_MESSAGEBOXYESORNO:
			showDialog(msg);
			break;			
		}
	}
		
	private void showDialog(Message msg) {
		Cocos2dxActivity theActivity = this.mActivity.get();
		DialogMessage dialogMessage = (DialogMessage)msg.obj;
		new AlertDialog.Builder(theActivity)
		.setTitle(dialogMessage.titile)
		.setMessage(dialogMessage.message)
		.setPositiveButton(R.string.ok,
				new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
						CCJNIHelper.ExitApplication();
					}
				})
		.setNegativeButton(R.string.cancel,
				new DialogInterface.OnClickListener() {
					
					@Override
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				}).create().show();
	}
	
	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
	public static class DialogMessage {
		public String titile;
		public String message;
		
		public DialogMessage(String title, String message) {
			this.titile = title;
			this.message = message;
		}
	}
}
