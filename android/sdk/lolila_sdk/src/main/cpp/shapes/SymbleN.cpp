//
// Created by tam on 2020/10/16.
//

#include "SymbleN.h"
#include "../shaders/SimpleVertexSet.h"

void SymbleN::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){


    SimpleVertexSet vs(4);
    vs.setColor(r,g,b,a);
    GLfloat x=0.0f;
    const GLfloat hStrider = .5f*.5f/2.0f;
    const GLfloat y=0.5f*0.8f;
    vs.setPos(0,x,0,0);
    vs.setPos(1,x,y,0);
    x+=hStrider;
    vs.setPos(2,x,0,0);
    vs.setPos(3,x,y,0);
    _vao.load(vs);
}

void SymbleN::draw()const{
    _vao.bind();
    //glDrawElements(GL_LINE_STRIP,5,GL_UNSIGNED_SHORT,(const void*)NULL);
    glDrawArrays(GL_LINE_STRIP,0,4);
    _vao.unBind();
}
