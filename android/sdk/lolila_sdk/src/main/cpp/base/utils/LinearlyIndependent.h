//
// Created by tam on 2021/7/2.
// 把向量看作矩阵的每一列，如果矩阵是可逆的，则这些向量是线性无关的
//

#ifndef _LINEARLYINDEPENDENT_H
#define _LINEARLYINDEPENDENT_H

class Vector;
class LinearlyIndependent{
public:

    /**
     * 检查V1和V2是否线性无关
     * @param v1
     * @param v2
     * @return
     */
    static bool check2(const Vector& v1,const Vector& v2);

    /**
     * 检查V1、V2、V3是否线性无关
     * @param v1
     * @param v2
     * @param v3
     * @return
     */
    static bool check3(const Vector& v1,const Vector& v2,const Vector& v3);

private:
    LinearlyIndependent();
    ~LinearlyIndependent();
};

#endif //_LINEARLYINDEPENDENT_H
