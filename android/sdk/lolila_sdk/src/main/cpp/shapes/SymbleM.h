//
// Created by tam on 2020/10/16.
//

#ifndef _SYMBLEM_H
#define _SYMBLEM_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SymbleM {
public:
    SymbleM(){

    }
    ~SymbleM(){

    }

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

private:
    SimpleVAO _vao;
};


#endif //_SYMBLEM_H
