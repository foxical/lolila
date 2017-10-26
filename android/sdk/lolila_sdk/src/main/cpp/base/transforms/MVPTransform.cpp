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
#include "../utils/AndroidLog.h"

static const float PI  = FloatUtils::PI;//3.14159265f

void MVPTransform::buildLookAtMatrix(
        float posX,    float posY,    float posZ,
        float lookAtX, float lookAtY, float lookAtZ,
        float upX,     float upY,     float upZ,
        Matrix& M){

    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }




    float axisX[3], axisY[3], axisZ[3];
    float length;

    // axisZ = lookAt - pos
    axisZ[0] = lookAtX - posX;
    axisZ[1] = lookAtY - posY;
    axisZ[2] = lookAtZ - posZ;

    // normalize axisZ
    length = sqrtf ( axisZ[0] * axisZ[0] + axisZ[1] * axisZ[1] + axisZ[2] * axisZ[2] );

    if ( length != 0.0f )
    {
        axisZ[0] /= length;
        axisZ[1] /= length;
        axisZ[2] /= length;
    }

    // axisX = up X axisZ
    axisX[0] = upY * axisZ[2] - upZ * axisZ[1];
    axisX[1] = upZ * axisZ[0] - upX * axisZ[2];
    axisX[2] = upX * axisZ[1] - upY * axisZ[0];

    // normalize axisX
    length = sqrtf ( axisX[0] * axisX[0] + axisX[1] * axisX[1] + axisX[2] * axisX[2] );

    if ( length != 0.0f )
    {
        axisX[0] /= length;
        axisX[1] /= length;
        axisX[2] /= length;
    }

    // axisY = axisZ x axisX
    axisY[0] = axisZ[1] * axisX[2] - axisZ[2] * axisX[1];
    axisY[1] = axisZ[2] * axisX[0] - axisZ[0] * axisX[2];
    axisY[2] = axisZ[0] * axisX[1] - axisZ[1] * axisX[0];

    // normalize axisY
    length = sqrtf ( axisY[0] * axisY[0] + axisY[1] * axisY[1] + axisY[2] * axisY[2] );

    if ( length != 0.0f )
    {
        axisY[0] /= length;
        axisY[1] /= length;
        axisY[2] /= length;
    }


    /*
     * result->m[0][0] = -axisX[0];
   result->m[0][1] =  axisY[0];
   result->m[0][2] = -axisZ[0];

   result->m[1][0] = -axisX[1];
   result->m[1][1] =  axisY[1];
   result->m[1][2] = -axisZ[1];

   result->m[2][0] = -axisX[2];
   result->m[2][1] =  axisY[2];
   result->m[2][2] = -axisZ[2];

   // translate (-posX, -posY, -posZ)
   result->m[3][0] =  axisX[0] * posX + axisX[1] * posY + axisX[2] * posZ;
   result->m[3][1] = -axisY[0] * posX - axisY[1] * posY - axisY[2] * posZ;
   result->m[3][2] =  axisZ[0] * posX + axisZ[1] * posY + axisZ[2] * posZ;
   result->m[3][3] = 1.0f;
     */

    M.set(0,0, -axisX[0]);
    M.set(0,1, -axisX[1]);
    M.set(0,2, -axisX[2]);
    M.set(0,3, axisX[0] * posX + axisX[1] * posY + axisX[2] * posZ);

    M.set(1,0, axisY[0]);
    M.set(1,1, axisY[1]);
    M.set(1,2, axisY[2]);
    M.set(1,3, -axisY[0] * posX - axisY[1] * posY - axisY[2] * posZ);

    M.set(2,0, -axisZ[0]);
    M.set(2,1, -axisZ[1]);
    M.set(2,2, -axisZ[2]);
    M.set(2,3, axisZ[0] * posX + axisZ[1] * posY + axisZ[2] * posZ);

    // translate (-posX, -posY, -posZ)

    M.set(3,0,0.0f);
    M.set(3,1,0.0f);
    M.set(3,2,0.0f);
    M.set(3,3,1.0f);

}

void MVPTransform::buildFrustumMatrix( const float& view_port_w, const float& view_port_h, const float& nearZ, const float& farZ, const float& fov, Matrix& mat4  ){
    const float aspect = view_port_w/view_port_h;  // 计算宽高比
    const float frustumH = tanf ( fov / 360.0f * PI ) * nearZ;  // 根据焦距neerZ(近平面)以及垂直视场角获得高度
    const float frustumW = frustumH * aspect; // 反算出宽度
    Projections::buildPerspectiveProjectionMatrix( -frustumW, frustumH, frustumW, -frustumH, nearZ, farZ,mat4 );
}