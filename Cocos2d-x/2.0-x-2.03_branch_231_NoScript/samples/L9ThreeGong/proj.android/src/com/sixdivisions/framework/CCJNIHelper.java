/****************************************************************************
Name��CCJNIHelper.java
Desc��C++<=>JNI�����ӿ���չ��cc2dxԭ����չ��Ҫ���Ķ����Ժ���������������ˣ�
Auth��Cool.Cat@2013-09-25
 ****************************************************************************/
package com.sixdivisions.framework;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.Iterator;
import java.util.Locale;
import java.util.Map.Entry;
import java.util.Properties;

import android.content.Context;
import android.content.pm.ApplicationInfo;
import android.net.wifi.WifiInfo;
import android.net.wifi.WifiManager;
import android.os.Build;
import android.telephony.TelephonyManager;
import android.util.DisplayMetrics;
import android.util.Log;

public class CCJNIHelper {
	// ===========================================================
	// Constants
	// ===========================================================

	// ===========================================================
	// Fields
	// ===========================================================
	private static Context sContext;
	private static String sPackageName;
	private static CCJNIFuncListener sCCJNIHelperListener;

	// ===========================================================
	// Constructors
	// ===========================================================

	public static void init(final Context pContext, final CCJNIFuncListener pCCJNIHelperListener) {
		final ApplicationInfo applicationInfo = pContext.getApplicationInfo();
		CCJNIHelper.sContext = pContext;
		CCJNIHelper.sCCJNIHelperListener = pCCJNIHelperListener;
		CCJNIHelper.sPackageName = applicationInfo.packageName;
		CCJNIHelper.setAPKPath(applicationInfo.sourceDir);
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
	public static native void ExitApplication();

	private static native void setAPKPath(final String pApkPath);
	private static native void setCPUFrequency(float []frequency);

	//private static native void nativeSetEditTextDialogResult(final byte[] pBytes);

	// ����
	public static String getPackageName() {
		return CCJNIHelper.sPackageName;
	}

	// ����
	public static String getCurrentLanguage() {
		return Locale.getDefault().getLanguage();
	}
	
	// SDK�汾
	public static String getVersionSDK(){
		return Build.VERSION.SDK;
	}
	
	// ϵͳ�汾
	public static String getVersionRelease(){
		return Build.VERSION.RELEASE;
	}
	
	// �ں˰汾
	public static String getVersionKernel(){
		try {		
			FileReader fr = new FileReader("proc/version"); 
			@SuppressWarnings("resource")
			BufferedReader br = new BufferedReader(fr); 
			return br.readLine();
		} catch (FileNotFoundException e) { 
			e.printStackTrace();
		} catch (IOException e) { 
			e.printStackTrace(); 
		}  
		return null; 		
	}

	// �豸�ͺ�
	public static String getDeviceModel(){
		return Build.MODEL;
	}

	// �豸���к�
	public static String getSerial(){
		return Build.SERIAL;
	}

	// CPU ABI
	public static String getCPUABI(){
		return Build.CPU_ABI;
	}

	// CPU ABI2
	public static String getCPUABI2(){
		return Build.CPU_ABI2;
	}

	// �ɵ�
	public static void killProcess() {
		android.os.Process.killProcess(android.os.Process.myPid());
	}

	// �ߴ�
	public static String getDisplayMetrics() {
		DisplayMetrics dm = new DisplayMetrics();
		dm = CCJNIHelper.sContext.getApplicationContext().getResources().getDisplayMetrics();
		return String.valueOf(dm.widthPixels) + "x" + String.valueOf(dm.heightPixels);
	}

	// CPU��Ϣ
	public static String getCPUInfo() {
		try { 
			FileReader fr = new FileReader("proc/cpuinfo"); 
			@SuppressWarnings("resource")
			BufferedReader br = new BufferedReader(fr); 
			String text = br.readLine();
			String[] cpuName = text.split(":\\s+", 2); 

//			for (int i = 0; i < cpuName.length; i++) {
//				Log.w("debug", " .....  " + cpuName[i]);
//			}
//			Log.w("debug", text);
			
			return cpuName[1]; 
		} catch (FileNotFoundException e) { 
			e.printStackTrace();
		} catch (IOException e) { 
			e.printStackTrace(); 
		}  
		return null; 
	}
	
	// ��ȡmac
	public static String getMacAddress() {
		WifiManager wifi = (WifiManager)CCJNIHelper.sContext.getSystemService(Context.WIFI_SERVICE);
		if (wifi==null)
			return null;
		WifiInfo info = wifi.getConnectionInfo();
		if (info==null)
			return null;
		return info.getMacAddress();
	}
	
	// ��ȡIMSI
	public static String getIMSI(){
		TelephonyManager tm = (TelephonyManager)CCJNIHelper.sContext.getSystemService(Context.TELEPHONY_SERVICE);
		if (tm==null)
			return null;
		String IMSI = tm.getSubscriberId();
		if (IMSI==null)
			return null;
		if (IMSI.startsWith("46000") || IMSI.startsWith("46002"))
		{
			Log.v("debug","�й��ƶ�");
		}
		else if (IMSI.startsWith("46001"))
		{
			Log.v("debug","�й���ͨ");
		}
		else if (IMSI.startsWith("46003"))
		{
			Log.v("debug","�й�����");
		}
		return IMSI;
	}	
	
	// ��ȡIMEI
	public static String getIMEI(){
		TelephonyManager tm = (TelephonyManager)CCJNIHelper.sContext.getSystemService(Context.TELEPHONY_SERVICE);
		if (tm==null)
			return null;
		return tm.getDeviceId();
	}
	
	// ��ȡIMEI SV
	public static String getIMEISV(){
		TelephonyManager tm = (TelephonyManager)CCJNIHelper.sContext.getSystemService(Context.TELEPHONY_SERVICE);
		if (tm==null)
			return null;
		return tm.getDeviceSoftwareVersion();
	}
	
	// ��ȡ�绰����
	public static String getPhoneNumber(){
		TelephonyManager tm = (TelephonyManager)CCJNIHelper.sContext.getSystemService(Context.TELEPHONY_SERVICE);
		if (tm==null)
			return null;
		return tm.getLine1Number();
	}
	
	// ��ȡ���Լ�ֵ��
	public static String getPropertiesKV(){
		String result = null;
		//int i=0;
		Properties props=System.getProperties();
		if (props==null)
			return null;
		Iterator<Entry<Object, Object>> it = props.entrySet().iterator();
		while (it.hasNext()) {
			//i++;
			Entry<Object, Object> entry = it.next();  
			Object key = entry.getKey();  
			Object value = entry.getValue();
			//Log.v("debug","props["+i+"].key["+key+"].value["+value+"]");
			result += key+"\\"+value+"\\";
		}
		return result;
	}	
	
	// �Ƿ��
	private static void showMsgBoxYesOrNo(final String[] array) {
		CCJNIHelper.sCCJNIHelperListener.showMsgBoxYesOrNo(array);
	}	

	private static void showMsgBoxYesOrNo(final String pTitle, final String pMessage) {
		CCJNIHelper.sCCJNIHelperListener.showMsgBoxYesOrNo(pTitle, pMessage);
	}

	/*	public static void setEditTextDialogResult(final String pResult) {
		try {
			final byte[] bytesUTF8 = pResult.getBytes("UTF8");

			Cocos2dxHelper.sCocos2dxHelperListener.runOnGLThread(new Runnable() {
				@Override
				public void run() {
					Cocos2dxHelper.nativeSetEditTextDialogResult(bytesUTF8);
				}
			});
		} catch (UnsupportedEncodingException pUnsupportedEncodingException) {
			 Nothing. 
		}
	}*/

	// ===========================================================
	// Inner and Anonymous Classes
	// ===========================================================
	public static interface CCJNIFuncListener {
		public void showMsgBoxYesOrNo(final String[] pArray);
		public void showMsgBoxYesOrNo(final String pTitle,final String pMessage);
	}
}