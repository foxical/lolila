//
// Created by tam on 2020/10/1.
//

#ifndef _COURSE1_H
#define _COURSE1_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
#endif

#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#endif

#ifndef _HOLLOWTRIANGLE_H_
#include "../shapes/HollowTriangle.h"
#endif

class Course1 : public AbstractCourse{
public:
    Course1();
    virtual ~Course1();
public:

    virtual void load();
    virtual void onDrawStep(DrawingContext& dc);

    virtual int getTotalStepsCount()const{
        return 1;
    }
    virtual int getCurStepNum()const{
        return 1;
    };

    virtual void nextStep();
    virtual void prevStep();
    virtual void reset();

private:
    SimpleLine _baseLine;
    HollowTriangle _t1;
    HollowTriangle _t2;
    float a1;
    float a2;
};


#endif //_COURSE1_H
