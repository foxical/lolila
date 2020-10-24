//
// Created by tam on 2020/10/16.
//

#ifndef _COURSE2_H
#define _COURSE2_H

#ifndef __ABSTRACTCOURSE_H__
#include "AbstractCourse.h"
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

#ifndef _SYMBLEN_O
#include "../shapes/SymbleO.h"
#endif

#ifndef _SYMBLEN_C
#include "../shapes/SymbleC.h"
#endif

#ifndef __SIMPLE_LINE_H__
#include "../shapes/SimpleLine.h"
#endif

class Course2  : public AbstractCourse{
public:
    Course2();
    virtual ~Course2();
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
    SimpleAxis _axis;
    SymbleM _m;
    SymbleN _n;
    SymbleO _o;
    SymbleC _c;
    SimpleLine _lineM;
    SimpleLine _lineQ;
    SimpleLine _lineP;

    int _step;
};


#endif //_COURSE2_H
