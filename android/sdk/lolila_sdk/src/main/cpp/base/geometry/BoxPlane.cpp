//
// Created by tam on 2020/11/6.
//

#include "BoxPlane.h"
#include "Triangle.h"

BoxPlane::BoxPlane(const Vector &f0, const Vector &f1, const Vector &f2, const Vector &f3):pf0(f0),pf1(f1),pf2(f2),pf3(f3) {

}

Vector BoxPlane::getN()const{
    return Triangle(pf0,pf1,pf2).getN().normalize();
}

bool  BoxPlane::surfaceIntersectionCheck(const Ray& ray, Vector& crossPoint,Vector& weight)const{

    Triangle triangle1(pf0,pf1,pf2);
    if(triangle1.surfaceIntersectionCheck(ray,crossPoint,weight)){
        return true;
    }
    Triangle triangle2(pf0,pf2,pf3);
    if(triangle2.surfaceIntersectionCheck(ray,crossPoint,weight)){
        return true;
    }
    return false;
}
