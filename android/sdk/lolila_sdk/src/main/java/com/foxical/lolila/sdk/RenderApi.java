package com.foxical.lolila.sdk;

/**
 * Created by Administrator on 2017/10/10.
 */

public final class RenderApi {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public static native void init();
    public static native void resize(int w,int h);
    public static native void draw();

    public static native void cameraMoveForward();
    public static native void cameraMoveBack();
    public static native void cameraMoveLeft();
    public static native void cameraMoveRight();
    public static native void cameraMoveUp();
    public static native void cameraMoveDown();
    public static native void cameraPitchUp();
    public static native void cameraPitchDown();
}
