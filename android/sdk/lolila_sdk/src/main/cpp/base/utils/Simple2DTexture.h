//
// Created by Administrator on 2018/1/19.
//

#ifndef __SIMPLE2DTEXTURE_H__
#define __SIMPLE2DTEXTURE_H__

#include <GLES3/gl3.h>

class Simple2DTexture{
public:
    Simple2DTexture();
    ~Simple2DTexture();
public:
    bool loadImage(const char* imgPath);
private:
    GLuint  _textureHandle;
    unsigned char* _imgData;
};

#endif //__SIMPLE2DTEXTURE_H__
