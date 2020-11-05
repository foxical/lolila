//
// Created by tam on 2020/11/5.
//

#ifndef _SIMPLE3DCOORDINATE_H
#define _SIMPLE3DCOORDINATE_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class Simple3DCoordinate {
public:
    Simple3DCoordinate(){

    }
    ~Simple3DCoordinate(){

    }

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
    void draw()const;

private:
    SimpleVAO _vao1;
    SimpleVAO _vao2;
    SimpleVAO _vao3;
};


#endif //_SIMPLE3DCOORDINATE_H
