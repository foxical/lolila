//
// Created by Administrator on 2018/1/30.
//

#include "SimpleVertexSet.h"

const GLint SimpleVertexSet::VERTEX_POS_SIZE=3;
const GLint SimpleVertexSet::VERTEX_COLOR_SIZE=4;
const GLsizei SimpleVertexSet::VERTEX_STRIDER_BASE = sizeof(GLfloat) * (VERTEX_POS_SIZE + VERTEX_COLOR_SIZE);
const GLuint SimpleVertexSet::POS_VBO_OFFSET = 0x0;
const GLuint SimpleVertexSet::COLOR_VBO_OFFSET = sizeof(GLfloat) * VERTEX_POS_SIZE;


static GLfloat* getEntry( const GLfloat* arrayHead, GLuint offset, GLsizei strider,int idx){
    unsigned char* ptr = (unsigned char*)( arrayHead);
    ptr += (offset + idx*strider);
    return (GLfloat*)ptr;
}

SimpleVertexSet::SimpleVertexSet(){

}
SimpleVertexSet::~SimpleVertexSet(){

}

GLfloat* SimpleVertexSet::getPosEntry(int idx)const{
    return getEntry(getRawVertexArrayPtr(),POS_VBO_OFFSET,getStider(),idx);
}
GLfloat* SimpleVertexSet::getColorEntry(int idx)const{
    return getEntry(getRawVertexArrayPtr(),COLOR_VBO_OFFSET,getStider(),idx);
}

void SimpleVertexSet::setColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a){

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

void SimpleVertexSet::setPos(int posIdx, GLfloat x, GLfloat y , GLfloat z){
    GLfloat* entry = getPosEntry(posIdx);
    entry[0]=x;
    entry[1]=y;
    entry[2]=z;
}