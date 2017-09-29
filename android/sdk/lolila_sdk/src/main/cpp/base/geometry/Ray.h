//
// Created by Administrator on 2017/3/24.
//

#ifndef __RAY_H__
#define __RAY_H__

#ifndef __VECTOR_H__
#include "Vector.h"
#endif//__VECTOR_H__

class Ray{
public:
    Ray(const Vector& S,const Vector& V);
    Ray(const Ray&);
    ~Ray();
public:
    Vector pointAt(const double& t)const;
    double distance(const Vector& Q)const;
    const Vector& endPoint()const;
    const Vector& direction()const;
    bool pointLiesInRay(const Vector& Q)const;


private:
    Ray();
private:
    const Vector _endpoint;
    const Vector _direction;
};

#endif //__RAY_H__
