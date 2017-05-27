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
#include "base/geometry/ViewFrustum.h"
#include <exception>
#include <stdexcept>
#include <math.h>

using namespace std;

extern Vector v_perp_to_n_and_not_perp_to_m(const Vector& N, const Vector& M,const Vector& P,const float& dot );

static void testLineDistance(){
    Vector p1_1(-2,-2,1);
    Vector p1_2(2,2,1);
    Vector p2_1(0,0,0);
    Vector p2_2(2,0,0);
    Line l1(p1_1,p1_2);
    Line l2(p2_1,p2_2);
    LineDistance::calc(l1,l2);
}

static void testPointLies(){
    Line l(Vector(0,0),Vector(2,2));
    Vector p1(0.5,0.5);
    Vector p2(1,0);
    LogQueue::push("p1 lies in line:%d, p2 lies in line:%d\n",l.pointLiesInLine(p1),l.pointLiesInLine(p2));
    LogQueue::push("p1 lies in line:%d, p2 lies in line:%d\n",LineDistance::pointLiesInLine(p1,l),LineDistance::pointLiesInLine(p2,l));

    const float f1=0.5,f2=0.5;
    LogQueue::push(" a-b:%g\n",f1-f2);
}

static void testPlanes(){

    Vector N1(1,6,9);
    Vector P1(4,5,0);
    Plane plane1(N1,P1);

    Vector N2(7,1,6);
    Vector P2(3,0,-9);
    Plane plane2(N2,P2);

    Vector N3(-50,-90,134);
    Vector P3(40,-67,90);
    Plane plane3(N3,P3);

    PlaneIntersection::intersects(plane1,plane2,plane3);

//    Ray RC(PlaneIntersection::intersects_v2(plane1,plane2));
//
//    string s1 = RC.endPoint().toString();
//    string s2 = RC.direction().toString();
//    LogQueue::push("RC  S:%s,V:%s\n",s1.c_str(),s2.c_str());
//
//    for(float t=0;t<1.0;t+=0.1){
//        Vector p = RC.pointAt(t);
//        LogQueue::push("Point at RC:%s, lies in plane1:%d, lies in plane2:%d\n",p.c_str(),plane1.pointLiesInPlane(p),plane2.pointLiesInPlane(p));
//
//    }

//    LogQueue::push("Line isParallel to plane: %d\n",PlaneIntersection::isParallel(plane,l2));
//    LogQueue::push("Line interrects to plane at point:%s\n",PlaneIntersection::intersects(plane,l2).c_str());


//    Vector N(2,0,2);
//    Vector M(4,0,1);
//    Vector P(1,0,1);
//
//    Vector v1 = v_perp_to_n_and_not_perp_to_m(N,M,P,1);
//    LogQueue::push("v1 is %s, dot with N is:%g, dot with M is:%g\n",v1.c_str(),Vector::dot(v1,N),Vector::dot(v1,M));
//    Vector v2 = v_perp_to_n_and_not_perp_to_m(N,M,P,2);
//    LogQueue::push("v2 is %s\n",v2.c_str());

}

extern "C"
jstring
Java_com_foxical_lolila_sdk_IndexApi_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {

    try{

        LogQueue::clear();

        //testLineDistance();
        //testPointLies();
        //testPlanes();

        LogQueue::push("b is %g\n",ViewFrustum::getVerticalViewAngle(1280,1024,75.0f));

        return env->NewStringUTF( LogQueue::c_str());

    }catch (exception& e){
        char buff[1024];
        sprintf(buff,"exception: %s\n", e.what());
        std::string hello(buff);
        return env->NewStringUTF(hello.c_str());
    }


}

