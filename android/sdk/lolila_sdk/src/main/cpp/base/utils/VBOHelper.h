//
// Created by Administrator on 2018/1/25.
//

#ifndef __VBOHELPER_H__
#define __VBOHELPER_H__

#include <GLES3/gl3.h>

class VBOHelper{
public:
    VBOHelper(GLenum target);
    ~VBOHelper();
public:
    /**
     * A Simple wrapper of glBufferData
     */
    void bindData(GLsizeiptr size,const void* data,GLenum usage);


public:

    /**
     * Wrapper of glVertexAttribPointer
     */
    class VertexAttribPointer{
    public:
        VertexAttribPointer(VBOHelper* host,GLuint index,GLint size,GLenum type,GLboolean normalized,GLsizei strider):_target(host->_target),_index(index){
            glBindBuffer(_target,host->_bufferHandle[0]);
            glVertexAttribPointer(index,size,type,normalized,strider,(const void*)0);
            glEnableVertexAttribArray(_index);
        }
        ~VertexAttribPointer(){
            glDisableVertexAttribArray(_index);
            glBindBuffer(_target,0);
        }
    private:
        GLenum _target;
        GLuint _index;
    };




private:
    GLenum  _target;
    GLuint _bufferHandle[1];
    friend class VertexAttribPointer;
};


#endif //__VBOHELPER_H__
