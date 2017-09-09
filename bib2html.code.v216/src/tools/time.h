#ifndef TIME_HH
#define TIME_HH

/*!
  \ingroug libtime
  \file time.h
  \author Francois Chaumette 
  \date in 19... a long time ago...

  \note Ready to use with Linux and M$ Visual C++
*/
#include <tools/String.h>

long MeasureTime() ;
int MeasureTimeMs() ;
double MeasureTimeSecond() ;
int Wait(int t0,int t) ;
void Wait(int t) ;
void  DateString(string &s) ;

#endif
