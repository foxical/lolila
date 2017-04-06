//
// Created by Administrator on 2017/3/31.
//

#ifndef __LINEDISTANCE_H__
#define __LINEDISTANCE_H__


class Line;
class Ray;

class LineDistance{
public:

    static Ray line2ray(const Line&);

    static float calc(const Line& l1, const Line& l2);
    static float calc(const Ray& l1,const Ray& l2);
    static float calc(const Line& l1, const Ray& l2);
    static float calc(const Ray& l1,const Line& l2);


private:
    LineDistance();
    ~LineDistance();
};

#endif //__LINEDISTANCE_H__
