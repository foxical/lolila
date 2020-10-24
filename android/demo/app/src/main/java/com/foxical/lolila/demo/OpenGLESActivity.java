package com.foxical.lolila.demo;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.content.res.ObbInfo;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.GestureDetector;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.FrameLayout;
import android.widget.LinearLayout;


import com.foxical.lolila.sdk.RenderApi;

import java.io.File;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import static android.view.ViewGroup.LayoutParams.MATCH_PARENT;

public class OpenGLESActivity extends Activity implements View.OnTouchListener{

    public static void start(Context ctx,int no){
        Intent intent = new Intent(ctx,OpenGLESActivity.class);
        intent.putExtra("courseNo",no);
        ctx.startActivity(intent);
    }


    private MyGLSurfaceView mGLView;
    private int mCourseNo;
    private Button btnNextStep;
    private Button btnReset;
    private int curStep=0;
    private GestureDetector gestureDetector;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        mCourseNo = getIntent().getIntExtra("courseNo",-1);

        requestWindowFeature(Window.FEATURE_NO_TITLE);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN);

        gestureDetector = new GestureDetector(this,new MyGestureListener());

        setContentView(R.layout.activity_opengles);
        findViewById(R.id.btn_move_back).setOnTouchListener(this);
        findViewById(R.id.btn_move_forward).setOnTouchListener(this);
        findViewById(R.id.btn_move_left).setOnTouchListener(this);
        findViewById(R.id.btn_move_right).setOnTouchListener(this);
        findViewById(R.id.btn_move_up).setOnTouchListener(this);
        findViewById(R.id.btn_move_down).setOnTouchListener(this);
        findViewById(R.id.btn_pitch_up).setOnTouchListener(this);
        findViewById(R.id.btn_pitch_down).setOnTouchListener(this);
        findViewById(R.id.btn_yaw_left).setOnTouchListener(this);
        findViewById(R.id.btn_yaw_right).setOnTouchListener(this);
        findViewById(R.id.btn_zoom_in).setOnTouchListener(this);
        findViewById(R.id.btn_zoom_out).setOnTouchListener(this);
        findViewById(R.id.btn_sc).setOnTouchListener(this);
        //findViewById(R.id.btn_use_f_prj).setOnTouchListener(this);
        //findViewById(R.id.btn_use_o_prj).setOnTouchListener(this);
        //findViewById(R.id.btn_push_near_plane).setOnTouchListener(this);
        findViewById(R.id.btn_reset_step).setOnTouchListener(this);
        findViewById(R.id.btn_prev_step).setOnTouchListener(this);
        findViewById(R.id.btn_next_step).setOnTouchListener(this);


        // 创建一个GLSurfaceView对象，并将其设置为当前Activity的ContentView
        mGLView = new MyGLSurfaceView(this);
        FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(MATCH_PARENT,MATCH_PARENT);
        FrameLayout glViewContainer = (FrameLayout) findViewById(R.id.gl_view_container);
        glViewContainer.setOnTouchListener(this);
        glViewContainer.addView(mGLView,layoutParams);


        btnNextStep = findViewById(R.id.btn_next_step);
        btnReset = findViewById(R.id.btn_reset_step);
        updateCurStep();
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


    private void updateCurStep(){
        btnReset.setText("复位"+"("+curStep+")");
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

        @Override
        public void surfaceDestroyed(SurfaceHolder holder){
            super.surfaceDestroyed(holder);
            renderer.term();
            Log.d("LOLILA","surfaceDestroyed, renderer.term()");
        }

    }

    private class JNIRenderer implements GLSurfaceView.Renderer {

        @Override
        public void onSurfaceCreated(GL10 gl10, EGLConfig eglConfig) {
            // 设置背景色
            //GLES20.glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
            RenderApi.init(0,mCourseNo);
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
        void cameraRotateLeft(){
            RenderApi.cameraRotateLeft();
        }
        void cameraRotateRight(){
            RenderApi.cameraRotateRight();
        }
        void cameraRotateUp(){
            RenderApi.cameraRotateUp();
        }
        void cameraRotateDown(){
            RenderApi.cameraRotateDown();
        }
        void cameraLookAtSceneCenter(){
            RenderApi.cameraLookAtSceneCenter();
        }
        void zoomIn(){RenderApi.zoomIn();}
        void zoomOut(){RenderApi.zoomOut();}
        void useFrustumPrj(){RenderApi.useFrustumPrj();}
        void useOrthoPrj(){RenderApi.useOrthoPrj();}
        void pushNearPlane(){RenderApi.pushNearPlane();}
        void term(){RenderApi.term();}
        void resetStep(){RenderApi.resetStep();}
        void nextStep(){RenderApi.nextStep();}
        void prevStep(){RenderApi.prevStep();}
    }


    ////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////

    private final class MyGestureListener extends GestureDetector.SimpleOnGestureListener {

        @Override
        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
            //Log.d("LOLILA","velocityX:"+velocityX+",velocityY:"+velocityY);
            Runnable runnable = null;
            float ax = Math.abs(velocityX);
            float ay = Math.abs(velocityY);
            final JNIRenderer renderer = mGLView.renderer;
            if( ax >ay){
                if( velocityX<0){
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.cameraRotateRight();
                        }
                    };
                }else{
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.cameraRotateLeft();
                        }
                    };
                }
            }else if(ay>ax){
                if( velocityY<0){
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.cameraRotateDown();
                        }
                    };
                }else{
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.cameraRotateUp();
                        }
                    };
                }
            }
            if(runnable!=null){
                final Runnable runnableF=runnable;
                new Thread(){
                    @Override
                    public void run(){
                        for (int i=1;i<= 90;++i){
                            mGLView.queueEvent(runnableF);
                            try {
                                Thread.sleep(10);
                            } catch (InterruptedException e) {
                                e.printStackTrace();
                            }
                        }
                    }
                }.start();
            }
            return true;
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return gestureDetector.onTouchEvent(event);
    }

    ////////////////////////////////////////////////////////////////////////////////////////
    //
    ////////////////////////////////////////////////////////////////////////////////////////


    private Object threadLock= new Object();
    private int pressedBtnId=-1;

    @Override
    public boolean onTouch(View v, MotionEvent event) {
        final int action = event.getAction();
        final int btnId = v.getId();
        //Log.d("LOLILA", "btnId:"+btnId+",action:"+action);
        if( btnId==R.id.gl_view_container){
            //Log.d("LOLILA","hit on gl_view_container");
            return false; // then will emit onTouchEvent
        }

        if( action == MotionEvent.ACTION_DOWN) {
            final JNIRenderer renderer = mGLView.renderer;
            Runnable runnable = null;
            switch (btnId) {
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
                case R.id.btn_sc:
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.cameraLookAtSceneCenter();
                        }
                    };
                    break;
                case R.id.btn_zoom_in:
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.zoomIn();
                        }
                    };
                    break;
                case R.id.btn_zoom_out:
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.zoomOut();
                        }
                    };
                    break;
                /*
                case R.id.btn_use_f_prj:
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.useFrustumPrj();
                        }
                    };
                    break;
                case R.id.btn_use_o_prj:
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.useOrthoPrj();
                        }
                    };
                    break;
                case R.id.btn_push_near_plane:
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.pushNearPlane();
                        }
                    };
                    break;

                 */

                case R.id.btn_reset_step:
                    curStep=0;
                    updateCurStep();
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.resetStep();
                        }
                    };
                    break;
                case R.id.btn_prev_step:
                    if(curStep>0) {
                        --curStep;
                    }
                    updateCurStep();
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.prevStep();
                        }
                    };
                    break;
                case R.id.btn_next_step:
                    ++curStep;
                    updateCurStep();
                    runnable = new Runnable() {
                        @Override
                        public void run() {
                            renderer.nextStep();
                        }
                    };
                    break;
            }
            if( runnable!=null){
                pressBtn(btnId,runnable);

            }
            //return true;
        }else if( action == MotionEvent.ACTION_UP || action==MotionEvent.ACTION_CANCEL || action == MotionEvent.ACTION_OUTSIDE){
             releaseBtn(btnId);
        }else if( !touchWithinBounds(event,v) ){
            releaseBtn(btnId);
        }

        v.onTouchEvent(event); // 吧事件传回给控件，使之有点击的效果
        return true;
    }

    private void pressBtn(final int btnId, final Runnable runnable){
        synchronized (threadLock){
            if( pressedBtnId!=-1 ){
                return;
            }
            pressedBtnId=btnId;


            new Thread(){
                @Override
                public void run(){
                    while (true){
                        synchronized (threadLock){
                            if(pressedBtnId==-1){
                                break;
                            }
                        }
                        if( runnable!=null){
                            Log.d("LOLILA","mGLView.queueEvent");
                            mGLView.queueEvent(runnable);
                        }
                        try {
                            Thread.sleep(100);
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        }
                    }
                }
            }.start();

        }
    }

    private void releaseBtn(final int btnId){
        synchronized (threadLock){
            if( pressedBtnId!=btnId){
                return;
            }
            pressedBtnId=-1;
        }
    }

    public static boolean touchWithinBounds(MotionEvent event, View view) {
        if (event == null || view == null || view.getWidth() == 0 || view.getHeight() == 0)
            return false;

        int[] viewLocation = new int[2];
        view.getLocationOnScreen(viewLocation);
        int viewMaxX = viewLocation[0] + view.getWidth() - 1;
        int viewMaxY = viewLocation[1] + view.getHeight() - 1;
        return (event.getRawX() <= viewMaxX && event.getRawX() >= viewLocation[0]
                && event.getRawY() <= viewMaxY && event.getRawY() >= viewLocation[1]);
    }

    private final static String getSDCardRootDir(){
        final String state = Environment.getExternalStorageState();
        if(state.equals(Environment.MEDIA_MOUNTED)){
            File path = Environment.getExternalStorageDirectory();
            if(path!=null)
                return path.getPath();
        }
        return "";
    }
}
