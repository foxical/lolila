//
// Created by tam on 2020/10/16.
//

#ifndef _SEMICIRCLE_H
#define _SEMICIRCLE_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SemiCircle {
public:
    SemiCircle(){

    }
    ~SemiCircle(){

    }

    void load(GLfloat angleStrider,GLfloat radius, GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

private:
    SimpleVAO _vao;
};


#endif //_SEMICIRCLE_H
