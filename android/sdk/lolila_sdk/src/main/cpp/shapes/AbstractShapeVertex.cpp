//
// Created by Administrator on 2018/1/30.
//

#include "AbstractShapeVertex.h"

const GLint AbstractShapeVertex::VERTEX_POS_SIZE=3;
const GLint AbstractShapeVertex::VERTEX_COLOR_SIZE=4;
const GLsizei AbstractShapeVertex::VERTEX_STRIDER_BASE = sizeof(GLfloat)*(VERTEX_POS_SIZE+VERTEX_COLOR_SIZE);
const GLuint AbstractShapeVertex::POS_VBO_OFFSET = 0x0;
const GLuint AbstractShapeVertex::COLOR_VBO_OFFSET = sizeof(GLfloat)*VERTEX_POS_SIZE;


static GLfloat* getEntry( const GLfloat* arrayHead, GLuint offset, GLsizei strider,int idx){
    unsigned char* ptr = (unsigned char*)( arrayHead);
    ptr += (offset + idx*strider);
    return (GLfloat*)ptr;
}

AbstractShapeVertex::AbstractShapeVertex(){

}
AbstractShapeVertex::~AbstractShapeVertex(){

}

GLfloat* AbstractShapeVertex::getPosEntry(int idx)const{
    return getEntry(getRawVertexArrayPtr(),POS_VBO_OFFSET,getStider(),idx);
}
GLfloat* AbstractShapeVertex::getColorEntry(int idx)const{
    return getEntry(getRawVertexArrayPtr(),COLOR_VBO_OFFSET,getStider(),idx);
}

void AbstractShapeVertex::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

    GLfloat* colorBuf = NULL;
    const int count = getRawVertexCount();
    for(int i=0;i<count;++i){
        colorBuf = getColorEntry(i);
        colorBuf[0]=r;
        colorBuf[1]=g;
        colorBuf[2]=b;
        colorBuf[3]=a;
    }
}

void AbstractShapeVertex::setPos(int posIdx, GLfloat x,GLfloat y ,GLfloat z){
    GLfloat* entry = getPosEntry(posIdx);
    entry[0]=x;
    entry[1]=y;
    entry[2]=z;
}