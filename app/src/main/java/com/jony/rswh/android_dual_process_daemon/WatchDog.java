package com.jony.rswh.android_dual_process_daemon;

/**
 * Created by Administrator on 2017/10/29 0029.
 * 监听service状态
 */

public class WatchDog {
    static {
        System.loadLibrary("native-lib");
    }

    public native void createWatchDog(String userId);
    public native void connectMonitor();
}
