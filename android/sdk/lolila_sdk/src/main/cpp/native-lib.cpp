#include <jni.h>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>

#include "base/math/Vector.h"
#include <exception>
#include <stdexcept>

using namespace std;

extern "C"
jstring
Java_com_foxical_lolila_sdk_IndexApi_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {


    char buff[1024];

    try{

        //sprintf(buff," v1 dot v2 is: %f", Vector::dot(v1,v2));

        Vector v1(1,2,3);
        Vector v2(4,5,6);
        Vector v3 = v1.cross(v2);

        Vector v3p= v3.normalize();
        //sprintf(buff," v3:%s, v1 dot v3 is: %g, v2 dot v3 is: %g", v3.toString().c_str(),Vector::dot(v1,v3),Vector::dot(v2,v3));

        sprintf(buff," v3p len:%g\n", v3p.length());

    }catch (exception& e){
        sprintf(buff,"exception: %s\n", e.what());
    }

    std::string hello(buff);
    return env->NewStringUTF(hello.c_str());
}
