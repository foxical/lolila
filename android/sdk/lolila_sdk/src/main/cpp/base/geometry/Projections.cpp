//
// Created by TanLinghui on 2017/6/5.
//

#include "Projections.h"
#include <stdexcept>
#include "Vector.h"
#include "../math/Matrix.h"
#include "../utils/LogQueue.h"
#include "../utils/AndroidLog.h"

Vector Projections::perspectiveProjection(
        const float& l,const float& t,const float& r,const float& b,
        const float& n,const float& f,
        const Vector& p){

    Matrix M(4,4);
    buildPerspectiveProjectionMatrix(l,t,r,b,n,f,M);


    //LogQueue::push("M is %s",M.c_str());

    Matrix P(4,1);
    P.set(0,0,p.x());P.set(1,0,p.y());P.set(2,0,p.z());P.set(3,0,1.0f);

    const Matrix PZ = Matrix::multiply(M,P);
    const float wc = PZ.get(3,0);
    //LogQueue::push("pz' is %g,wc is %g\n",PZ.get(2,0),wc);
    return Vector(PZ.get(0,0)/wc,PZ.get(1,0)/wc,PZ.get(2,0)/wc);
}

void  Projections::buildPerspectiveProjectionMatrix(
        const float& l,const float& t,const float& r,const float& b,
        const float& n,const float& f,
        Matrix& M){
    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }

    LOGD("buildPerspectiveProjectionMatrix, l:%f,r:%f\n",l,r);
    LOGD("buildPerspectiveProjectionMatrix, t:%f,b:%f\n",t,b);
    LOGD("buildPerspectiveProjectionMatrix, n:%f,f:%f\n",n,f);

    const float       deltaX = r - l;
    const float       deltaY = t - b;
    const float       deltaZ = f - n;
    if ( ( n <= 0.0f ) || ( f <= 0.0f ) ||
         ( deltaX <= 0.0f ) || ( deltaY <= 0.0f ) || ( deltaZ <= 0.0f ) ){
        throw runtime_error("delta is invalid!");
    }

    M.set(0,0,2.0f*n/deltaX); M.set(0,1,0);/*0*/         M.set(0,2,(r+l)/deltaX);         M.set(0,3,0);/*0*/
    M.set(1,0,0);/*0*/        M.set(1,1,2.0f*n/deltaY);  M.set(1,2,(t+b)/deltaY);         M.set(1,3,0);/*0*/
    M.set(2,0,0);/*0*/        M.set(2,1,0);/*0*/         M.set(2,2,-1.0f*(f+n)/deltaZ);   M.set(2,3,-2.0f*n*f/deltaZ);
    M.set(3,0,0);/*0*/        M.set(3,1,0);/*0*/         M.set(3,2,-1.0f);                M.set(3,3,0);/*0*/
}

void  Projections::buildOrthoProjectionMatrix(
        const float& l,const float& t,const float& r,const float& b,
        const float& n,const float& f,
        Matrix& M){

    if( !M.isSquare() || M.col()!=4){
        throw runtime_error("Matrix must a 4x4 square!");
    }

    const float       deltaX = r - l;
    const float       deltaY = t - b;
    const float       deltaZ = f - n;
    if ( ( n <= 0.0f ) || ( f <= 0.0f ) ||
         ( deltaX <= 0.0f ) || ( deltaY <= 0.0f ) || ( deltaZ <= 0.0f ) ){
        throw runtime_error("delta is invalid!");
    }

    M.set(0,0,2.0f/deltaX);    M.set(0,1,0);/*0*/         M.set(0,2,0);/*0*/               M.set(0,3,-1.0f*(r+l)/deltaX);
    M.set(1,0,0);/*0*/        M.set(1,1,2.0f/deltaY);     M.set(1,2,0);/*0*/               M.set(1,3,-1.0f*(t+b)/deltaY);
    M.set(2,0,0);/*0*/        M.set(2,1,0);/*0*/         M.set(2,2,-2.0f/deltaZ);         M.set(2,3,-1.0f*(f+n)/deltaZ);
    M.set(3,0,0);/*0*/        M.set(3,1,0);/*0*/         M.set(3,2,0);/*0*/               M.set(3,3,1.0f);

}

