//
// Created by tam on 2020/9/29.
//

#ifndef _SIMPLEPLANE_H_
#define _SIMPLEPLANE_H_

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SimplePlane{
public:
    SimplePlane(){

    }

    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;
private:
    SimpleVAO _vao;
};

#endif //_SIMPLEPLANE_H_
