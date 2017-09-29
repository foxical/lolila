//
// Created by Administrator on 2017/4/18.
//

#ifndef __HOMOGENEOUSCOORDINATE_H__
#define __HOMOGENEOUSCOORDINATE_H__

#ifndef __VECTOR_H__
#include "../geometry/Vector.h"
#endif//__VECTOR_H__

class HomogeneousCoordinate{
public:
    HomogeneousCoordinate(const double& x,const double& w);
    HomogeneousCoordinate(const double& x,const double& y,const double& w);
    HomogeneousCoordinate(const double& x,const double& y,const double& z,const double& w);
    HomogeneousCoordinate(const Vector&,const double& w);
    HomogeneousCoordinate(const HomogeneousCoordinate&);
public:
    inline int dim()const{
        return _vector.dim()+1;
    }
    inline double x()const{
        return _vector.x();
    }
    inline double y()const{
        return _vector.y();
    }
    inline double z()const{
        return _vector.z();
    }
    inline double w()const{
        return _w;
    }
public:
    double dot(const HomogeneousCoordinate&)const;
public:
    static double dot(const HomogeneousCoordinate&,const HomogeneousCoordinate&);
private:
    HomogeneousCoordinate();
private:
    const Vector _vector;
    const double _w;
};

#endif //__HOMOGENEOUSCOORDINATE_H__
