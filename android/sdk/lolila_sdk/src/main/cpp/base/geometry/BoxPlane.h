//
// Created by tam on 2020/11/6.
//

#ifndef _BOXPLANE_H
#define _BOXPLANE_H

#ifndef __VECTOR_H__
#include "Vector.h"
#endif

class Ray;

struct BoxPlane{
    const Vector& pf0;
    const Vector& pf1;
    const Vector& pf2;
    const Vector& pf3;

    BoxPlane(const Vector&,const Vector&,const Vector&,const Vector&);
    Vector getN()const;
    bool  surfaceIntersectionCheck(const Ray& ray, Vector& crossPoint,Vector& weight)const;
};

#endif //_BOXPLANE_H
