//
// Created by Administrator on 2017/4/6.
//

#ifndef __PLANEINTERSECTION_H__
#define __PLANEINTERSECTION_H__

class Plane;
class Ray;
class Line;
class Vector;

class PlaneIntersection{
public:
    static bool isParallel(const Plane&, const Ray& );
    static bool isParallel(const Plane&, const Line& );
    static bool isParallel(const Plane&, const Plane& );

    static Vector  intersects(const Plane&, const Ray& );

    static float  intersects_f(const Plane&, const Ray& );

    static Vector  intersects(const Plane&, const Line& );

    static Ray intersects(const Plane& plane1,const Plane& plane2);
    static Ray intersects_v2(const Plane& plane1,const Plane& plane2);

    static Vector intersects(const Plane& plane1,const Plane& plane2,const Plane& plane3);

private:
    PlaneIntersection();
    ~PlaneIntersection();
};


#endif //__PLANEINTERSECTION_H__
