//
// Created by tam on 2020/11/6.
//

#ifndef _COURSE5_H
#define _COURSE5_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
#endif

#ifndef _SIMPLE3DCOORDINATE_H
#include "../shapes/Simple3DCoordinate.h"
#endif

#ifndef _HOLLOWCUBE_H
#include "../shapes/HollowCube.h"
#endif

#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#include "../shapes/SimpleTriangle.h"

#endif



class Course5 : public AbstractCourse{
public:
    Course5(){}
    virtual ~Course5(){}
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
    HollowCube _cube;
    SimpleTriangle _tri1;
    SimpleTriangle _tri2;
};


#endif //_COURSE5_H
