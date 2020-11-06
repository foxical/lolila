//
// Created by tam on 2020/11/6.
//

#include "Box.h"
#include "Ray.h"
#include "../transforms/Translate.h"
#include "../transforms/Rotation.h"
#include "../transforms/Scaling.h"
#include "../utils/AndroidLog.h"


Box::Box(float w, float h, float d):
_p0(0,0,0),
_p1(w,0,0),
_p2(w,h,0),
_p3(0,h,0),
_p4(0,0,-d),
_p5(w,0,-d),
_p6(w,h,-d),
_p7(0,h,-d),
_plane0(_p0,_p1,_p2,_p3),
_plane1(_p1,_p5,_p6,_p2),
_plane2(_p5,_p4,_p7,_p6),
_plane3(_p4,_p0,_p3,_p7),
_plane4(_p4,_p5,_p1,_p0),
_plane5(_p3,_p2,_p6,_p7),
curTransformMat(4,4)
{
    /*
    LOGD("w:%f,h:%f,d:%f",getWidth(),getHeight(),getDepth());
    LOGD("plane0,N:%s",_plane0.getN().c_str());
    LOGD("plane1,N:%s",_plane1.getN().c_str());
    LOGD("plane2,N:%s",_plane2.getN().c_str());
    LOGD("plane3,N:%s",_plane3.getN().c_str());
    LOGD("plane4,N:%s",_plane4.getN().c_str());
    LOGD("plane5,N:%s",_plane5.getN().c_str());
    */
    Scaling::buildScalingMatrix(Vector(w,h,d),curTransformMat);
}

Box::~Box() {

}

float Box::getWidth()const{
    return Vector::minus(_p1,_p0).length();
}
float Box::getHeight()const{
    return Vector::minus(_p3,_p0).length();
}
float Box::getDepth()const{
    return Vector::minus(_p4,_p0).length();
}

bool  Box::surfaceIntersectionCheck(const Ray& ray, Vector& crossPoint,Vector& weight)const{

    const Vector& V = ray.direction();

    const BoxPlane* pa[]={ &_plane0,&_plane1,&_plane2,&_plane3,&_plane4,&_plane5  };

    int bingoCount=0;
    bool suc=false;
    for(int i=0;i<6;++i){
        const BoxPlane* plane = pa[i];
        const Vector& N = plane->getN();
        if( Vector::dot(N,V)<0.0f){
            bingoCount++;
            if( plane->surfaceIntersectionCheck(ray,crossPoint,weight) ){
                suc=true;
                break;
            }
        }
    }
    LOGD("bingoCount:%i",bingoCount);
    return suc;
}

void Box::translate(const Vector& t){
    _p0 = Translate::doTransform(t,_p0);
    _p1 = Translate::doTransform(t,_p1);
    _p2 = Translate::doTransform(t,_p2);
    _p3 = Translate::doTransform(t,_p3);
    _p4 = Translate::doTransform(t,_p4);
    _p5 = Translate::doTransform(t,_p5);
    _p6 = Translate::doTransform(t,_p6);
    _p7 = Translate::doTransform(t,_p7);
    Matrix m(4,4);
    Translate::buildTranslateMatrix(t,m);
    curTransformMat.set(Matrix::multiply(m,curTransformMat));
}

void Box::rotate(const Vector& axis,float angle){

    _p0 = Rotation::doTransform(axis,angle,_p0);
    _p1 = Rotation::doTransform(axis,angle,_p1);
    _p2 = Rotation::doTransform(axis,angle,_p2);
    _p3 = Rotation::doTransform(axis,angle,_p3);
    _p4 = Rotation::doTransform(axis,angle,_p4);
    _p5 = Rotation::doTransform(axis,angle,_p5);
    _p6 = Rotation::doTransform(axis,angle,_p6);
    _p7 = Rotation::doTransform(axis,angle,_p7);
    Matrix m(4,4);
    Rotation::buildRotationMatrix(axis,angle,m);
    curTransformMat.set(Matrix::multiply(m,curTransformMat));
}
