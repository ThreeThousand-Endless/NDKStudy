package com.jcy.ndk.liveTv.pusher;

public abstract class Pusher {

	public abstract void startPush();
	
	public abstract void stopPush();
	
	public abstract void release();
	
}
