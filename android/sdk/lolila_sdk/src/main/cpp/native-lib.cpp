#include <jni.h>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

//#include <GLES3/gl3.h>

#include "base/geometry/Vector.h"
#include "base/geometry/Line.h"
#include "base/geometry/Ray.h"
#include "base/math/Matrix.h"
#include "base/geometry/LineDistance.h"
#include "base/utils/AndroidLog.h"
#include "base/utils/LogQueue.h"
#include <exception>
#include <stdexcept>
#include <math.h>

using namespace std;

extern "C"
jstring
Java_com_foxical_lolila_sdk_IndexApi_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    try{

        LogQueue::clear();


        //sprintf(buff," v1 dot v2 is: %f", Vector::dot(v1,v2));

        Vector P(-1,0,0);
        Vector Q(1,0,0);
        Vector V(1,1,1);
        Vector p_plua_q = Vector::dot(P,Q);

        float  ss = -2.0*Vector::dot(V,V);
        //Vector v3p= v3.normalize();


        Vector p1_1(-2,-2,1);
        Vector p1_2(2,2,3.6);
        Vector p2_1(0,0,0);
        Vector p2_2(2,0,0);
        Line l1(p1_1,p1_2);
        Line l2(p2_1,p2_2);
        //float items[] = {2,0,0,0,3,0,0,0,4};
        //Matrix m(3,3,items);
        //float items[] = {1,0,0,0,2,2,3,0,8};
        //Matrix m(3,3,items);
        //float items[] = {1,0,0,4,0,1,0,3,0,0,1,7,0,0,0,1};
        //Matrix m(4,4,items);

        //Matrix mr(m.invert());
        LineDistance::calc(l1,l2);
        //sprintf(buff," p1 is:%s, p2 is:%s", LineDistance::ps1.c_str(), LineDistance::ps2.c_str());

        //sprintf(buff," distance between  l1 and l2 is:%g\n", LineDistance::calc(l1,l2));


        Ray r1 = LineDistance::line2ray(l1);
        Ray r2 = LineDistance::line2ray(l2);

        const Vector& V1 = r1.direction();
        const Vector& V2 = r2.direction();

        //sprintf(buff," point At 1.5 is:%s\n", r1.pointAt(1.5).toString().c_str());



        return env->NewStringUTF( LogQueue::c_str());

    }catch (exception& e){
        char buff[1024];
        sprintf(buff,"exception: %s\n", e.what());
        std::string hello(buff);
        return env->NewStringUTF(hello.c_str());
    }


}
