//
// Created by TanLinghui on 2017/5/27.
//

#ifndef __VIEWFRUSTUM_H__
#define __VIEWFRUSTUM_H__

class ViewFrustum{
public:
    /**
     * a: horizontal field of view angle.
     * return the e
     */
    static double getFocalLength(const double& a);

    /**
     * w: width of display screen
     * h: height of display screen
     * a: horizontal field of view angle.
     * return the vertical field of view angle β
     */
    static double getVerticalViewAngle(const int& w,const int& h,const double& a);

private:
    ViewFrustum();
    ~ViewFrustum();
};

#endif //__VIEWFRUSTUM_H__
