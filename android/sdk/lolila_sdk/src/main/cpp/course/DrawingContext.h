//
// Created by tam on 2020/9/28.
//

#ifndef __DRAWINGCONTEXT_H__
#define __DRAWINGCONTEXT_H__

#ifndef __SIMPLESHADER_H__
#include "../shaders/SimpleShader.h"
#endif

class DrawingContext{
public:
    DrawingContext(SimpleShader& ss):_SimpleShaderRef(ss){

    }
public:
    void setModelMatrix(const Matrix& m)const{
        _SimpleShaderRef.setModelMatrix(m);
    }
    void setModelMatrix(const glm::mat4& m)const{
        _SimpleShaderRef.setModelMatrix(m);
    }
private:
    SimpleShader& _SimpleShaderRef;
};

#endif //__DRAWINGCONTEXT_H__
