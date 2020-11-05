//
// Created by tam on 2020/11/5.
//

#include "SimpleTriangle.h"
#include "../shaders/SimpleVertexSet.h"

void SimpleTriangle::load(
        GLfloat x0, GLfloat y0, GLfloat z0,
        GLfloat x1, GLfloat y1, GLfloat z1,
        GLfloat x2, GLfloat y2, GLfloat z2,
        GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(3);
    vs.setColor(r,g,b,a);
    vs.setPos(0,x0,y0,z0);
    vs.setPos(1,x1,y1,z1);
    vs.setPos(2,x2,y2,z2);
    _vao.load(vs);
}

void SimpleTriangle::draw()const{
    _vao.bind();
    glDrawArrays(GL_TRIANGLE_STRIP,0,3);
    _vao.unBind();
}