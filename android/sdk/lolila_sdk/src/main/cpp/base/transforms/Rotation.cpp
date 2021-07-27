//
// Created by Administrator on 2017/10/19.
//

#include <stdexcept>
#include <math.h>
#include "Rotation.h"

#include "../geometry/Vector.h"
#include "../math/Matrix.h"
#include "../utils/FloatUtils.h"

static const float PI  = FloatUtils::PI;//3.14159265f


#define GLM_FORCE_MESSAGES // Or defined when building (e.g. -DGLM_FORCE_SWIZZLE)
#include <glm/glm.hpp>
#include <glm/ext/vector_float3.hpp>
#include <glm/ext/matrix_float4x4.hpp> // mat4
#include <glm/ext/matrix_transform.hpp>
#include <glm/trigonometric.hpp> // radians
#include <glm/gtx/transform.hpp>

void Rotation::buildRotationMatrix(const Vector& axis, const float& degree, Matrix& M){
    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }

#if 0
    const float length = axis.length();// 求轴的长度
    if( FloatUtils::isEqual(length,0.0f)){
        throw runtime_error("axis length ==0!");
    }


    const float Ax = axis.x() / length;  // 规格化，使轴变为单位向量
    const float Ay = axis.y() / length;
    const float Az = axis.z() / length;
    const float s = sinf(degree*PI/180.0f);
    const float c = cosf(degree*PI/180.0f);
    const float i_c = FloatUtils::minus(1.0f,c);

    M.zero();
    M.set(0,0, c + i_c*Ax*Ax );  M.set(0,1, i_c*Ax*Ay-s*Az);      M.set(0,2,i_c*Ax*Az+s*Ay);      /*0*/
    M.set(1,0, i_c*Ax*Ay+s*Az);  M.set(1,1, c+i_c*Ay*Ay);         M.set(1,2,i_c*Ay*Az-s*Ax);      /*0*/
    M.set(2,0, i_c*Ax*Az-s*Ay);  M.set(2,1, i_c*Ay*Az+s*Ax);      M.set(2,2, c+i_c*Az*Az);        /*0*/
    /*0*/                        /*0*/                            /*0*/                           M.set(3,3,1.0f);

#endif

    // using glm
    glm::vec<3,float> vAxis(axis.x(),axis.y(),axis.z());
    glm::mat<4,4,float> outM(1.0f);

    glm::mat<4,4,float> result = glm::rotate(
            glm::radians(degree),
            //degree,
            vAxis
    );



    M.zero();
    M.set(0,0,result[0][0]);M.set(0,1,result[0][1]);M.set(0,2,result[0][2]);M.set(0,3,result[0][3]);
    M.set(1,0,result[1][0]);M.set(1,1,result[1][1]);M.set(1,2,result[1][2]);M.set(1,3,result[1][3]);
    M.set(2,0,result[2][0]);M.set(2,1,result[2][1]);M.set(2,2,result[2][2]);M.set(2,3,result[2][3]);
    M.set(3,0,result[3][0]);M.set(3,1,result[3][1]);M.set(3,2,result[3][2]);M.set(3,3,result[3][3]);
}

Vector Rotation::doTransform( const Vector& axis, const float& degree, const Vector& in ){

    Matrix M(4,4);
    buildRotationMatrix(axis,degree,M);
    Matrix P(4,1);
    P.set(0,0,in.x());P.set(1,0,in.y());P.set(2,0,in.z());P.set(3,0,1.0f);
    const Matrix PZ = Matrix::multiply(M,P);
    return Vector(PZ.get(0,0),PZ.get(1,0),PZ.get(2,0));
}