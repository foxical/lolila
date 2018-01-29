//
// Created by Administrator on 2018/1/19.
//
#include <GLES3/gl3.h>
#include "Simple2DTexture.h"
#include "stb_image.h"

Simple2DTexture::Simple2DTexture():_textureHandle(-1),_imgData(NULL){

    glGenTextures(1, &_textureHandle);
    glBindTexture(GL_TEXTURE_2D, _textureHandle);
    // 为当前绑定的纹理对象设置环绕、过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Simple2DTexture::~Simple2DTexture(){
    if(_imgData!=NULL){
        stbi_image_free(_imgData);
    }
}

bool Simple2DTexture::loadImage(const char* imgPath){

    // 加载并生成纹理
    int width, height, nrChannels;
    _imgData = stbi_load(imgPath, &width, &height, &nrChannels, 0);
    if (_imgData!=NULL){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, _imgData);
        glGenerateMipmap(GL_TEXTURE_2D);
        return true;
    }
    return false;
}