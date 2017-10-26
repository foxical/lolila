//
// Created by TanLingHui on 2017/5/27.
//
#include "ViewFrustum.h"
#include "../utils/FloatUtils.h"
#include <math.h>

static const float PI  = FloatUtils::PI;//3.14159265f

float ViewFrustum::getFocalLength(const float& a){
    return 1.0f/tanf( (a/2)*PI/180.0f );
}

float ViewFrustum::getVerticalViewAngle(const int& w,const int& h,const float& a){
    return  2* ( atanf( (((float)h)/((float)w))/getFocalLength(a) )  * 180.0f / PI );
}



