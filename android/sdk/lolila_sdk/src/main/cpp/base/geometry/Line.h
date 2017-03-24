//
// Created by Administrator on 2017/3/24.
//

#ifndef __LINE_H__
#define __LINE_H__

#ifndef __VECTOR_H__
#include "Vector.h"
#endif//__VECTOR_H__

class Line{
public:
    Line(const Vector& p1,const Vector& p2);
    ~Line();
public:
    Vector pointAt(const float& t)const;
    float distance(const Vector& Q)const;
private:
    Line();
private:
    const Vector _point1;
    const Vector _point2;
};

#endif //__LINE_H__
