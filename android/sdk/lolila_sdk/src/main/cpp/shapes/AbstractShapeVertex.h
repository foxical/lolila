//
// Created by Administrator on 2018/1/30.
//

#ifndef __ABSTRACTSHAPEVERTEX_H__
#define __ABSTRACTSHAPEVERTEX_H__

#include <GLES3/gl3.h>

class AbstractShapeVertex{
protected:
    AbstractShapeVertex();
    virtual ~AbstractShapeVertex();
public:

    virtual const GLfloat* getRawVertexArrayPtr()const=0;
    virtual GLuint getRawVertexCount()const=0;

    /**
     * In bytes
     */
    virtual GLsizeiptr getRawVertexArraySize()const{
        return getRawVertexCount() * getStider();
    }

    /**
     * in bytes
     */
    virtual GLsizei getStider()const{
        return VERTEX_STRIDER_BASE;
    }

    /**
     * 为每个顶点设置相同的颜色
     */
    void setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /**
     * 设置顶点坐标
     */
    void setPos(int posIdx, GLfloat x,GLfloat y ,GLfloat z);

public:

    virtual void draw()const=0;

public:
    static const GLint VERTEX_POS_SIZE; //3
    static const GLint VERTEX_COLOR_SIZE; // 4
    static const GLsizei VERTEX_STRIDER_BASE; // in bytes
    static const GLuint POS_VBO_OFFSET;  // in bytes
    static const GLuint COLOR_VBO_OFFSET; // in bytes

protected:

    GLfloat* getPosEntry(int idx)const;
    GLfloat* getColorEntry(int idx)const;

};



#endif //__ABSTRACTSHAPEVERTEX_H__
