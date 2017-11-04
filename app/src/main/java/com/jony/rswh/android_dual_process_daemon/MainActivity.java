package com.jony.rswh.android_dual_process_daemon;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        //启动Service服务
        Intent intent = new Intent(this,ProcessService.class);
        startService(intent);
    }

}
