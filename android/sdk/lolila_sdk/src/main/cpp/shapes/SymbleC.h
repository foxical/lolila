//
// Created by tam on 2020/10/17.
//

#ifndef _SYMBLEC_H
#define _SYMBLEC_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SymbleC {
public:
    SymbleC(){

    }
    ~SymbleC(){

    }

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

    GLfloat getWidth()const;
    GLfloat getHeight()const;

private:
    SimpleVAO _vao;
};


#endif //_SYMBLEC_H
