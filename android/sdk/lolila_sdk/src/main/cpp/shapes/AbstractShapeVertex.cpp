//
// Created by Administrator on 2018/1/30.
//

#include "AbstractShapeVertex.h"

const GLint AbstractShapeVertex::VERTEX_POS_SIZE=3;
const GLint AbstractShapeVertex::VERTEX_COLOR_SIZE=4;
const GLsizei AbstractShapeVertex::VERTEX_STRIDER_BASE = sizeof(GLfloat)*(VERTEX_POS_SIZE+VERTEX_COLOR_SIZE);
const GLuint AbstractShapeVertex::POS_VBO_OFFSET = 0x0;
const GLuint AbstractShapeVertex::COLOR_VBO_OFFSET = sizeof(GLfloat)*VERTEX_POS_SIZE;


AbstractShapeVertex::AbstractShapeVertex(){

}
AbstractShapeVertex::~AbstractShapeVertex(){

}

void AbstractShapeVertex::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    GLfloat* colorBuf = (GLfloat*)(((unsigned char*)getRawVertexArrayPtr()) + COLOR_VBO_OFFSET);
    const int count = getRawVertexCount();
    const GLsizei strider = getStider();
    for(int i=0;i<count;++i){
        colorBuf[0]=r;
        colorBuf[1]=g;
        colorBuf[2]=b;
        colorBuf[3]=a;
        colorBuf = (GLfloat*)(((unsigned char*)colorBuf) + strider);
    }
}