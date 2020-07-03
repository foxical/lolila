//
// Created by Administrator on 2018/2/1.
//

#ifndef __SCALING_H__
#define __SCALING_H__

class Vector;
class Matrix;

class Scaling{
public:
    static void buildScalingMatrix(const Vector& S, Matrix& M);
private:
    Scaling();
    ~Scaling();
};


#endif //__SCALING_H__
