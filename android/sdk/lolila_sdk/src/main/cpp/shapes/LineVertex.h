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
    LineVertex(){
        LineVertex(1,0,0,1);
    }
    LineVertex(GLfloat r, GLfloat g, GLfloat b, GLfloat a){
        setPos(0,0,0,0);
        setPos(1,1,0,0);
        setColor(r,g,b,a);
    }
    LineVertex(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1){
        setPos(0,x0,y0,z0);
        setPos(1,x1,y1,z1);
        setColor(1,0,0,1);
    }
    ~LineVertex(){}
public:
    virtual const GLfloat* getRawVertexArrayPtr()const{
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
