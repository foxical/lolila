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
    return FloatUtils::isEqual(Vector::dot(N,V),0);
}

bool PlaneIntersection::isParallel(const Plane& plane, const Line& line){
    return isParallel(plane,LineDistance::line2ray(line));
}

Vector  PlaneIntersection::intersects(const Plane& plane, const Ray& ray){
    const Vector& S = ray.endPoint();
    const Vector& V = ray.direction();
    const Vector& N = plane.N();
    const Vector& P = plane.P();
    const float D = -1.0*Vector::dot(N,P);

    const float NV = Vector::dot(N,V);
    if( FloatUtils::isEqual(NV,0)){
        throw runtime_error("Line is parallel to plane!");
    }

    const float t = -1.0*(Vector::dot(N,S)+D)/NV;
    return ray.pointAt(t);
}

Vector  PlaneIntersection::intersects(const Plane& plane, const Line& line ){
    return intersects(plane,LineDistance::line2ray(line));
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
