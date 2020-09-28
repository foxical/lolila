//
// Created by Administrator on 2018/1/31.
//

#include "SimpleVAO.h"
#include "SimpleVertexSet.h"

SimpleVAO::SimpleVAO():_vboId(0){

}
SimpleVAO::~SimpleVAO(){
    if(_vboId!=0){
        glDeleteBuffers(1,&_vboId);
    }
    if(_vaoId!=0){
        glDeleteVertexArrays(1,&_vaoId);
    }
}

void SimpleVAO::bind()const{
    glBindVertexArray(_vaoId);
}
void SimpleVAO::unBind()const{
    glBindVertexArray(0);
}

void SimpleVAO::load(const SimpleVertexSet &shapeVertex){

    const void*  vertices = (const void*)shapeVertex.getRawVertexArrayPtr();
    const GLsizeiptr size = shapeVertex.getRawVertexArraySize();
    const GLsizei strider = shapeVertex.getStider();

    glGenBuffers(1,&_vboId);

    glBindBuffer ( GL_ARRAY_BUFFER, _vboId );
    glBufferData ( GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW );

    // Bind the VAO and then setup the vertex
    // attributes
    bind();

    glBindBuffer ( GL_ARRAY_BUFFER, _vboId );

    glEnableVertexAttribArray ( 0/*VERTEX_POS_INDX*/ );
    glEnableVertexAttribArray ( 1/*VERTEX_COLOR_INDX*/ );

    glVertexAttribPointer (0, SimpleVertexSet::VERTEX_POS_SIZE,
                           GL_FLOAT, GL_FALSE, strider, (const void*)SimpleVertexSet::POS_VBO_OFFSET );

    glVertexAttribPointer (1, SimpleVertexSet::VERTEX_COLOR_SIZE,
                           GL_FLOAT, GL_FALSE, strider, (const void*)SimpleVertexSet::COLOR_VBO_OFFSET );

    // Reset to the default VAO
    unBind();
}