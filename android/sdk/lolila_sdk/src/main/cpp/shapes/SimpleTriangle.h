//
// Created by tam on 2020/11/5.
//

#ifndef _SIMPLETRIANGLE_H
#define _SIMPLETRIANGLE_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SimpleTriangle {
public:
    SimpleTriangle(){}
    ~SimpleTriangle(){}

    void load(
            GLfloat x0, GLfloat y0, GLfloat z0,
            GLfloat x1, GLfloat y1, GLfloat z1,
            GLfloat x2, GLfloat y2, GLfloat z2,
            GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

private:
    SimpleVAO _vao;
};


#endif //_SIMPLETRIANGLE_H
