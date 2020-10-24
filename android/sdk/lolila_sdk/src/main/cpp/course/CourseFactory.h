//
// Created by tam on 2020/10/19.
//

#ifndef DEMO_COURSEFACTORY_H
#define DEMO_COURSEFACTORY_H

class AbstractCourse;

class CourseFactory {

public :
    static AbstractCourse* createCourse(int no);
};


#endif //DEMO_COURSEFACTORY_H
