//
// Created by Administrator on 2018/1/31.
//

#ifndef __SIMPLEVAO_H__
#define __SIMPLEVAO_H__

#include <GLES3/gl3.h>

class SimpleVertexSet;

class SimpleVAO{
public:
    SimpleVAO();
    ~SimpleVAO();
public:

    void bind()const;
    void unBind()const;
    void load(const SimpleVertexSet &shapeVertex);

private:
// VertexBufferObject Ids
    GLuint _vboId;
    // VertexArrayObject Id
    GLuint _vaoId;
};


#endif //__SIMPLEVAO_H__
