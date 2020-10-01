//
// Created by tam on 2020/10/1.
//

#ifndef _HOLLOWTRIANGLE_H_
#define _HOLLOWTRIANGLE_H_

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class HollowTriangle {
public:
    void load(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;
private:
    SimpleVAO _vao;
};


#endif //_HOLLOWTRIANGLE_H_
