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
    HomogeneousCoordinate(const float& x,const float& w);
    HomogeneousCoordinate(const float& x,const float& y,const float& w);
    HomogeneousCoordinate(const float& x,const float& y,const float& z,const float& w);
    HomogeneousCoordinate(const Vector&,const float& );
    HomogeneousCoordinate(const HomogeneousCoordinate&);
public:
    inline int dim()const{
        return _vector.dim()+1;
    }
    inline float x()const{
        return _vector.x();
    }
    inline float y()const{
        return _vector.y();
    }
    inline float z()const{
        return _vector.z();
    }
    inline float w()const{
        return _w;
    }
public:
    int dot(const HomogeneousCoordinate&)const;
public:
    static int dot(const HomogeneousCoordinate&,const HomogeneousCoordinate&);
private:
    HomogeneousCoordinate();
private:
    const Vector _vector;
    const float _w;
};

#endif //__HOMOGENEOUSCOORDINATE_H__
