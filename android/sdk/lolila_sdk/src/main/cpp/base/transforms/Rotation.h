//
// Created by Administrator on 2017/10/19.
//

#ifndef __ROTATION_H__
#define __ROTATION_H__


class Vector;
class Matrix;

class Rotation {
public:
    static void buildRotationMatrix(const Vector& axis, const float& degree, Matrix& mat4);
private:
    Rotation();
    ~Rotation();
};


#endif //__ROTATION_H__
