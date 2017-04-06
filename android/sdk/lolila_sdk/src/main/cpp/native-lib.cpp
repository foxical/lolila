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
#include "base/utils/FloatUtils.h"
#include "base/geometry/Plane.h"
#include "base/geometry/PlaneIntersection.h"
#include <exception>
#include <stdexcept>
#include <math.h>

using namespace std;


static void testLineDistance(){
    Vector p1_1(-2,-2,1);
    Vector p1_2(2,2,1);
    Vector p2_1(0,0,0);
    Vector p2_2(2,0,0);
    Line l1(p1_1,p1_2);
    Line l2(p2_1,p2_2);
    LineDistance::calc(l1,l2);
}

static void testPlanes(){

    Vector N(0,0,1);
    Vector P(0,0,0);
    Plane plane(N,P);

    Vector p2_1(1.7890,0,0);
    Vector p2_2(2,0,1);
    Line l2(p2_1,p2_2);

    LogQueue::push("Point lies in plane: %d\n",plane.pointLiesInPlane(Vector(-1.45454,0.1998,0.00)));
    LogQueue::push("Line isParallel to plane: %d\n",PlaneIntersection::isParallel(plane,l2));
    LogQueue::push("Line interrects to plane at point:%s\n",PlaneIntersection::intersects(plane,l2).c_str());
}

extern "C"
jstring
Java_com_foxical_lolila_sdk_IndexApi_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    try{

        LogQueue::clear();

        testPlanes();

        return env->NewStringUTF( LogQueue::c_str());

    }catch (exception& e){
        char buff[1024];
        sprintf(buff,"exception: %s\n", e.what());
        std::string hello(buff);
        return env->NewStringUTF(hello.c_str());
    }


}

