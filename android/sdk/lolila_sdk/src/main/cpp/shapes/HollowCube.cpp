//
// Created by tam on 2020/10/1.
//

#include "HollowCube.h"
#include "../shaders/SimpleVertexSet.h"


void HollowCube::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    SimpleVertexSet vs(8);
    vs.setColor(r,g,b,a);
    vs.setPos(0,0,0,0);
    vs.setPos(1,1,0,0);
    vs.setPos(2,1,1,0);
    vs.setPos(3,0,1,0);
    vs.setPos(4,1,1,-1);
    vs.setPos(5,0,1,-1);
    vs.setPos(6,1,0,-1);
    vs.setPos(7,0,0,-1);
    {
        GLushort indices[4]={
                0,1,2,3,
        };
        _vao1.load(vs,indices);
    }
    {
        GLushort indices[4]={
                7,6,4,5,
        };
        _vao2.load(vs,indices);
    }
    {
        GLushort indices[4]={
                1,6,4,2,
        };
        _vao3.load(vs,indices);
    }
    {
        GLushort indices[4]={
                0,7,5,3,
        };
        _vao4.load(vs,indices);
    }
}

void HollowCube::draw()const{
    _vao1.bind();
    glDrawElements(GL_LINE_LOOP,4,GL_UNSIGNED_SHORT,(const void*)NULL);
    _vao1.unBind();

    _vao2.bind();
    glDrawElements(GL_LINE_LOOP,4,GL_UNSIGNED_SHORT,(const void*)NULL);
    _vao2.unBind();

    _vao3.bind();
    glDrawElements(GL_LINE_LOOP,4,GL_UNSIGNED_SHORT,(const void*)NULL);
    _vao3.unBind();

    _vao4.bind();
    glDrawElements(GL_LINE_LOOP,4,GL_UNSIGNED_SHORT,(const void*)NULL);
    _vao4.unBind();
}