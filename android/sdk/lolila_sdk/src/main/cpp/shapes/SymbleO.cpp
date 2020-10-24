//
// Created by tam on 2020/10/16.
//

#include "SymbleO.h"
#include "../shaders/SimpleVertexSet.h"
#include "../shaders/VertexSetTransform.h"
#include "../base/math/Matrix.h"
#include "../base/transforms/Translate.h"
#include "../base/transforms/Scaling.h"
#include "../base/geometry/Vector.h"

const GLfloat radius = .5f;
const GLfloat widthScale = 1.0f;

GLfloat SymbleO::getWidth()const{
    return 2*radius;
}
GLfloat SymbleO::getHeight()const{
    return 2*radius;
}

void SymbleO::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(VertexSetTransform::circleCount(1.0f));
    vs.setColor(r,g,b,a);

    VertexSetTransform::setCirclePos(vs,1.0f,radius);

    Matrix t(4,4);
    Translate::buildTranslateMatrix(Vector(radius,radius,0),t); // 移到逻辑坐标右上
    Matrix s(4,4);
    Scaling::buildScalingMatrix(Vector(widthScale,1.0,1.0),s);// X方向缩小到原来的widthScale
    VertexSetTransform::positionTransformByMat(vs,Matrix::multiply(s,t));
    _vao.load(vs);
}

void SymbleO::draw() const {
    _vao.bind();
    glDrawArrays(GL_LINE_STRIP,0,_vao.getVSCount());
    _vao.unBind();
}
