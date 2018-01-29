//
// Created by TanLingHui on 2017/6/5.
//

#ifndef __PROJECTIONS_H__
#define __PROJECTIONS_H__

class Vector;
class Matrix;

class Projections{
public:

    /**
     * 执行透视变换（该函数内部会自动执行透视除法）
     */
    static Vector perspectiveProjection(
            const float& l,const float& t,const float& r,const float& b,
            const float& n,const float& f,
            const Vector& P);

    /**
     * 构造透视投影矩阵
     */
    static void  buildPerspectiveProjectionMatrix(
            const float& l,const float& t,const float& r,const float& b,
            const float& n,const float& f,
            Matrix& mat4);

    /**
     * 构造正视投影矩阵
     */
    static void  buildOrthoProjectionMatrix(
            const float& l,const float& t,const float& r,const float& b,
            const float& n,const float& f,
            Matrix& mat4);

    /*
    static Vector perspectiveProjection_v2(
            const double& l,const double& t,const double& r,const double& b,
            const double& n,const double& f,
            const Vector& P);
    */

private:
    Projections();
    ~Projections();
};


#endif //__PROJECTIONS_H__
