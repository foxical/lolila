//
// Created by tam on 2020/11/2.
//

#include "Triangle.h"
#include "Plane.h"
#include "PlaneIntersection.h"
#include "Ray.h"
#include "../utils/FloatUtils.h"
#include "../math/TMatrix.hpp"
#include "../math/FloatOutputAdapter.hpp"

Triangle::Triangle():_p0(0,0,0),_p1(0,0,0),_p2(0,0,0){

}

Triangle::Triangle(const Vector& p0,const Vector& p1,const Vector& p2):_p0(p0),_p1(p1),_p2(p2){

}
Triangle::Triangle(float px0, float py0, float pz0,
         float px1, float py1, float pz1,
         float px2, float py2, float pz2):_p0(px0,py0,pz0),_p1(px1,py1,pz1),_p2(px2,py2,pz2){

}
Triangle::~Triangle(){

}

void Triangle::setPoint(const Vector& p0,const Vector& p1,const Vector& p2){
    _p0=p0;
    _p1=p1;
    _p2=p2;
}

Vector Triangle::getN()const{
    return Vector::cross(Vector::minus(_p1,_p0),Vector::minus(_p2,_p0));
}

bool  Triangle::surfaceIntersectionCheck(const Ray& ray, Vector& crossPoint,Vector& weight)const{

    Plane plane(getN(),_p0);

    float  t = PlaneIntersection::intersects_f(plane,ray);
    if( FloatUtils::isEqual(t,-1.0f) ){
        return false;
    }

    crossPoint = ray.pointAt(t);

    const Vector& P = crossPoint;
    const Vector& R = Vector::minus(P,_p0);
    const Vector& Q1 = Vector::minus(_p1,_p0);
    const Vector& Q2 = Vector::minus(_p2,_p0);

    const float Q1Q1 = Vector::dot(Q1,Q1);
    const float Q2Q2 = Vector::dot(Q2,Q2);
    const float Q1Q2 = Vector::dot(Q1,Q2);
    const float RQ1  = Vector::dot(R,Q1);
    const float RQ2  = Vector::dot(R,Q2);

    const float T[]={
            Q1Q1,Q1Q2,RQ1,
            Q1Q2,Q2Q2,RQ2
    };
    TMatrix<float,FloatOutputAdapter> fm(T,2,3);
    //LOGD("before elementary_line_transformation:%s", fm.c_str() );
    fm.elementary_line_transformation();
    //LOGD("after elementary_line_transformation:%s", fm.c_str() );

    const float w1 = fm.get(0,2);
    const float w2 = fm.get(1,2);

    if( w1<0.0f || w2<0.0f){
        return false;
    }
    const float w0 = 1.0f-w1-w2;
    if( w0<0.0f){
        return false;
    }

    weight = Vector(w0,w1,w2);
    return true;
}
