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