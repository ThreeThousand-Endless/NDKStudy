package com.jcy.ndk.liveTv.listener;

public interface LiveStateChangeListener {

	/**
	 * 发送错误
	 * @param code
	 */
	void onError(int code);
	
}
