package com.foxical.lolila.demo;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.LinearLayout;


import com.foxical.lolila.sdk.RenderApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;

public class OpenGLESActivity extends Activity implements View.OnClickListener{

    public static void start(Context ctx){
        ctx.startActivity(new Intent(ctx,OpenGLESActivity.class));
    }


    private MyGLSurfaceView mGLView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);


        setContentView(R.layout.activity_opengles);
        findViewById(R.id.btn_move_back).setOnClickListener(this);
        findViewById(R.id.btn_move_forward).setOnClickListener(this);
        findViewById(R.id.btn_move_left).setOnClickListener(this);
        findViewById(R.id.btn_move_right).setOnClickListener(this);
        findViewById(R.id.btn_move_up).setOnClickListener(this);
        findViewById(R.id.btn_move_down).setOnClickListener(this);
        findViewById(R.id.btn_pitch_up).setOnClickListener(this);
        findViewById(R.id.btn_pitch_down).setOnClickListener(this);
        findViewById(R.id.btn_yaw_left).setOnClickListener(this);
        findViewById(R.id.btn_yaw_right).setOnClickListener(this);


        // 创建一个GLSurfaceView对象，并将其设置为当前Activity的ContentView
        mGLView = new MyGLSurfaceView(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(MATCH_PARENT,MATCH_PARENT);
        LinearLayout glViewContainer = (LinearLayout) findViewById(R.id.gl_view_container);
        glViewContainer.addView(mGLView,layoutParams);
    }

    @Override
    protected void onResume() {
        // TODO Auto-generated method stub
        super.onResume();
        mGLView.onResume();
    }

    @Override
    protected void onPause() {
        // TODO Auto-generated method stub
        super.onPause();
        mGLView.onPause();
    }

    @Override
    public void onClick(View v) {
        final JNIRenderer renderer = mGLView.renderer;
        Runnable runnable=null;
        switch (v.getId()){
            case R.id.btn_move_forward:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraMoveForward();
                    }
                };
                break;
            case R.id.btn_move_back:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraMoveBack();
                    }
                };
                break;
            case R.id.btn_move_left:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraMoveLeft();
                    }
                };
                break;
            case R.id.btn_move_right:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraMoveRight();
                    }
                };
                break;
            case R.id.btn_move_up:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraMoveUp();
                    }
                };
                break;
            case R.id.btn_move_down:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraMoveDown();
                    }
                };
                break;
            case R.id.btn_pitch_up:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraPitchUp();
                    }
                };
                break;
            case R.id.btn_pitch_down:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraPitchDown();
                    }
                };
                break;
            case R.id.btn_yaw_left:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraYawLeft();
                    }
                };
                break;
            case R.id.btn_yaw_right:
                runnable = new Runnable() {
                    @Override
                    public void run() {
                        renderer.cameraYawRight();
                    }
                };
                break;
        }
        if( runnable!=null){
            mGLView.queueEvent(runnable);
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////

    class MyGLSurfaceView extends GLSurfaceView {

        JNIRenderer renderer;


        public MyGLSurfaceView(Context context){
            super(context);

            // 创建一个OpenGL ES 3.0 context
            setEGLContextClientVersion(3);
            // 只有在绘制数据改变时才绘制view
            //setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
            // 设置渲染对象，用于控制在GLSurfaceView中的绘制工作
            renderer = new JNIRenderer();
            setRenderer(renderer);
        }

    }

    private class JNIRenderer implements GLSurfaceView.Renderer {

        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
            // 设置背景色
            //GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            RenderApi.init();
        }

        public void onSurfaceChanged(GL10 unused, int width, int height) {
            //GLES20.glViewport(0, 0, width, height);
            RenderApi.resize(width,height);
        }

        public void onDrawFrame(GL10 unused) {
            // 重绘背景色
            //GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);
            RenderApi.draw();
        }

        void cameraMoveForward(){
            RenderApi.cameraMoveForward();
        }
        void cameraMoveBack(){
            RenderApi.cameraMoveBack();
        }
        void cameraMoveLeft(){
            RenderApi.cameraMoveLeft();
        }
        void cameraMoveRight(){
            RenderApi.cameraMoveRight();
        }
        void cameraMoveUp(){
            RenderApi.cameraMoveUp();
        }
        void cameraMoveDown(){
            RenderApi.cameraMoveDown();
        }
        void cameraPitchUp(){
            RenderApi.cameraPitchUp();
        }
        void cameraPitchDown(){
            RenderApi.cameraPitchDown();
        }
        void cameraYawLeft(){
            RenderApi.cameraYawLeft();
        }
        void cameraYawRight(){
            RenderApi.cameraYawRight();
        }
    }


}
