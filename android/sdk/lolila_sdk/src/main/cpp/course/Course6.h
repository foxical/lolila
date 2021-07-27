//
// Created by tam on 2021/7/23.
//

#ifndef _COURSE6_H
#define _COURSE6_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
#endif

#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#endif

#include "../shapes/SimpleAxis.h"

class Course6 : public AbstractCourse{
public:
    Course6();
    virtual ~Course6(){}
public:

    virtual void load();
    virtual void onDrawStep(DrawingContext& dc);

    virtual int getTotalStepsCount()const{
        return 99999;
    }
    virtual int getCurStepNum()const{
        return 0;
    };

    virtual void nextStep(){}
    virtual void prevStep(){}
    virtual void reset(){}


    virtual const Matrix* getCustomProjection()const;

private:

    SimpleLine _Line1;
    SimpleLine _Line2;
    SimpleAxis _axis1;
    SimpleAxis _axis2;
};

#endif //_COURSE6_H
