package com.foxical.lolila.demo;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
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


    private GLSurfaceView mGLView;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);


        setContentView(R.layout.activity_opengles);




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
    }


}
