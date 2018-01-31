//
// Created by Administrator on 2018/1/30.
//

#ifndef __LINEVERTEX_H__
#define __LINEVERTEX_H__

#ifndef __ABSTRACTSHAPEVERTEX_H__
#include "AbstractShapeVertex.h"
#endif

class LineVertex: public AbstractShapeVertex{
public:
    LineVertex(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

        GLfloat* ptr = _vertexArray;
        ptr[0]=0;
        ptr[1]=0;
        ptr[2]=0;
        ptr = (GLfloat*)(((unsigned char*)_vertexArray)+VERTEX_STRIDER_BASE);
        ptr[0]=1.0;
        ptr[1]=0;
        ptr[2]=0;
        setColor(r,g,b,a);
    }
    ~LineVertex(){}
public:
    virtual const void* getRawVertexArrayPtr()const{
        return _vertexArray;
    }
    virtual GLuint getRawVertexCount()const{
        return 2;
    }
    virtual void draw()const{
        glDrawArrays(GL_LINES,0,getRawVertexCount());
    }
private:
    GLfloat _vertexArray[14];
};


#endif //__LINEVERTEX_H__
