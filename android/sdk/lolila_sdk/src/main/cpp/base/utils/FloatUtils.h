//
// Created by Administrator on 2017/4/6.
//

#ifndef __FLOATUTILS_H__
#define __FLOATUTILS_H__

class FloatUtils{
public:
    static bool isEqual(const float& f1, const float& f2){
        const float x = f1-f2;
        return ((x >= - EPSINON_F)&& (x <= EPSINON_F));
    }
    static float minus(const float& f1, const float& f2){
        if(isEqual(f1,f2)){
            return 0;
        }
        return f1-f2;
    }
    static bool isEqualD(const double& f1, const double& f2){
        const double x = f1-f2;
        return ((x >= - EPSINON_D)&& (x <= EPSINON_D));
    }
    static double minusD(const double& f1, const double& f2){
        if(isEqualD(f1,f2)){
            return 0;
        }
        return f1-f2;
    }

    static float radians(const float degree){
        return degree*PI/180.0f;
    }

public:
    static const float PI;

private:
    static const float EPSINON_F;
    static const double EPSINON_D;
private:
    FloatUtils();
    ~FloatUtils();
};



#endif //__FLOATUTILS_H__
