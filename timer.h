/* File:     timer.h
 *
 * Purpose:  Define a macro that returns the number of seconds that 
 *           have elapsed since some point in the past.  
 *
 * Note:     The argument passed to the GET_TIME macro should be
 *           a double, *not* a pointer to a double.
 *
 * Example:  
 *    #include "timer.h"
 *    . . .
 *    double start, finish, elapsed;
 *    . . .
 *    GET_TIME(start);
 *    . . .
 *    Code to be timed
 *    . . .
 *    GET_TIME(finish);
 *    elapsed = finish - start;
 *    printf("The code to be timed took %e seconds\n", elapsed);
 */
#ifndef _TIMER_H_
#define _TIMER_H_

#include <time.h>
#define BILLION 1E9

#define GET_TIME(now) { \
   struct timespec t; \
   clock_gettime(CLOCK_REALTIME, &t);	 \
   now = t.tv_sec + t.tv_nsec/BILLION;   \
}

#endif