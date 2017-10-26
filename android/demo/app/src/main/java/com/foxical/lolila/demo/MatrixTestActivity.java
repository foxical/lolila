package com.foxical.lolila.demo;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Matrix;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.DisplayMetrics;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.ImageView;

import java.lang.ref.WeakReference;

/**
 * Created by Administrator on 2017/10/24.
 */

public class MatrixTestActivity extends Activity implements View.OnTouchListener {


    public static void start(Context ctx){
        ctx.startActivity(new Intent(ctx,MatrixTestActivity.class));
    }


    private TransformMatrixView view;
    private static int scrWidth,scrHeight;
    private PlayHandler playHandler;
    private static float sDegree=0f;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        requestWindowFeature(Window.FEATURE_NO_TITLE);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN, WindowManager.LayoutParams.FLAG_FULLSCREEN);

        WindowManager manager = this.getWindowManager();
        DisplayMetrics outMetrics = new DisplayMetrics();
        manager.getDefaultDisplay().getMetrics(outMetrics);
        scrWidth = outMetrics.widthPixels;
        scrHeight = outMetrics.heightPixels;


        view = new TransformMatrixView(this);
        view.setScaleType(ImageView.ScaleType.MATRIX);
        view.setOnTouchListener(this);

        setContentView(view);


    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        stopPlay();
    }

    @Override
    public boolean onTouch(View v, MotionEvent e) {
        if (e.getAction() == MotionEvent.ACTION_UP) {

            if( playHandler==null){
                playHandler=new PlayHandler(this);
                startPlay();
            }

        }
        return true;
    }




    class TransformMatrixView extends ImageView
    {
        private Bitmap bitmap;
        private Matrix matrix;
        private final float imgWidth;
        private final float imgHeight;
        public TransformMatrixView(Context context){
            super(context);
            bitmap = BitmapFactory.decodeResource(getResources(), R.drawable.default_searchl_icon);
            imgWidth = bitmap.getWidth();
            imgHeight = bitmap.getHeight();

            matrix = setupMatrix(0f);

        }

        @Override
        protected void onDraw(Canvas canvas){

            // 画出变换后的图像
            canvas.drawBitmap(bitmap, matrix, null);
            super.onDraw(canvas);
        }

        @Override
        public void setImageMatrix(Matrix matrix)
        {
            this.matrix.set(matrix);
            super.setImageMatrix(matrix);
        }

        public Matrix setupMatrix(float degree){

            Matrix matrix = new Matrix();

            // 先以自己的左上角为中心，旋转-90度
            matrix.setRotate(-90f);

            // 旋转之后，会超出屏幕显示范围之外，因此要平移回【0，0】
            matrix.postTranslate(0,imgWidth);

            // 再平移到预备位置：屏幕中点的左侧
            final float offX = (scrWidth/2f - imgHeight)/2f;
            final float offY = scrHeight/2f - imgWidth/2f;
            matrix.postTranslate(offX,offY);

            // 以屏幕中心为原点，旋转
            matrix.postRotate(degree,scrWidth/2f,scrHeight/2f);

            return matrix;
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////
    //
    //////////////////////////////////////////////////////////////////////////////////////////

    private static final int PLAY_DEALY_TIME = 50;
    private static final int MSG_PLAY = 1 << 0;

    private static class PlayHandler extends Handler {
        final WeakReference<MatrixTestActivity> weakRef;
        PlayHandler(MatrixTestActivity p) {
            weakRef = new WeakReference(p);
        }
        @Override
        public void handleMessage(Message msg) {
            MatrixTestActivity p = weakRef.get();
            if (p == null || p.view==null) {
                return;
            }
            switch (msg.what) {
                case MSG_PLAY:
                    if( (sDegree+1f) >= 360f){
                        sDegree=0f;
                    }else{
                        sDegree+=1f;
                    }
                    p.view.setImageMatrix(p.view.setupMatrix(sDegree));
                    p.view.invalidate();
                    sendEmptyMessageDelayed(MSG_PLAY, PLAY_DEALY_TIME);
                    break;
            }
        }
    }

    public void stopPlay() {
        if(playHandler!=null) {
            playHandler.removeMessages(MSG_PLAY);
        }
    }

    //@Override
    public void startPlay() {

        if (playHandler!=null && !playHandler.hasMessages(MSG_PLAY)) {
            playHandler.sendEmptyMessageDelayed(MSG_PLAY, PLAY_DEALY_TIME);
        }
    }
}
