#include <jni.h>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

#include <GLES3/gl3.h>

extern "C"
jstring
Java_com_foxical_lolila_sdk_IndexApi_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";



    return env->NewStringUTF(hello.c_str());
}
