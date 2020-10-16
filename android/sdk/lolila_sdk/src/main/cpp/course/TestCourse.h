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

#ifndef _SIMPLEPLANE_H_
#include "../shapes/SimplePlane.h"
#endif

#ifndef _HOLLOWTRIANGLE_H_
#include "../shapes/HollowTriangle.h"
#endif

#ifndef _HOLLOWCUBE_H
#include "../shapes/HollowCube.h"
#endif

#ifndef _SIMPLEAXIS_H
#include "../shapes/SimpleAxis.h"
#endif

#ifndef _SYMBLEM_H
#include "../shapes/SymbleM.h"
#endif

#ifndef _SYMBLEN_H
#include "../shapes/SymbleN.h"
#endif

#ifndef _SEMICIRCLE_H
#include "../shapes/SemiCircle.h"
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
    SimplePlane _plane;
    HollowTriangle ht;
    HollowCube hollowCube;
    SimpleAxis _axis;
    SymbleM _m;
    SymbleN _n;
    SemiCircle _sc;
};


#endif //DEMO_TESTCOURSE_H
