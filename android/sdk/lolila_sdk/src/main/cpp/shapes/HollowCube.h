//
// Created by tam on 2020/10/1.
//

#ifndef _HOLLOWCUBE_H
#define _HOLLOWCUBE_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class HollowCube {
public:
    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;
private:
    SimpleVAO _vao1;
    SimpleVAO _vao2;
    SimpleVAO _vao3;
    SimpleVAO _vao4;
};


#endif //_HOLLOWCUBE_H
