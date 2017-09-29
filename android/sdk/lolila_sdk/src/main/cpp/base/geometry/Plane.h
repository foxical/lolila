//
// Created by Administrator on 2017/4/6.
//

#ifndef __PLANE_H__
#define __PLANE_H__

#ifndef __VECTOR_H__
#include "Vector.h"
#endif

class Plane{
public:
    Plane(const Vector& N, const Vector& P);
    ~Plane();
public:
    bool pointLiesInPlane(const Vector&)const;
    double distanceFromOri()const;
    inline const Vector& N()const{
        return _n;
    }
    inline const Vector& P()const{
        return _p;
    }
    inline double D()const{
        return (-1.0)*Vector::dot(_n,_p);
    }
public:
    static bool  pointLiesInPlane(const Plane &, const Vector &);

private:
    Plane();
private:
    const Vector _n;
    const Vector _p;
};

#endif //__PLANE_H__
