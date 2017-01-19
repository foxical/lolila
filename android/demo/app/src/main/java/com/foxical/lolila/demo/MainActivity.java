package com.foxical.lolila.demo;

import android.app.Activity;
import android.os.Bundle;
import android.widget.TextView;

import com.foxical.lolila.sdk.IndexApi;

public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tvTitle = (TextView) findViewById(R.id.tv_title);
        tvTitle.setText(IndexApi.getStr());
    }
}
