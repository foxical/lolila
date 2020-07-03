//
// Created by Administrator on 2018/1/31.
//

#include "SimpleVAO.h"
#include "AbstractShapeVertex.h"

SimpleVAO::SimpleVAO():_vboId(0){

}
SimpleVAO::~SimpleVAO(){
    if(_vboId!=0){
        glDeleteBuffers(1,&_vboId);
    }
}

void SimpleVAO::load(const AbstractShapeVertex &shapeVertex){

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

    glVertexAttribPointer ( 0, AbstractShapeVertex::VERTEX_POS_SIZE,
                            GL_FLOAT, GL_FALSE, strider, (const void*)AbstractShapeVertex::POS_VBO_OFFSET );

    glVertexAttribPointer ( 1, AbstractShapeVertex::VERTEX_COLOR_SIZE,
                            GL_FLOAT, GL_FALSE, strider,(const void*)AbstractShapeVertex::COLOR_VBO_OFFSET );

    // Reset to the default VAO
    unBind();
}