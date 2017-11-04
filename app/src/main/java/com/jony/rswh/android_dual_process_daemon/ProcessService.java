package com.jony.rswh.android_dual_process_daemon;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.os.Process;
import android.support.annotation.Nullable;
import android.util.Log;

import java.util.Timer;
import java.util.TimerTask;

/**
 * Created by Administrator on 2017/10/29 0029.
 */

public class ProcessService extends Service{
    private static final String TAG = "ProcessService";
    private int i = 0;
    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onCreate() {
        super.onCreate();
        final WatchDog watchDog = new WatchDog();
        watchDog.createWatchDog(String.valueOf(Process.myUid()));
        watchDog.connectMonitor();

        //设置定时器打印Log，判断service是否存活
        Timer timer = new Timer();
        timer.scheduleAtFixedRate(new TimerTask() {
            @Override
            public void run() {
                Log.i(TAG,"服务开启中" + i);
                i++;
            }
        },0,1000*3);
    }
}
