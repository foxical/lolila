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
    //LOGD("vDirect:%s",vDirect.c_str());

    // 上向量必须与方向向量垂直
    if( !FloatUtils::isEqual(Vector::dot(vDirect,vUp),0.0f) ){
        throw runtime_error("vector UP must vDirect");
    }

    // 右向量 =  UP  X 方向向量 （新X轴）
    const Vector vRight = Vector::cross(vUp,vDirect).normalize();
    //LOGD("vRight:%s",vRight.c_str());

    // 新Y轴
    const Vector vU = Vector::cross(vDirect,vRight).normalize();
    //LOGD("vU:%s",vU.c_str());


    // 以上叉乘注意顺序不要搞错，遵守右手法则，三个新轴的方向和OPENGL世界坐标系的方向完全相同
    // 三个新轴向量都必须是单位向量，即三个新轴是规范正交基
    /// 因为轴的长度是1，因此旋转矩阵可以简化为以下形式，消去了角度的因素，即和旋转角度无关

    Matrix M0(4,4);
    M0.set(0,0, vRight.x());   M0.set(0,1, vRight.y());   M0.set(0,2, vRight.z());   //M0.set(0,3, 0.0f);
    M0.set(1,0, vU.x());       M0.set(1,1, vU.y());       M0.set(1,2, vU.z());       //M0.set(1,3, 0.0f);
    M0.set(2,0, vDirect.x());  M0.set(2,1, vDirect.y());  M0.set(2,2, vDirect.z());  //M0.set(2,3, 0.0f);
    /*M0.set(3,0, 0.0f);         M0.set(3,1,0.0f)         M0.set(3,2, 0.0f);*/         M0.set(3,3, 1.0f);
    //LOGD("MO:%s",M0.c_str());


    Matrix M1(4,4);
    Translate::buildTranslateMatrix(Vector(-posX,-posY,-posZ),M1);

    //!!! 这里先平移，即先把坐标原点重合，再做变换
    M.set(Matrix::multiply(M0,M1));


    ///// !!!
    // 另外一种方法：根据基变换原理, 完全按照课本的通用线性变换公式  M的逆矩阵 * P'
    // Test OK

    /*
    Matrix M2(4,4);
    M2.set(0,0, vRight.x());   M2.set(0,1, vU.x());   M2.set(0,2, vDirect.x());
    M2.set(1,0, vRight.y());   M2.set(1,1, vU.y());   M2.set(1,2, vDirect.y());
    M2.set(2,0, vRight.z());   M2.set(2,1, vU.z());   M2.set(2,2, vDirect.z());
    M2.set(3,0, 0.0f);         M2.set(3,1,0.0f);      M2.set(3,2, 0.0f);          M2.set(3,3, 1.0f);
    LOGD("M2-1:%s",M2.invert().c_str());

    M.set(Matrix::multiply(M2.invert(),M1));
    */

    /// 经过实际测试
    /// M2的逆矩阵 = M0
    // 所以用第一种方法，计算速度会快一点，因为不用求逆矩阵


    // 以上的两种方法实际是一种简化，
    // 根据课本的理论，应该是先把原坐标变为新坐标  P‘ = M ×P + T
    // 然后 再进行 P = M逆 x ( P'-T)，把在摄像机坐标系中的坐标变回去
    // 渲染的时候，是按照原坐标的

    // 摄像机变换的实质是： 先把原坐标的原点移动到摄像机位置，求得点在原坐标系移动后的新位置，然后把这个新位置看成是旧坐标系的（旧）坐标，
    //  再通过基变换变为摄像机的新坐标（M的逆），直接把新坐标看成是旧坐标的这个点的新坐标，因为原点是重合的
    //  基变换（坐标旋转）是使用 M的逆
    //  向量旋转是使用 也是M的逆，两者是等价的

}





void MVPTransform::buildFrustumMatrix( const float& view_port_w, const float& view_port_h, const float& nearZ, const float& farZ, const float& fov, Matrix& mat4  ){
    const float aspect = view_port_w/view_port_h;  // 计算宽高比
    const float frustumH = tanf ( FloatUtils::radians(fov/2) ) * nearZ;  // 根据焦距neerZ(近平面)以及垂直视场角获得高度
    const float frustumW = frustumH * aspect; // 反算出宽度
    Projections::buildPerspectiveProjectionMatrix( -frustumW, frustumH, frustumW, -frustumH, nearZ, farZ,mat4 );
}

void MVPTransform::buildOrthoMatrix( const float& view_port_w, const float& view_port_h, const float& nearZ, const float& farZ, const float& fov, Matrix& mat4  ){
    const float aspect = view_port_w/view_port_h;  // 计算宽高比
    const float frustumH = tanf ( FloatUtils::radians(fov/2) ) * nearZ;  // 根据焦距neerZ(近平面)以及垂直视场角获得高度
    const float frustumW = frustumH * aspect; // 反算出宽度
    //LOGD("w:%f,h:%f",frustumW,frustumH);
    Projections::buildOrthoProjectionMatrix( -frustumW, frustumH, frustumW, -frustumH, nearZ, farZ,mat4 );
}

Matrix MVPTransform:: vec2mat(const Vector& in){
    Matrix P(4,1);
    P.set(0,0,in.x());P.set(1,0,in.y());P.set(2,0,in.z());P.set(3,0,1.0f);
    return P;
}