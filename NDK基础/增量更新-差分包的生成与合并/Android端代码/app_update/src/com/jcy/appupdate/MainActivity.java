package com.jcy.appupdate;

import java.io.File;

import com.jcy.appupdate.utils.ApkUtils;
import com.jcy.appupdate.utils.BsPatch;
import com.jcy.appupdate.utils.Constants;
import com.jcy.appupdate.utils.DownloadUtils;

import android.app.Activity;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.Log;
import android.widget.Toast;

public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		new ApkUpdateTask().execute();
	}

	class ApkUpdateTask extends AsyncTask<Void, Void, Boolean>{

		@Override
		protected Boolean doInBackground(Void... params) {
			try {
				//1.下载差分包
				Log.d("jcy", "开始下载");
				File patchFile = DownloadUtils.download(Constants.URL_PATCH_DOWNLOAD);
				
				//获取当前应用的apk文件/data/app/app
				String oldfile = ApkUtils.getSourceApkPath(MainActivity.this, getPackageName());
				//2.合并得到最新版本的APK文件
				String newfile = Constants.NEW_APK_PATH;
				String patchfile = patchFile.getAbsolutePath();
				BsPatch.patch(oldfile, newfile, patchfile);
				
				Log.d("jcy", "oldfile:"+oldfile);
				Log.d("jcy", "newfile:"+newfile);
				Log.d("jcy", "patchfile:"+patchfile);
			} catch (Exception e) {
				e.printStackTrace();
				return false;
			}
			
			return true;
		}
		
		@Override
		protected void onPostExecute(Boolean result) {
			super.onPostExecute(result);
			//3.安装
			if(result){
				Toast.makeText(MainActivity.this, "您正在进行无流量更新", Toast.LENGTH_SHORT).show();
				ApkUtils.installApk(MainActivity.this, Constants.NEW_APK_PATH);
			}
		}
		
	}
}
