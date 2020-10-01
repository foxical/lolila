//
// Created by tam on 2020/10/1.
//

#include "SimplePlane.h"
#include "../shaders/SimpleVertexSet.h"



void SimplePlane::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(4);
    vs.setColor(r,g,b,a);
    vs.setPos(0,0,0,0);
    vs.setPos(1,1,0,0);
    vs.setPos(2,0,0,-1);
    vs.setPos(3,1,0,-1);
    GLushort indices[4]={0,1,2,3};
    _vao.load(vs,indices);
}

void SimplePlane::draw()const{
    _vao.bind();
    glDrawElements(GL_TRIANGLE_STRIP,4,GL_UNSIGNED_SHORT,(const void*)NULL);
    _vao.unBind();
}