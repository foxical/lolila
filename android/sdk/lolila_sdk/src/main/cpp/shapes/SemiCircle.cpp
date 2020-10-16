//
// Created by tam on 2020/10/16.
//

#include "SemiCircle.h"
#include "../shaders/SimpleVertexSet.h"
#include "../shaders/VertexSetTransform.h"


void SemiCircle::load(GLfloat angleStrider,GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    SimpleVertexSet vs(VertexSetTransform::semiCircleCount(angleStrider));
    VertexSetTransform::setCirclePos(vs,angleStrider,radius);
    vs.setColor(r,g,b,a);
    _vao.load(vs);
}

void SemiCircle::draw()const{
    _vao.bind();
    glDrawArrays(GL_LINE_STRIP,0, _vao.getVSCount());
    _vao.unBind();
}
