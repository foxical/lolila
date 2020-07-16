//
// Created by tam on 2020/7/3.
//

#ifndef __TEMPLATEEXPORTDEF_H__
#define __TEMPLATEEXPORTDEF_H__

/**
 * Fuck 'warning: exported templates are unsupported'
 */
//#define USE_EXPORT_TEMPLATE


#if defined(USE_EXPORT_TEMPLATE)
#define EXPORT export
#else
#define EXPORT
#endif





#endif //__TEMPLATEEXPORTDEF_H__
