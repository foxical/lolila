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
    void load(const SimpleVertexSet &shapeVertex, const void* indices);
    void load(const SimpleVertexSet &shapeVertex);
    void unLoad();

    inline GLuint getVSCount()const{
        return _vsCount;
    }

private:
    // VertexBufferObject Ids
    GLuint _vboId1;
    GLuint _vboId2;
    // VertexArrayObject Id
    GLuint _vaoId;

    GLuint _vsCount;
};


#endif //__SIMPLEVAO_H__
