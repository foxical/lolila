package com.foxical.lolila.demo;

import android.app.Activity;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

import com.foxical.lolila.sdk.IndexApi;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvTitle = (TextView) findViewById(R.id.tv_title);
        tvTitle.setText(IndexApi.getStr());

        findViewById(R.id.btn_enter_test).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                OpenGLES2Activity.start(MainActivity.this);
            }
        });
    }
}
