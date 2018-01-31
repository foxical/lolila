//
// Created by Administrator on 2018/1/31.
//

#ifndef __ABSTRACTVAO_H__
#define __ABSTRACTVAO_H__

#include <GLES3/gl3.h>

class AbstractVAO{
public:
    AbstractVAO();
    virtual ~AbstractVAO();
public:

    void bind()const;
    void unBind()const;

private:

    // VertexArrayObject Id
    GLuint _vaoId;
};

#endif //__ABSTRACTVAO_H__
