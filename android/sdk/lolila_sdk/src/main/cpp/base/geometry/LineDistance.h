//
// Created by Administrator on 2017/3/31.
//

#ifndef __LINEDISTANCE_H__
#define __LINEDISTANCE_H__


#include "Vector.h"

class Line;
class Ray;
class Vector;

class LineDistance{
public:



    static float calc(const Line& l1, const Line& l2);
    static float calc(const Ray& l1,const Ray& l2);
    static float calc(const Line& l1, const Ray& l2);
    static float calc(const Ray& l1,const Line& l2);


    static bool isParallel(const Vector&,const Vector&);

    static bool pointLiesInRay(const Vector&, const Ray&);
    static bool pointLiesInLine(const Vector&, const Line&);

private:
    LineDistance();
    ~LineDistance();
};

#endif //__LINEDISTANCE_H__
