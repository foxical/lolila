//
// Created by tam on 2020/9/29.
//

#include "SimpleLine.h"
#include "../shaders/SimpleVertexSet.h"

void SimpleLine::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(2);
    vs.setColor(r,g,b,a);
    vs.setPos(0,0,0,0);
    vs.setPos(1,1,0,0);
    _vao.load(vs);
}

void SimpleLine::draw()const{
    _vao.bind();
    glDrawArrays(GL_LINES,0,2);
    _vao.unBind();
}
