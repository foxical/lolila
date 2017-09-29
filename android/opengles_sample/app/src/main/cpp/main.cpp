#include <EGL/egl.h>
#include <GLES3/gl3.h>


#include <android/sensor.h>
#include <android/log.h>
#include <android_native_app_glue.h>

extern "C"
void android_main(struct android_app* state) {
    //接下来，程序处理由 glue 库排入队列的事件。事件处理程序遵循状态结构。

    //struct engine engine;



// Suppress link-time optimization that removes unreferenced code
// to make sure glue isn't stripped.
    app_dummy();
/*

    memset(&engine, 0, sizeof(engine));
    state->userData = &engine;
    state->onAppCmd = engine_handle_cmd;
    state->onInputEvent = engine_handle_input;
    engine.app = state;
    //应用准备开始使用 sensor.h 中的 API 监控传感器。

    engine.sensorManager = ASensorManager_getInstance();
    engine.accelerometerSensor =
            ASensorManager_getDefaultSensor(engine.sensorManager,
                                            ASENSOR_TYPE_ACCELEROMETER);
    engine.sensorEventQueue =
            ASensorManager_createEventQueue(engine.sensorManager,
                                            state->looper, LOOPER_ID_USER, NULL, NULL);
    //接下来循环开始，应用就消息（传感器事件）对系统进行轮询。 它将消息发送至 android_native_app_glue，由后者检查消息是否与 android_main 中定义的任何 onAppCmd 事件匹配。 若匹配，消息会发送给处理程序并执行。

    while (1) {
        // Read all pending events.
        int ident;
        int events;
        struct android_poll_source *source;


        // If not animating, we will block forever waiting for events.
        // If animating, we loop until all events are read, then continue
        // to draw the next frame of animation.
        while ((ident = ALooper_pollAll(engine.animating ? 0 : -1, NULL,
                                        &events,
                                        (void **) &source)) >= 0) {


            // Process this event.
            if (source != NULL) {
                source->process(state, source);
            }


            // If a sensor has data, process it now.
            if (ident == LOOPER_ID_USER) {
                if (engine.accelerometerSensor != NULL) {
                    ASensorEvent event;
                    while (ASensorEventQueue_getEvents(engine.sensorEventQueue,
                                                       &event, 1) > 0) {
                        LOGI("accelerometer: x=%f y=%f z=%f",
                             event.acceleration.x, event.acceleration.y,
                             event.acceleration.z);
                    }
                }
            }


            // Check if we are exiting.
            if (state->destroyRequested != 0) {
                engine_term_display(&engine);
                return;
            }
        }
        //当队列为空，且程序退出轮询循环后，程序会调用 OpenGL 在屏幕上绘图。

        if (engine.animating) {
            // Done with events; draw next animation frame.
            engine.state.angle += .01f;
            if (engine.state.angle > 1) {
                engine.state.angle = 0;
            }


            // Drawing is throttled to the screen update rate, so there
            // is no need to do timing here.
            engine_draw_frame(&engine);
        }
    }
*/


    for(uint8_t ui = 0; ui < 100; ++ui)
    {
        // The function prints to log cat the index of the for loop
        __android_log_print(
                ANDROID_LOG_INFO,
                "UFO Tap Attack",
                " -- CUFOTapAttack::android_main(), ui == %d \n",
                ui);

    } // End of for(uint8_t ui = 0; ui < 100; ++ui)
}
