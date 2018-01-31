//
// Created by Administrator on 2018/1/25.
//

#include "VBOHelper.h"
#include "AndroidLog.h"

VBOHelper::VBOHelper(GLenum target):_target(target),_bufferHandle(0){

}

VBOHelper::~VBOHelper(){
    if( _bufferHandle!=0) {
        glDeleteBuffers(1, &_bufferHandle);
    }
}

void VBOHelper::bindData(GLsizeiptr size,const void* data,GLenum usage){
    if( _bufferHandle==0){
        glGenBuffers(1,&_bufferHandle);
    }
    glBindBuffer(_target,_bufferHandle);
    glBufferData(_target,size,data,usage);
}

