//
// Created by tam on 2020/11/2.
//

#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#ifndef __VECTOR_H__
#include "Vector.h"
#endif

class Ray;

class Triangle {
public:
    Triangle();
    Triangle(const Vector& p0,const Vector& p1,const Vector& p2);
    Triangle(float px0, float py0, float pz0,
             float px1, float py1, float pz1,
             float px2, float py2, float pz2);
    ~Triangle();

    void setPoint(const Vector& p0,const Vector& p1,const Vector& p2);

    Vector getN()const;

    bool  surfaceIntersectionCheck(const Ray& ray, Vector& crossPoint,Vector& weight)const;

private:
    Vector _p0;
    Vector _p1;
    Vector _p2;
};


#endif //_TRIANGLE_H
