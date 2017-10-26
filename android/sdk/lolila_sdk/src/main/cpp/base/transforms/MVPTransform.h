//
// Created by Administrator on 2017/10/20.
//

#ifndef __MVPTRANSFORM_H__
#define __MVPTRANSFORM_H__


class Matrix;

class MVPTransform {
public:
    static void buildLookAtMatrix(
        float posX,    float posY,    float posZ,
        float lookAtX, float lookAtY, float lookAtZ,
        float upX,     float upY,     float upZ,
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

private:
    MVPTransform();
    ~MVPTransform();
};


#endif //DEMO_MVPTRANSFORM_H
