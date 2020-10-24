//
// Created by tam on 2020/10/16.
//

#include "SymbleM.h"
#include "../shaders/SimpleVertexSet.h"

const GLfloat hStrider = 1.0f/4;
const GLfloat y=1.0f;

GLfloat SymbleM::getWidth()const{

    return 1.0;
}

GLfloat SymbleM::getHeight()const{
    return y;
}

void SymbleM::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){


    SimpleVertexSet vs(5);
    vs.setColor(r,g,b,a);
    GLfloat x=0.0f;

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
    glDrawArrays(GL_LINE_STRIP,0,_vao.getVSCount());
    _vao.unBind();
}