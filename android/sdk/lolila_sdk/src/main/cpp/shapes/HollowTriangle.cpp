//
// Created by tam on 2020/10/1.
//

#include "HollowTriangle.h"
#include "../shaders/SimpleVertexSet.h"


void HollowTriangle::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(3);
    vs.setColor(r,g,b,a);
    vs.setPos(0,0,0,0);
    vs.setPos(1,1,0,0);
    vs.setPos(2,1,1,0);
    GLushort indices[3]={0,1,2};
    _vao.load(vs,indices);
}

void HollowTriangle::draw()const{
    _vao.bind();
    glDrawElements(GL_LINE_LOOP,3,GL_UNSIGNED_SHORT,(const void*)NULL);
    _vao.unBind();
}