package com.foxical.lolila.demo.widget;

import android.annotation.TargetApi;
import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Build;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class RadarWidget extends View {

    private float cameraPosX;
    private float cameraPoxZ;
    private float scenePosX;
    private float scenePoxZ;
    private float yaw;

    public RadarWidget(Context context) {
        super(context);
    }

    public RadarWidget(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public RadarWidget(Context context, AttributeSet attrs, int defStyleAttr) {
        super(context, attrs, defStyleAttr);
    }

    @TargetApi(Build.VERSION_CODES.LOLLIPOP)
    public RadarWidget(Context context, AttributeSet attrs, int defStyleAttr, int defStyleRes) {
        super(context, attrs, defStyleAttr, defStyleRes);
    }

    public void setCameraPosX(float cameraPosX) {
        this.cameraPosX = cameraPosX;
    }

    public void setCameraPoxZ(float cameraPoxZ) {
        this.cameraPoxZ = cameraPoxZ;
    }

    public void setScenePosX(float scenePosX) {
        this.scenePosX = scenePosX;
    }

    public void setScenePoxZ(float scenePoxZ) {
        this.scenePoxZ = scenePoxZ;
    }

    public void setYaw(float yaw) {
        this.yaw = yaw;
    }

    /*
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
    }

     */

    @Override
    protected void onDraw(Canvas canvas) {
        //Log.d("LOLILA","RadarWidget onDraw");
        //Log.d("LOLILA","camera draw_x:"+getDrawX(cameraPosX)+",draw_z:"+getDrawZ(cameraPoxZ));

        drawPosPoint(canvas,getDrawX(scenePosX),getDrawZ(scenePoxZ), Color.BLUE);
        drawPosPoint(canvas,getDrawX(cameraPosX),getDrawZ(cameraPoxZ), Color.RED);
    }

    private float getDrawX(float x){
        final float _canvas_ox = (getMeasuredWidth()/2)*-1.0f;
        final float draw_x = x-_canvas_ox;
        return draw_x;
    }

    private float getDrawZ(float z){
        final float _canvas_oz = (getMeasuredHeight()/2)*-1.0f;
        final float draw_z = z-_canvas_oz;
        return draw_z;
    }

    private void drawPosPoint(Canvas canvas,float x,float z,int color){
        Paint p = new Paint();
        p.setAntiAlias(true);// 设置画笔的锯齿效果。 true是去除，大家一看效果就明白了
        p.setColor(color);
        canvas.drawCircle(x, z, 4, p);// 小圆


    }
}
