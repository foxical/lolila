package com.foxical.lolila.demo;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;


import com.foxical.lolila.sdk.RenderApi;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class OpenGLESActivity extends Activity {

    public static void start(Context ctx){
        ctx.startActivity(new Intent(ctx,OpenGLESActivity.class));
    }


    private GLSurfaceView mGLView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        // 创建一个GLSurfaceView对象，并将其设置为当前Activity的ContentView
        mGLView = new MyGLSurfaceView(this);
        setContentView(mGLView);
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

    ////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////

    class MyGLSurfaceView extends GLSurfaceView {

        public MyGLSurfaceView(Context context){
            super(context);

            // 创建一个OpenGL ES 3.0 context
            setEGLContextClientVersion(3);
            // 只有在绘制数据改变时才绘制view
            //setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
            // 设置渲染对象，用于控制在GLSurfaceView中的绘制工作
            setRenderer(new JNIRenderer());
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
    }


}
