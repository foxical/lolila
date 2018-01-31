//
// Created by Administrator on 2018/1/31.
//

#ifndef __SIMPLEVAO_H__
#define __SIMPLEVAO_H__

#ifndef __ABSTRACTVAO_H__
#include "AbstractVAO.h"
#endif

class AbstractShapeVertex;

class SimpleVAO:public AbstractVAO{
public:
    SimpleVAO();
    ~SimpleVAO();
public:

    void load(const AbstractShapeVertex &shapeVertex);

private:
// VertexBufferObject Ids
    GLuint _vboId;
};


#endif //__SIMPLEVAO_H__
