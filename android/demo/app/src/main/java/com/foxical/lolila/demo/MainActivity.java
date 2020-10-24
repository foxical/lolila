package com.foxical.lolila.demo;

import android.app.Activity;
import android.app.ActivityManager;
import android.content.Context;
import android.content.pm.ConfigurationInfo;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;
import android.widget.Toast;

import com.foxical.lolila.sdk.IndexApi;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvTitle = (TextView) findViewById(R.id.tv_title);
        tvTitle.setText(IndexApi.getStr());

        /*

        ActivityManager am =(ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        String s = info.reqGlEsVersion+"";
        String ver = Integer.toHexString(Integer.parseInt(s));
        Toast.makeText(this,"reqGlEsVersion = " + ver,Toast.LENGTH_LONG).show();
        */

        findViewById(R.id.btn_enter_course_1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startCourse(1);
            }
        });
        findViewById(R.id.btn_enter_course_2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startCourse(2);
            }
        });
        findViewById(R.id.btn_enter_course_3).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startCourse(3);
            }
        });
        findViewById(R.id.btn_enter_course_test).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                startCourse(-1);
            }
        });

        findViewById(R.id.btn_enter_test_2d).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                MatrixTestActivity.start(MainActivity.this);
            }
        });
    }


    private boolean detectOpenGLES30() {
        ActivityManager am = (ActivityManager)getSystemService(Context.ACTIVITY_SERVICE);
        ConfigurationInfo info = am.getDeviceConfigurationInfo();
        return (info.reqGlEsVersion >= 0x30000);
    }

    private void startCourse(int no){
        if( !detectOpenGLES30()){
            Toast.makeText(MainActivity.this,"OpenGL ES 3.0 not supported on device. Aborting...",Toast.LENGTH_SHORT).show();
            return;
        }
        OpenGLESActivity.start(MainActivity.this,no);
    }
}
