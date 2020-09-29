//
// Created by tam on 2020/9/28.
//

#ifndef DEMO_TESTCOURSE_H
#define DEMO_TESTCOURSE_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
#endif



#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#endif

class TestCourse : public AbstractCourse{
public:
    TestCourse();
    ~TestCourse();
public:

    virtual void load();
    virtual void onDrawStep(DrawingContext& dc);

    virtual int getTotalStepsCount()const{
        return 1;
    }
    virtual int getCurStepNum()const{
        return 1;
    };
    virtual void nextStep(){

    }
    virtual void prevStep(){

    }
    virtual void reset(){

    }

private:

    SimpleLine _line1;
    SimpleLine _line2;
};


#endif //DEMO_TESTCOURSE_H
