//
// Created by TanLinghui on 2017/5/27.
//

#ifndef __VIEWFRUSTUM_H__
#define __VIEWFRUSTUM_H__


class Matrix;

class ViewFrustum{
public:
    /**
     * a: horizontal field of view angle.
     * 水平视场角
     * return the e
     * 返回焦距
     */
    static float getFocalLength(const float& a);

    /**
     * w: width of display screen
     * h: height of display screen
     * a: horizontal field of view angle.
     * return the vertical field of view angle β
     */
    static float getVerticalViewAngle(const int& w,const int& h,const float& a);




private:
    ViewFrustum();
    ~ViewFrustum();
};

#endif //__VIEWFRUSTUM_H__
