package com.jony.rswh.android_dual_process_daemon;

/**
 * Created by Administrator on 2017/10/29 0029.
 * 监听service状态
 */

public class WatchDog {
    static {
        System.loadLibrary("native-lib");
    }

    /**
     * 创建Linux守护进程服务端
     */
    public native void createWatchDog(String userId);
    /**
     * APP端(客户端)进程状态监测
     */
    public native void connectMonitor();
}
