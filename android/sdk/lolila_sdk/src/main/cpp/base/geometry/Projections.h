//
// Created by TanLingHui on 2017/6/5.
//

#ifndef __PROJECTIONS_H__
#define __PROJECTIONS_H__

class Vector;

class Projections{
public:

    /**
     *
     */
    static Vector perspectiveProjection(
            const double& l,const double& t,const double& r,const double& b,
            const double& n,const double& f,
            const Vector& P);

    static Vector perspectiveProjection_v2(
            const double& l,const double& t,const double& r,const double& b,
            const double& n,const double& f,
            const Vector& P);

private:
    Projections();
    ~Projections();
};


#endif //__PROJECTIONS_H__
