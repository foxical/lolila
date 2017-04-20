//
// Created by Administrator on 2017/4/6.
//

#ifndef __FLOATUTILS_H__
#define __FLOATUTILS_H__

class FloatUtils{
public:
    static bool isEqual(const float& f1, const float& f2){
        const float x = f1-f2;
        return ((x >= - EPSINON)&& (x <= EPSINON));
    }
    static float minus(const float& f1, const float& f2){
        if(isEqual(f1,f2)){
            return 0;
        }
        return f1-f2;
    }
private:
    static const float EPSINON;//=0.00001;

private:
    FloatUtils();
    ~FloatUtils();
};



#endif //__FLOATUTILS_H__
