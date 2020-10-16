//
// Created by tam on 2020/10/10.
//

#include "SimpleAxis.h"
#include "../shaders/SimpleVertexSet.h"

SimpleAxis::SimpleAxis():_length(0){

}
SimpleAxis::~SimpleAxis(){

}

void SimpleAxis::load(int len,GLfloat r, GLfloat g, GLfloat b, GLfloat a){
    _length=len;
    // 数轴两端点
    SimpleVertexSet ls(2);
    ls.setColor(r,g,b,a);
    ls.setPos(0,0,0,0);
    ls.setPos(1,1.0f*((GLfloat)_length),0,0);
    _vao1.load(ls);
    // 数轴刻度线
    const int kc = (_length+1)*4;
    SimpleVertexSet ks(kc);
    ks.setColor(r,g,b,a);
    for(int i=0;i<=(_length);++i){
        const GLfloat x = 1.0f * ((GLfloat)(i));
        const GLfloat y = 0.5f;
        const int pidx = 2*i;
        ks.setPos(pidx,x,0,0);
        ks.setPos(pidx+1,x,y,0);
    }
    _vao2.load(ks);
}

void SimpleAxis::draw()const{

    _vao1.bind();
    glDrawArrays(GL_LINES,0,2);
    _vao1.unBind();

    const int kc = (_length+1)*4;
    _vao2.bind();
    glDrawArrays(GL_LINES,0,kc);
    _vao2.unBind();
}