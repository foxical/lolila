//
// Created by tam on 2020/10/16.
//

#ifndef _SYMBLEN_H
#define _SYMBLEN_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SymbleN {
public:
    SymbleN(){

    }
    ~SymbleN(){

    }

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

private:
    SimpleVAO _vao;
};


#endif //_SYMBLEN_H
