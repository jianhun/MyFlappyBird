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
package com.Shao.Test;

import java.util.Calendar;

import net.youmi.android.AdManager;
import net.youmi.android.dev.OnlineConfigCallBack;
import net.youmi.android.spot.SpotManager;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxGLSurfaceView;

import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.RelativeLayout;
import android.app.Activity;
import android.content.Context;
import android.content.SharedPreferences;

//飞沃
//import com.feiwoone.banner.AdBanner;
//import com.feiwoone.banner.RecevieAdListener;
//import com.feiwothree.coverscreen.CoverAdComponent;

//微信
//import com.tencent.mm.sdk.openapi.IWXAPI;
//import com.tencent.mm.sdk.openapi.WXAPIFactory;
//import com.tencent.mm.sdk.openapi.WXTextObject;
public class testShao3 extends Cocos2dxActivity{
	
	public static Context ownerContext;
	public static SharedPreferences sharedPrefs;
	public static SharedPreferences.Editor prefsEditor;
	//微信
//	public static final String APP_ID = "wxed6feb2e2a0410f6";
	//飞沃
//	private RelativeLayout myAdonContainerView;
//	private String feiwo_appKey = "UiWpbaNQJdJ5yUAw15OqS16m";
//	private AdBanner myAdView;
	//有米
	private static final String youmi_appid = "cc8275d283012071";
	private static final String youmi_appkey = "21cc9be3fc7a8b39";
	private static String youmi_open = "2";	//1.open 2.close
	private static int youmi_checkHour = -1;
	
    protected void onCreate(Bundle savedInstanceState){
		super.onCreate(savedInstanceState);	
		
		ownerContext = getApplicationContext();
		sharedPrefs = getApplicationContext().getSharedPreferences("testShao3.preferences", Activity.MODE_PRIVATE);
		prefsEditor = sharedPrefs.edit();  
		
		//微信
		//final IWXAPI api = WXAPIFactory.createWXAPI(this, APP_ID);
		//api.registerApp(APP_ID);
		//飞沃banner
//		myAdonContainerView = new RelativeLayout(this);
//        RelativeLayout.LayoutParams parentLayputParams = new RelativeLayout.LayoutParams(
//                RelativeLayout.LayoutParams.FILL_PARENT,
//                RelativeLayout.LayoutParams.FILL_PARENT);
//		this.addContentView(myAdonContainerView, parentLayputParams);
//        myAdView = new AdBanner(this);
//        myAdonContainerView.addView(myAdView);
//		myAdView.setAppKey(feiwo_appKey);
//		RecevieAdListener adListener = new RecevieAdListener() {
//			@Override
//			public void onSucessedRecevieAd(AdBanner adView) {
//				myAdonContainerView.setVisibility(View.VISIBLE);
//			}
//			@Override
//			public void onFailedToRecevieAd(AdBanner adView) {
//				myAdonContainerView.setVisibility(View.GONE);
//			}
//		};
//		myAdView.setRecevieAdListener(adListener);
		//飞沃插屏
//		CoverAdComponent.init(this, feiwo_appKey);
		
		//有米插屏
		AdManager.getInstance(this).init(youmi_appid,youmi_appkey, false);
		SpotManager.getInstance(this).loadSpotAds();
		SpotManager.getInstance(this).setSpotTimeout(3000);//3秒
		getYoumi();
	}
    
    public Cocos2dxGLSurfaceView onCreateView() {
    	Cocos2dxGLSurfaceView glSurfaceView = new Cocos2dxGLSurfaceView(this);
    	// testShao3 should create stencil buffer
    	glSurfaceView.setEGLConfigChooser(5, 6, 5, 0, 16, 8);
    	
    	return glSurfaceView;
    }

    static {
        System.loadLibrary("cocos2dcpp");
    }     
    
    //有米获取在线参数
    public static void getYoumi() {
    	int hour = Calendar.getInstance().get(Calendar.HOUR);
    	Log.v("aaaaaaaahour", hour + "");
    	Log.v("aaaaaaaahour", youmi_checkHour + "");
    	if (hour != youmi_checkHour) {
    		AdManager.getInstance(ownerContext).asyncGetOnlineConfig("adsOpen", new OnlineConfigCallBack() {
    	        @Override
    	        public void onGetOnlineConfigSuccessful(String key, String value) {
    	        // TODO Auto-generated method stub
    	            //获取在线参数成功
    	        	Log.v("aaaaaaaakey",key);
    	        	Log.v("aaaaaaaavalue", value);
    	        	youmi_open = value;
    	        }       
    	        @Override
    	        public void onGetOnlineConfigFailed(String key) {
    	            // TODO Auto-generated method stub
    	            //获取在线参数失败，可能原因有：键值未设置或为空、网络异常、服务器异常
    	        	Log.v("aaaaaaaafail",key);
    	        }
    	    });
    	}
    	youmi_checkHour = hour;
    }
    
    public static void showAdsScreen() {
    	//飞沃插屏
//    	CoverAdComponent.showAd(ownerContext);
    	//有米插屏
    	getYoumi();
    	Log.v("aaaaaaaaastate", youmi_open);    	
    	if (youmi_open.equals("1")) {
    		SpotManager.getInstance(ownerContext).showSpotAds(ownerContext);
    	}
    	    	
    }
    
    public static void closeAdsScreen() {
    	//飞沃插屏
//    	CoverAdComponent.close(ownerContext);
    }
    
    
    @Override
    protected void onDestroy() {
    	super.onDestroy();
    	//飞沃释放占用资源
//    	CoverAdComponent.destory(this);
    }
    
    public static void setInt(String key, int value){
    	try
    	{
    		prefsEditor.putInt(key, value);
    		prefsEditor.commit();
    	}
    	catch(Exception e)
    	{
    		
    	}
    }
    
    public static int getInt(String key, int defValue){
    	try
    	{
    		int v = sharedPrefs.getInt(key, defValue);
    		return v;
    	}
    	catch(Exception e)
    	{
    		return 0;
    	}
    }
    
    public static void setBool(String key, boolean value){
    	try
    	{
    		prefsEditor.putBoolean(key, value);
    		prefsEditor.commit();
    	}
    	catch(Exception e)
    	{
    		
    	}
    }
    
    public static boolean getBool(String key, boolean defValue){
    	try
    	{	
    		boolean v = sharedPrefs.getBoolean(key, defValue);
    		return v;
    	}
    	catch(Exception e)
    	{
    		return false;
    	}
    }
}
