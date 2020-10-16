//
// Created by tam on 2020/10/16.
//

#include "VertexSetTransform.h"
#include "SimpleVertexSet.h"
#include "../base/math/Matrix.h"
#include "../base/geometry/Vector.h"
#include "../base/transforms/Rotation.h"
#include "../base/utils/AndroidLog.h"
#include <stdexcept>

void VertexSetTransform::positionTransformByMat(SimpleVertexSet& vs, const Matrix& m){

    const int vsCount = vs.getRawVertexCount();
    for(int pos=0;pos<vsCount;++pos){
        GLfloat pc[3]={.0f,.0f,.0f};
        vs.getPos(pos,pc);
        Matrix v = Matrix::createHomogeneousCoordinates(pc[0],pc[1],pc[2]);
        Matrix nv = Matrix::multiply(m,v);
        pc[0] = nv.get(0,0);
        pc[1] = nv.get(1,0);
        pc[2] = nv.get(2,0);
        vs.setPos(pos,pc);
    }
}

int VertexSetTransform::semiCircleCount(float angleStrider){
    return (int)(180.0f/angleStrider) + 1;
}

void VertexSetTransform::setCirclePos(SimpleVertexSet& vs,float angleStrider, GLfloat radius){
    const int vsCount = vs.getRawVertexCount();

    const Vector axis(0,0,-1); //  rotate around with z axis

    Vector base(radius,0,0);
    vs.setPos(0,radius,0,0);

    for(int c = 1; c<=(vsCount-1);++c){
        base = Rotation::doTransform(axis,angleStrider*-1.0f,base);
        //LOGD("c:%d,x:%f, y:%f, z:%f",c,base.x(),base.y(),base.z());
        vs.setPos(c,base.x(),base.y(),base.z());
    }
}
