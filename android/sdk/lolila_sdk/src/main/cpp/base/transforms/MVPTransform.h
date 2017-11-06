//
// Created by Administrator on 2017/10/20.
//

#ifndef __MVPTRANSFORM_H__
#define __MVPTRANSFORM_H__

#include "../math/Matrix.h"
#include "../geometry/Vector.h"

class Vector;
class Matrix;

class MVPTransform {
public:

    /**
     * pos
     * 摄像机位置
     * lookAt
     * 观察点
     * up
     * 上向量
     */
    static void buildLookAtMatrix(
        const float& posX,    const float& posY,    const float& posZ,
        const float& lookAtX, const float& lookAtY, const float& lookAtZ,
        const Vector&   up,
        Matrix& M
    );


    /**
     * @view_port_w
     * 视口宽度
     * @view_port_h
     * 视口高度
     * @nearZ
     * 近平面距离（焦距）必须为正数
     * @farZ
     * 远平面距离，必须为正数
     * @fov
     * 垂直视场角
     */
    static void buildFrustumMatrix( const float& view_port_w, const float& view_port_h, const float& nearZ, const float& farZ, const float& fov, Matrix& mat4 );


    static Matrix vec2mat(const Vector& in);

private:
    MVPTransform();
    ~MVPTransform();
};


#endif //DEMO_MVPTRANSFORM_H
