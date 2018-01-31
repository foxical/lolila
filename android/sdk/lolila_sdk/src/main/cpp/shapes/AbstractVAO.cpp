//
// Created by Administrator on 2018/1/31.
//

#include "AbstractVAO.h"

AbstractVAO::AbstractVAO():_vaoId(0){

}

AbstractVAO::~AbstractVAO(){
    if(_vaoId!=0){
        glDeleteVertexArrays(1,&_vaoId);
    }
}

void AbstractVAO::bind()const{
    glBindVertexArray(_vaoId);
}
void AbstractVAO::unBind()const{
    glBindVertexArray(0);
}