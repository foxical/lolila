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

    void load(GLfloat x0,GLfloat y0,GLfloat z0,
              GLfloat x1,GLfloat y1,GLfloat z1,
              GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

private:
    SimpleVAO _vao;
};


#endif //__SIMPLE_LINE_H__
