//
// Created by Administrator on 2018/1/31.
//

#include "SimpleVAO.h"
#include "SimpleVertexSet.h"
#include "../base/utils/AndroidLog.h"

SimpleVAO::SimpleVAO():_vboId1(0),_vboId2(0),_vaoId(0),_vsCount(0){

}
SimpleVAO::~SimpleVAO(){
    unLoad();
}

void SimpleVAO::unLoad(){
    if(_vboId1!=0){
        glDeleteBuffers(1,&_vboId1);
        _vboId1=0;
    }
    if(_vboId2!=0){
        glDeleteBuffers(1,&_vboId2);
        _vboId2=0;
    }
    if(_vaoId!=0){
        glDeleteVertexArrays(1,&_vaoId);
        _vaoId=0;
    }

    _vsCount=0;
}

void SimpleVAO::bind()const{
    if(_vaoId!=0) {
        glBindVertexArray(_vaoId);
    }
}
void SimpleVAO::unBind()const{
    glBindVertexArray(0);
}

void SimpleVAO::load(const SimpleVertexSet &shapeVertex){
    load(shapeVertex,NULL);
}

void SimpleVAO::load(const SimpleVertexSet &shapeVertex, const void* indices){

    // 记得要在这里分配VAO，即必须在opengl context 初始化之后
    glGenVertexArrays(1, &_vaoId);

    const void*  vertices = (const void*)shapeVertex.getRawVertexArrayPtr();
    const GLsizeiptr size = shapeVertex.getRawVertexArraySize();
    const GLsizei strider = shapeVertex.getStider();

    _vsCount = shapeVertex.getRawVertexCount();

    glGenBuffers(1,&_vboId1);
    glBindBuffer ( GL_ARRAY_BUFFER, _vboId1 );
    glBufferData ( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

    if( indices!=NULL){
        glGenBuffers(1,&_vboId2);
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _vboId2 );
        glBufferData ( GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW );
    }

    // Bind the VAO and then setup the vertex
    // attributes
    bind();

    glBindBuffer ( GL_ARRAY_BUFFER, _vboId1 );
    if( _vboId2!=0 ){
        glBindBuffer ( GL_ELEMENT_ARRAY_BUFFER, _vboId2 );
    }

    glEnableVertexAttribArray ( 0/*VERTEX_POS_INDX*/ );
    glEnableVertexAttribArray ( 1/*VERTEX_COLOR_INDX*/ );

    glVertexAttribPointer (0, SimpleVertexSet::VERTEX_POS_SIZE,
                           GL_FLOAT, GL_FALSE, strider, (const void*)SimpleVertexSet::POS_VBO_OFFSET );

    glVertexAttribPointer (1, SimpleVertexSet::VERTEX_COLOR_SIZE,
                           GL_FLOAT, GL_FALSE, strider, (const void*)SimpleVertexSet::COLOR_VBO_OFFSET );

    // Reset to the default VAO
    unBind();

    //LOGD("_vaoid:%i, _vboid1:%i,_vboId2:%i,ss:%i",_vaoId,_vboId1,_vboId2,sizeof(indices));


}