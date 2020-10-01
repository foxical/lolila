//
// Created by Administrator on 2018/2/2.
//

#ifndef __ABSTRACTCOURSE_H__
#define __ABSTRACTCOURSE_H__

class DrawingContext;

class AbstractCourse{
public:
    virtual void load()=0;
    virtual void onDrawStep(DrawingContext& dc)=0; // default 20ms per frame
    virtual int getTotalStepsCount()const=0;
    virtual int getCurStepNum()const=0;
    virtual void nextStep()=0;
    virtual void prevStep()=0;
    virtual void reset()=0;
};

#endif //__ABSTRACTCOURSE_H__
