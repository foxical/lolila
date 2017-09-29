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
    static bool isEqual(const double& f1, const double& f2){
        const float x = f1-f2;
        return ((x >= - EPSINON_D)&& (x <= EPSINON_D));
    }
    static double minus(const double& f1, const double& f2){
        if(isEqual(f1,f2)){
            return 0;
        }
        return f1-f2;
    }
private:
    static const float EPSINON_F;
    static const double EPSINON_D;
private:
    FloatUtils();
    ~FloatUtils();
};



#endif //__FLOATUTILS_H__
