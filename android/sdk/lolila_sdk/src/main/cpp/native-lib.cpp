#include <jni.h>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

//#include <GLES3/gl3.h>

#include "base/geometry/Vector.h"
#include "base/geometry/Line.h"
#include "base/geometry/Ray.h"
#include "base/math/Matrix.h"
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

        Vector P(2,2,1);
        Vector Q(1,-2,0);
        Vector proj_pQ = Vector::proj(Q,P);

        //Vector v3p= v3.normalize();
        //sprintf(buff," v3:%s, v1 dot v3 is: %g, v2 dot v3 is: %g", v3.toString().c_str(),Vector::dot(v1,v3),Vector::dot(v2,v3));

        Vector p1(0,0);
        Vector p2(1,0);
        Vector p3(1,3);
        Ray l2(p1,Vector::minus(p2,p1));

        //float items[] = {2,0,0,0,3,0,0,0,4};
        //Matrix m(3,3,items);
        //float items[] = {1,0,0,0,2,2,3,0,8};
        //Matrix m(3,3,items);
        float items[] = {1,0,0,4,0,1,0,3,0,0,1,7,0,0,0,1};
        Matrix m(4,4,items);

        Matrix mr(m.invert());
        sprintf(buff," M invert is:\n%s\n, M x MR is:\n%s\n", mr.toString().c_str(), Matrix::multiply(m,mr).toString().c_str());

        //sprintf(buff," M :\n%s\n, M del(2,2) is:\n%s\n", m.toString().c_str(), Matrix::del(m,2,2).toString().c_str());

    }catch (exception& e){
        sprintf(buff,"exception: %s\n", e.what());
    }

    std::string hello(buff);
    return env->NewStringUTF(hello.c_str());
}
