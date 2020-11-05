//
// Created by tam on 2020/11/5.
//

#ifndef _COURSE4_H
#define _COURSE4_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
#endif

#ifndef _SIMPLE3DCOORDINATE_H
#include "../shapes/Simple3DCoordinate.h"
#endif

#ifndef _SIMPLETRIANGLE_H
#include "../shapes/SimpleTriangle.h"
#endif

#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#endif

class Course4 : public AbstractCourse{
public:
    Course4(){}
    virtual ~Course4(){}
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

    virtual const Vector* getSceneCenterV()const;

private:
    Simple3DCoordinate _coordinate;
    SimpleTriangle _triangle;

};


#endif //_COURSE4_H
