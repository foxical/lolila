//
// Created by tam on 2020/10/19.
//

#include "CourseFactory.h"
#include "TestCourse.h"
#include "DrawingContext.h"
#include "Course1.h"
#include "Course2.h"
#include "Course3.h"
#include "Course4.h"
#include "Course5.h"
#include "Course6.h"

AbstractCourse* CourseFactory::createCourse(int no){
    switch (no){
        case -1:
            return new TestCourse();
        case 1:
            return new Course1();
        case 2:
            return new Course2();
        case 3:
            return new Course3();
        case 4:
            return new Course4();
        case 5:
            return new Course5();
        case 6:
            return new Course6();
        default:
            break;
    }
    return NULL;
}