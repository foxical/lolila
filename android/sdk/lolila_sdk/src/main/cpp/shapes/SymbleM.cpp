//
// Created by tam on 2020/10/16.
//

#include "SymbleM.h"
#include "../shaders/SimpleVertexSet.h"

void SymbleM::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){


    SimpleVertexSet vs(5);
    vs.setColor(r,g,b,a);
    GLfloat x=0.0f;
    const GLfloat hStrider = .5f*.5f/2.0f;
    const GLfloat y=0.5f*0.8f;
    vs.setPos(0,x,0,0);
    x+=hStrider;
    vs.setPos(1,x,y,0);
    x+=hStrider;
    vs.setPos(2,x,0,0);
    x+=hStrider;
    vs.setPos(3,x,y,0);
    x+=hStrider;
    vs.setPos(4,x,0,0);
    GLushort indices[5]={0,1,2,3,4};
    _vao.load(vs,indices);
}

void SymbleM::draw()const{
    _vao.bind();
    //glDrawElements(GL_LINE_STRIP,5,GL_UNSIGNED_SHORT,(const void*)NULL);
    glDrawArrays(GL_LINE_STRIP,0,5);
    _vao.unBind();
}