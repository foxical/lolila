#include <jni.h>
#include <string>

#include <android/asset_manager_jni.h>
#include <android/log.h>

#include <GLES3/gl3.h>

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
#include "base/geometry/Projections.h"
#include "base/transforms/Rotation.h"
#include "base/transforms/MVPTransform.h"
#include "base/transforms/Translate.h"
#include <exception>
#include <stdexcept>
#include <math.h>

#include <dirent.h>

#include "base/math/Fraction.h"

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
//
//    Vector N1(1,6,9);
//    Vector P1(4,5,0);
//    Plane plane1(N1,P1);
//
//    Vector N2(7,1,6);
//    Vector P2(3,0,-9);
//    Plane plane2(N2,P2);
//
//    Vector N3(-50,-90,134);
//    Vector P3(40,-67,90);
//    Plane plane3(N3,P3);
//
//    PlaneIntersection::intersects(plane1,plane2,plane3);

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

    Vector N1(0,0,9);
    Vector P1(0,0,1);
    Plane plane1(N1,P1);

    LogQueue::push("p1 D is %g\n",plane1.distanceFromOri());
}

static void testProjections(){

    float left=-2.0;
    float right=2.0;
    float top=2.0;
    float bottom=-2.0;
    float near = 1.0;
    float far = 3.0;

    Vector P1(2.0,2.0,-3);
    LogQueue::push("p1 project: %s\n",Projections::perspectiveProjection(left,top,right,bottom,near,far,P1).c_str());
    //LogQueue::push("p1 project_v2: %s\n",Projections::perspectiveProjection_v2(left,top,right,bottom,near,far,P1).c_str());
    Vector P2(2.0,2.0,-2);
    LogQueue::push("p2 project: %s\n",Projections::perspectiveProjection(left,top,right,bottom,near,far,P2).c_str());
    //LogQueue::push("p2 project_v2: %s\n",Projections::perspectiveProjection_v2(left,top,right,bottom,near,far,P2).c_str());

}

static void testMisc(){
    double ddd[]={1.0f,2.0f,3.0f };

    const double* pd = ddd;

    LOGI("sizeof float:%d,sizeof double:%d", sizeof(float), sizeof(double));

    const float * pf = (const float *) pd;
    for( int i=0;i< 3;++i){
        LOGI("float:%.8lf, double:%.8lf",pf[i],pd[i]);
    }
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
        //testProjections();

        //testMisc();
        //LogQueue::push("b is %g\n",ViewFrustum::getVerticalViewAngle(1280,1024,75.0f));

        /*
        float m0[]={1,-1,0,1,1,0,0,0,1};
        Matrix M0(3,3,m0);
        float m1[]={1,0,-1,0,1,-1,0,0,1};
        Matrix M1(3,3,m1);

        float v[]={1,0,-1,1};
        Matrix MV(4,1,v);

        Matrix MC(4,4);
        MVPTransform::buildLookAtMatrix(1,0,1,0,0,0,Vector(0,1,0),MC);

        //LOGD("camera:%s", Matrix::multiply(MC,MV).c_str());

        Matrix MR(4,4);
        Rotation::buildRotationMatrix(Vector(0,1,0),-45.0f,MR);
        LOGD("MR:%s",MR.c_str());

        Matrix MVT = MVPTransform::vec2mat(Translate::doTransform(Vector(-1,0,-1),Vector(1,0,-1)));
        LOGD("rotation:%s", Matrix::multiply(MR,MVT).c_str());


        float mm[]={1,0,0,0,1,0,0,0,1};
        Matrix MF(3,3,mm);
        LOGD("MF-1:%s",MF.invert().c_str());
         */


        /*
        const char* rootPath = "/storage/emulated/0";
        DIR* dir;
        dir = opendir(rootPath);
        if (dir != NULL) {
            dirent* currentDir;
            while ((currentDir = readdir(dir)) != NULL) {  //readdir()方法就像java中迭代器的next()方法一样
                //currentDir->d_name; //文件名，目录名
                //currentDir->d_type; //类型，是目录还是文件啥的
                LOGD("dirName:%s,type:%d",currentDir->d_name,currentDir->d_type);
            }
            closedir(dir); //用完要关掉，要不然会出错的
        }else{
            LOGD("open dir failed");
        }
         */


        {

            Matrix MF(4, 4);
            LOGD("isMostSimplest :%i",MF.isMostSimplest()?1:0);
        }

        {

            Matrix MF = Matrix::createIdentityMatrix(4);
            LOGD("isMostSimplest :%i",MF.isMostSimplest()?1:0);
        }

        {
            float mm[] = {
                    3, 2, -3, 5,
                    4, -3, 6, 1,
                    0, 0, 1.0, 3,
                    0, 0, 0, 1.0
            };
            Matrix MF(4, 4, mm);
            LOGD("isMostSimplest :%i",MF.isMostSimplest()?1:0);
        }

        {
            float mm[] = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 0,
                    0, 0, 0, 1
            };
            Matrix MF(4, 4, mm);
            LOGD("isMostSimplest :%i",MF.isMostSimplest()?1:0);
        }

        {
            float mm[] = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 1,
                    0, 0, 1, 0
            };
            Matrix MF(4, 4, mm);
            LOGD("Mat:%s",MF.toString().c_str());
            LOGD("isMostSimplest :%i",MF.isMostSimplest()?1:0);
        }

        {
            float mm[] = {
                    1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 0, 1,
                    0, 0, 0, 0
            };
            Matrix MF(4, 4, mm);
            LOGD("Mat:%s",MF.toString().c_str());
            LOGD("isMostSimplest :%i",MF.isMostSimplest()?1:0);
        }


        //LOGD("MF:%s",MF.c_str());
        //MF.elementary_line_transformation(0);
        //MF.elementary_line_transformation(1);
        //MF.elementary_line_transformation(2);
        //LOGD("isZeroRow of 0 :%i",MF.isZeroRow(0)?1:0);
        //LOGD("first 1 idx :%i",MF.getFirstOneColIdx(3));

        Fraction fraction("2/4");
        fraction.reduce();

        LOGD("fraction :%s",fraction.c_str());


        return env->NewStringUTF( LogQueue::c_str());

    }catch (exception& e){
        char buff[1024];
        sprintf(buff,"exception: %s\n", e.what());
        LOGD("exception:%s",buff);
        std::string hello(buff);
        return env->NewStringUTF(hello.c_str());
    }


}

