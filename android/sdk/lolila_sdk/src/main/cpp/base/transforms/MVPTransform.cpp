//
// Created by Administrator on 2017/10/20.
//

#include <stdexcept>
#include <math.h>
#include "MVPTransform.h"
#include "../math/Matrix.h"
#include "../utils/FloatUtils.h"
#include "../geometry/Projections.h"
#include "../geometry/ViewFrustum.h"
#include "../geometry/Vector.h"
#include "../utils/AndroidLog.h"
#include "Translate.h"

static const float PI  = FloatUtils::PI;//3.14159265f

void MVPTransform::buildLookAtMatrix(
        const float& posX,    const float& posY,    const float& posZ,
        const float& lookAtX, const float& lookAtY, const float& lookAtZ,
        const Vector&   vUp,
        Matrix& M){

    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }


    // 构建方向向量(新Z轴)
    const Vector vPos(posX,posY,posZ);
    const Vector vTarget(lookAtX,lookAtY,lookAtZ);
    const Vector vDirect = Vector::minus(vPos,vTarget).normalize();


    // 上向量必须与方向向量垂直
    if( !FloatUtils::isEqual(Vector::dot(vDirect,vUp),0.0f) ){
        throw runtime_error("vector UP must vDirect");
    }

    // 右向量 =  UP  X 方向向量 （新X轴）
    const Vector vRight = Vector::cross(vUp,vDirect).normalize();

    // 新Y轴
    const Vector vU = Vector::cross(vDirect,vRight).normalize();


    // 以上叉乘注意顺序不要搞错，遵守右手法则，三个新轴的方向和OPENGL世界坐标系的方向完全相同



    Matrix M0(4,4);
    M0.set(0,0, vRight.x());   M0.set(0,1, vRight.y());   M0.set(0,2, vRight.z());   //M0.set(0,3, 0.0f);
    M0.set(1,0, vU.x());       M0.set(1,1, vU.y());       M0.set(1,2, vU.z());       //M0.set(1,3, 0.0f);
    M0.set(2,0, vDirect.x());  M0.set(2,1, vDirect.y());  M0.set(2,2, vDirect.z());  //M0.set(2,3, 0.0f);
    /*M0.set(3,0, 0.0f);         M0.set(3,1,0.0f)         M0.set(3,2, 0.0f);*/         M0.set(3,3, 1.0f);

    Matrix M1(4,4);
    Translate::buildTranslateMatrix(Vector(-posX,-posY,-posZ),M1);

    //!!! 这里先平移，在做变换，即先把坐标原点重合，
    // 这个和 P' = MP + T  即先旋转再平移，有本质区别
    // 千万不能用 [ M | T ]
    //            [ 0 | 1 ]
    M.set(Matrix::multiply(M0,M1));


    /*

    M.set(0,0, vRight.x());   M.set(0,1, vU.x());   M.set(0,2, vDirect.x());   M.set(0,3, -posX);
    M.set(1,0, vRight.y());   M.set(1,1, vU.y());   M.set(1,2, vDirect.y());   M.set(1,3, -posY);
    M.set(2,0, vRight.z());   M.set(2,1, vU.z());   M.set(2,2, vDirect.z());   M.set(2,3, -posZ);
    M.set(3,0, 0.0f);         M.set(3,1,0.0f);       M.set(3,2, 0.0f);          M.set(3,3, 1.0f);
    */
}

void MVPTransform::buildFrustumMatrix( const float& view_port_w, const float& view_port_h, const float& nearZ, const float& farZ, const float& fov, Matrix& mat4  ){
    const float aspect = view_port_w/view_port_h;  // 计算宽高比
    const float frustumH = tanf ( (fov/2)*PI/180.0f ) * nearZ;  // 根据焦距neerZ(近平面)以及垂直视场角获得高度
    const float frustumW = frustumH * aspect; // 反算出宽度
    Projections::buildPerspectiveProjectionMatrix( -frustumW, frustumH, frustumW, -frustumH, nearZ, farZ,mat4 );
}