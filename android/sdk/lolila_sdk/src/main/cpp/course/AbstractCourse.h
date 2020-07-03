//
// Created by Administrator on 2018/2/2.
//

#ifndef __ABSTRACTCOURSE_H__
#define __ABSTRACTCOURSE_H__

class Matrix;

class AbstractCourse{
public:

    virtual void onInit()=0;
    virtual void onDraw(const Matrix& prj,const Matrix& view)=0;
    virtual int getTotalSteps()const=0;
    virtual int getCurStep()const=0;
    virtual void next()=0;
    virtual void prev()=0;
    virtual void reset()=0;

private:

};

#endif //__ABSTRACTCOURSE_H__
