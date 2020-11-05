//
// Created by tam on 2020/11/5.
//

#include "Simple3DCoordinate.h"
#include "../shaders/SimpleVertexSet.h"

void Simple3DCoordinate::load(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    {
        SimpleVertexSet vs(2);
        vs.setColor(r, g, b, a);
        vs.setPos(0,0,0,0);
        vs.setPos(1,1,0,0);
        _vao1.load(vs);
    }

    {
        SimpleVertexSet vs(2);
        vs.setColor(r, g, b, a);
        vs.setPos(0,0,0,0);
        vs.setPos(1,0,1,0);
        _vao2.load(vs);
    }

    {
        SimpleVertexSet vs(2);
        vs.setColor(r, g, b, a);
        vs.setPos(0,0,0,0);
        vs.setPos(1,0,0,-1);
        _vao3.load(vs);
    }
}

void Simple3DCoordinate::draw()const{

    _vao1.bind();
    glDrawArrays(GL_LINES,0,2);
    _vao1.unBind();

    _vao2.bind();
    glDrawArrays(GL_LINES,0,2);
    _vao2.unBind();

    _vao3.bind();
    glDrawArrays(GL_LINES,0,2);
    _vao3.unBind();
}
