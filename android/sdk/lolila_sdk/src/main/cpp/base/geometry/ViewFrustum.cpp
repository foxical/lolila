//
// Created by TanLingHui on 2017/5/27.
//
#include "ViewFrustum.h"
#include <math.h>

#define PI 3.14159265

double ViewFrustum::getFocalLength(const double& a){
    return 1.0/tan( (a/2)*PI/180.0 );
}

double ViewFrustum::getVerticalViewAngle(const int& w,const int& h,const double& a){
    return  2* ( atan( (((double)h)/((double)w))/getFocalLength(a) )  * 180.0 / PI );
}