//
// Created by tam on 2020/10/16.
//

#include "SymbleN.h"
#include "../shaders/SimpleVertexSet.h"

const GLfloat hStrider = 1.0f;
const GLfloat y=1.0f;
GLfloat SymbleN::getWidth()const{
    return 1.0f;
}

GLfloat SymbleN::getHeight()const{
    return y;
}

void SymbleN::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){


    SimpleVertexSet vs(4);
    vs.setColor(r,g,b,a);
    GLfloat x=0.0f;

    vs.setPos(0,x,0,0);
    vs.setPos(1,x,y,0);
    x+=hStrider;
    vs.setPos(2,x,0,0);
    vs.setPos(3,x,y,0);
    _vao.load(vs);
}

void SymbleN::draw()const{
    _vao.bind();
    glDrawArrays(GL_LINE_STRIP,0,_vao.getVSCount());
    _vao.unBind();
}
