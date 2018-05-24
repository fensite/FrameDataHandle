package com.zkn.framedatahandle;

import android.util.Log;

public class FrameDataHandle {
	private static FrameDataHandle mInstance;
	private boolean mIsLoadLib = false;
	private String LOG_TAG = "FrameDataHandle";
	private String JAR_VERSION = "V1.0.0";
	
	private FrameDataHandle() {
	}
	
	static {
		Log.d("FrameDataHandle", "下载本地库");
		System.loadLibrary("FrameDataHandle");
	}

	/**
	 * 静态构造方法
	 * 
	 * @return
	 */
	public synchronized static FrameDataHandle getInstance() {
		if (mInstance == null) {
			mInstance = new FrameDataHandle();
		}
		return mInstance;
	}

	private void loadLib(String libName) {
		if (!mIsLoadLib) {
			try {
				System.load(libName);
				mIsLoadLib = true;
				Log.d(LOG_TAG, "loadLib OK " + libName);
			} catch (Exception e) {
				Log.d(LOG_TAG, "loadLib: " + e.toString());
			}
		}
	}
	
	/**
	 * 调用底层接口
	 * 
	 * @return
	 */
	public native boolean getParserData(byte[] data, byte[] redata);
	public synchronized boolean getData(char[] data, byte[] redata) {
		Log.d(LOG_TAG, "FrameDataHandle JAR_VERSION: " + JAR_VERSION);
		mIsLoadLib = true;
		 byte[] bs2 = new byte[data.length];//定义一个长度与需要转换的char数组相同的byte数组
		  for(int i = 0; i < data.length; i++) {//循环将char数组的每一个元素转换为byte并存在上面定义的byte数组中
		   byte b = (byte) data[i];//将每一个char转换成byte
		   bs2[i] = b;//保存到数组中
		  }
		Log.d(LOG_TAG, "FrameDataHandle 调用native getParserData ");
		return getParserData(bs2, redata);
	}
}
