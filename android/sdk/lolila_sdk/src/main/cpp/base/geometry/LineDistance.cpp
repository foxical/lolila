//
// Created by Administrator on 2017/3/31.
//
#include <math.h>
#include "LineDistance.h"
#include "Line.h"
#include "Ray.h"
#include "../math/Matrix.h"
#include "../utils/LogQueue.h"


Ray LineDistance::line2ray(const Line& l){
    return Ray(l.point1(),Vector::minus(l.point2(),l.point1()));
}

float LineDistance::calc(const Ray& l1,const Ray& l2){
    LogQueue::push("LineDistance::calc begin...\n");

    const Vector& V1 = l1.direction();
    LogQueue::push("V1 is:%s\n",V1.c_str());

    const Vector& V2 = l2.direction();
    LogQueue::push("V2 is:%s\n",V2.c_str());

    const float V1V2 = Vector::dot(V1,V2);
    Matrix M(2,2);
    M.set(0,0,Vector::dot(V1,V1));M.set(0,1,-1.0*V1V2);
    M.set(1,0,V1V2);              M.set(1,1,-1.0*Vector::dot(V2,V2));
    LogQueue::push("M is:%s",M.c_str());

    const int detM = M.determinant();
    LogQueue::push("detM is:%d\n",detM);

    if( detM==0){
        LogQueue::push("Ll and L2 is parallel!\n");
        const Vector pAtL2 = l2.pointAt(0);
        LogQueue::push("get first point on L2: %s\n",pAtL2.c_str());
        const float result = l1.distance(pAtL2);
        LogQueue::push("distance between L1 and L2 is:%g\n",result);
        LogQueue::push("LineDistance::calc end.\n");
        return result;
    }

    const Vector& S1 = l1.endPoint();
    LogQueue::push("S1 is:%s\n",S1.c_str());

    const Vector& S2 = l2.endPoint();
    LogQueue::push("S2 is:%s\n",S2.c_str());

    const Vector& S2_S1 = Vector::minus(S2,S1);
    LogQueue::push("S2-S1 is:%s\n",S2_S1.c_str());


    Matrix R(2,1);
    R.set(0,0,Vector::dot(S2_S1,V1));
    R.set(1,0,Vector::dot(S2_S1,V2));
    LogQueue::push("R is: %s",R.c_str());


    const Matrix T = Matrix::multiply(Matrix::scalarMultiply(M.cofactors(),1.0/detM),R);
    LogQueue::push("T is: %s",T.c_str());


    const float  t1 = T.get(0,0);
    const Vector p1 = l1.pointAt(t1);
    LogQueue::push("point at L1: %s\n",p1.c_str());

    const float  t2 = T.get(1,0);
    const Vector p2 = l2.pointAt(t2);
    LogQueue::push("point at L2: %s\n",p2.c_str());


    const float distance = Vector::dot(p1,p1) + Vector::dot(p2,p2) - 2.0*(Vector::dot(p1,p2));
    const float  result = sqrtf(distance);
    LogQueue::push("distance between L1 and L2 is:%g\n",result);
    //LogQueue::push("distance v2 between L1 and L2 is:%g\n",Vector::minus(p1,p2).length());
    LogQueue::push("LineDistance::calc end.\n");
    return result;
}

float LineDistance::calc(const Line& l1, const Line& l2){
    return calc(line2ray(l1),line2ray(l2));
}

float LineDistance::calc(const Line& l1, const Ray& l2){
    return calc(line2ray(l1),l2);
}

float LineDistance::calc(const Ray& l1,const Line& l2){
    return calc(l1,line2ray(l2));
}
