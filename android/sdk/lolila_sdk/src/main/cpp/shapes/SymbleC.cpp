//
// Created by tam on 2020/10/17.
//

#include "SymbleC.h"
#include "../shaders/SimpleVertexSet.h"
#include "../shaders/VertexSetTransform.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/transforms/Rotation.h"
#include "../base/geometry/Vector.h"

const GLfloat radius = .5f;
const GLfloat widthScale = 1.0f;

GLfloat SymbleC::getWidth()const{
    return 2*radius;
}
GLfloat SymbleC::getHeight()const{
    return 2*radius;
}

void SymbleC::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(VertexSetTransform::semiCircleCount(1.0f));
    vs.setColor(r,g,b,a);

    VertexSetTransform::setCirclePos(vs,1.0f,radius);

    Matrix rm(4,4);
    Rotation::buildRotationMatrix(Vector(0,0,-1),-90,rm);
    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(radius,radius,0),t); // 移到逻辑坐标右上
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(widthScale,1.0,1.0),s);// X方向缩小到原来的widthScale
    VertexSetTransform::positionTransformByMat(vs,Matrix::multiply(s,t,rm));
    _vao.load(vs);
}

void SymbleC::draw() const {
    _vao.bind();
    glDrawArrays(GL_LINE_STRIP,0,_vao.getVSCount());
    _vao.unBind();
}
