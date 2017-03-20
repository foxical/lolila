#include <jni.h>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>

#include "base/math/Vector.h"


extern "C"
jstring
Java_com_foxical_lolila_sdk_IndexApi_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {


    Vector v1(1,2);
    Vector v2(3,4);

    char buff[128];
    sprintf(buff," v1 dot v2 is: %f", Vector::dot(v1,v2));
    std::string hello(buff);
    return env->NewStringUTF(hello.c_str());
}
