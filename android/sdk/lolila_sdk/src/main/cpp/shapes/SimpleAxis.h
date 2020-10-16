//
// Created by tam on 2020/10/10.
//

#ifndef _SIMPLEAXIS_H
#define _SIMPLEAXIS_H

#ifndef __SIMPLEVAO_H__
#include "../shaders/SimpleVAO.h"
#endif

class SimpleAxis {

public:
    SimpleAxis();
    ~SimpleAxis();
    void load(int len,GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    void draw()const;
private:
    int _length;
    SimpleVAO _vao1;
    SimpleVAO _vao2;
};


#endif //_SIMPLEAXIS_H
