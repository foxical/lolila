//
// Created by tam on 2020/10/18.
//

#ifndef _COURSE3_H
#define _COURSE3_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
#endif

#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#endif

class Course3 : public AbstractCourse{
public:
    Course3();
    virtual ~Course3();
public:

    virtual void load();
    virtual void onDrawStep(DrawingContext& dc);

    virtual int getTotalStepsCount()const{
        return 30;
    }
    virtual int getCurStepNum()const{
        return _step;
    };

    virtual void nextStep();
    virtual void prevStep();
    virtual void reset();
private:
    SimpleLine _line;
    int _step;
};


#endif //_COURSE3_H
