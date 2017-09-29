//
// Created by Administrator on 2017/4/6.
//

#include <stdexcept>
#include "PlaneIntersection.h"
#include "LineDistance.h"
#include "Vector.h"
#include "Ray.h"
#include "Line.h"
#include "Plane.h"
#include "../utils/FloatUtils.h"
#include "../math/Matrix.h"
#include "../utils/LogQueue.h"

bool PlaneIntersection::isParallel(const Plane& plane, const Ray& ray ){
    const Vector& V = ray.direction();
    const Vector& N = plane.N();
    return FloatUtils::isEqual(Vector::dot(N,V),0.0);
}

bool PlaneIntersection::isParallel(const Plane& plane, const Line& line){
    return isParallel(plane,Line::line2ray(line));
}

bool PlaneIntersection::isParallel(const Plane& p1, const Plane& p2){
    return LineDistance::isParallel(p1.N(),p2.N());
}

Vector  PlaneIntersection::intersects(const Plane& plane, const Ray& ray){
    const Vector& S = ray.endPoint();
    const Vector& V = ray.direction();
    const Vector& N = plane.N();
    const Vector& P = plane.P();
    const double D = -1.0*Vector::dot(N,P);

    const double NV = Vector::dot(N,V);
    if( FloatUtils::isEqual(NV,0)){
        throw runtime_error("Line is parallel to plane!");
    }

    const double t = -1.0*(Vector::dot(N,S)+D)/NV;
    return ray.pointAt(t);
}

Vector  PlaneIntersection::intersects(const Plane& plane, const Line& line ){
    return intersects(plane,Line::line2ray(line));
}

// 求任意两个平面交线的算法
// 先检查两个平面的法向量N1,N2是否平行，若平行，则两个平面平行，抛出异常
// 求交线的方向IV， IV必定与N1和N2都垂直，因此IV等于N1 X N2
// 确定位于这个交线上的一个点就可以了
// 首先求和IV和N1都垂直的矢量IV_C = IV X N1
// 作一条射线，原点是P1， 方向为IV_C
// 求这条射线与平面plane2的交点IP
// 射线《IP,IV》即为所求
Ray PlaneIntersection::intersects(const Plane& plane1,const Plane& plane2){

    const Vector& N1 = plane1.N();
    const Vector& N2 = plane2.N();

    if( LineDistance::isParallel(N1,N2)){
        throw runtime_error("the two planes is parallel!");
    }

    const Vector IV = Vector::cross(N1,N2);
    //LogQueue::push("IV:%s\n",IV.c_str());

    const Vector IV_C = Vector::cross(IV,N1);
    //LogQueue::push("IV_C:%s\n",IV_C.c_str());

    const Ray RC(plane1.P(),IV_C);

    const Vector IP = intersects(plane2,RC);
    //LogQueue::push("IP:%s\n",IP.c_str());

    return Ray(IP,IV);
}

// 求两平面交线的第二个方法
// IV的求法是一样的
// 这次以IV作为法向量，以座标原点O作为平面原点
// 求这个平面和两个平面的交点Q
// 射线《Q,IV》即为所求
Ray PlaneIntersection::intersects_v2(const Plane& plane1,const Plane& plane2){

    const Vector& N1 = plane1.N();
    const Vector& N2 = plane2.N();

    if( LineDistance::isParallel(N1,N2)){
        throw runtime_error("the two planes is parallel!");
    }

    const Vector IV = Vector::cross(N1,N2);

    const Plane plane3(IV,Vector(0,0,0));

    const Vector Q(intersects(plane1,plane2,plane3));

    return Ray(Q,IV);
}

Vector PlaneIntersection::intersects(const Plane& plane1,const Plane& plane2,const Plane& plane3){

    const Vector& N1 = plane1.N();
    const Vector& N2 = plane2.N();
    const Vector& N3 = plane3.N();

    Matrix M(3,3);
    M.set(0,0,N1.x());M.set(0,1,N1.y());M.set(0,2,N1.z());
    M.set(1,0,N2.x());M.set(1,1,N2.y());M.set(1,2,N2.z());
    M.set(2,0,N3.x());M.set(2,1,N3.y());M.set(2,2,N3.z());
    LogQueue::push("M is:%s",M.c_str());

    const double detM = M.determinant();
    LogQueue::push("detM is:%.8lf\n",detM);
    if( FloatUtils::isEqual(detM,0.0)){
        throw runtime_error("The three planes do not intersect at a point.");
    }

    Matrix D(3,1);
    D.set(0,0,-1.0*plane1.D());
    D.set(1,0,-1.0*plane2.D());
    D.set(2,0,-1.0*plane3.D());
    LogQueue::push("D is:%s",D.c_str());

    const Matrix Q = Matrix::multiply(Matrix::scalarMultiply(M.cofactors(),1.0/detM),D);
    LogQueue::push("Q is: %s",Q.c_str());

    return Vector(Q.get(0,0),Q.get(1,0),Q.get(2,0));
}
