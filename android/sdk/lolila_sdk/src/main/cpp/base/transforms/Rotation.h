//
// Created by Administrator on 2017/10/19.
//

#ifndef __ROTATION_H__
#define __ROTATION_H__


#include "../geometry/Vector.h"

class Vector;
class Matrix;

class Rotation {
public:
    static void buildRotationMatrix(const Vector& axis, const float& degree, Matrix& mat4);

    static Vector doTransform( const Vector& axis, const float& degree, const Vector& in );

private:
    Rotation();
    ~Rotation();
};


#endif //__ROTATION_H__
