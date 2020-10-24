//
// Created by tam on 2020/10/16.
//

#ifndef _SYMBLEO_H
#define _SYMBLEO_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SymbleO {
public:
    SymbleO(){

    }
    ~SymbleO(){

    }

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;

    //void getOutRect(GLfloat* rect)const;

    GLfloat getWidth()const;
    GLfloat getHeight()const;
private:
    SimpleVAO _vao;
};


#endif //_SYMBLEO_H
