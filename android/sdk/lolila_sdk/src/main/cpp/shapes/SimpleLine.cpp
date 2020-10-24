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

void SimpleLine::load(GLfloat x0,GLfloat y0,GLfloat z0,
          GLfloat x1,GLfloat y1,GLfloat z1,
          GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    SimpleVertexSet vs(2);
    vs.setColor(r,g,b,a);
    vs.setPos(0,x0,y0,z0);
    vs.setPos(1,x1,y1,z1);
    _vao.load(vs);
}

void SimpleLine::draw()const{
    _vao.bind();
    glDrawArrays(GL_LINES,0,2);
    _vao.unBind();
}
