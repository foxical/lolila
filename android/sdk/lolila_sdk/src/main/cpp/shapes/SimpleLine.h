//
// Created by Administrator on 2018/1/30.
//

#ifndef __SIMPLE_LINE_H__
#define __SIMPLE_LINE_H__

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SimpleLine{
public:
    SimpleLine(){

    }

    ~SimpleLine(){}
public:

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const{
        _vao.bind();
        glDrawArrays(GL_LINES,0,2);
        _vao.unBind();
    }

private:
    SimpleVAO _vao;
};


#endif //__SIMPLE_LINE_H__
