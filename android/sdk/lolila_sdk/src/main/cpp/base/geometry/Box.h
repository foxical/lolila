//
// Created by tam on 2020/11/6.
//

#ifndef _BOX_H
#define _BOX_H

#ifndef __VECTOR_H__
#include "Vector.h"
#endif

#ifndef _BOXPLANE_H
#include "BoxPlane.h"
#endif

#ifndef __MATRIX_H__
#include "../math/Matrix.h"
#endif

class Ray;

class Box {
public:
    Box(float w,float h,float d);
    ~Box();
    float getWidth()const;
    float getHeight()const;
    float getDepth()const;
    bool  surfaceIntersectionCheck(const Ray& ray, Vector& crossPoint,Vector& weight)const;
    void translate(const Vector& t);
    void rotate(const Vector& axis,float angle);
    inline const Matrix& geCurTransformMat()const{
        return curTransformMat;
    }
private:
    Vector _p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7;
    BoxPlane _plane0,_plane1,_plane2,_plane3,_plane4,_plane5;
    Matrix curTransformMat;
};


#endif //_BOX_H
