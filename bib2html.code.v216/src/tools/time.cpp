/*                                                                -*-c++-*-
#----------------------------------------------------------------------------
#  Copyright (C) 1998  IRISA-INRIA Rennes Vista Project
#  All Rights Reserved.
#
#
#    Contact:
#       Eric Marchand
#       IRISA-INRIA Rennes
#       Campus Universitaire de Beaulieu
#       35042 Rennes Cedex
#       France
#
#    email: marchand@irisa.fr
#    www  : http://www.irisa.fr/vista
#
#----------------------------------------------------------------------------
*/


#include <tools/time.h>


/*!
  \ingroug libtime
  \file time.cpp
  \author Francois Chaumette
  \date in 19... a long time ago...

  \note Ready to use with Linux and M$ Visual C++
*/

#ifdef WIN32
// Partie dependante de la plateforme (M$ Windows)

#include <afx.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include <app/CViSPApp.h>

/*!
  \ingroup libtime
  \brief Return the time in milli seconds
*/

int MeasureTimeMs()
{
	LARGE_INTEGER count;
	QueryPerformanceCounter(&count);
	return (int) (count.QuadPart*1000/(double)CViSPApp::getFrequency());
}

/*!
  \ingroup libtime
  \brief Wait t miliseconds after t0 ms

  \param t0 : reference time (in ms)
  \param t  : time to wait (in ms)

  \return 1 the function did wait, 0 the time was already over
*/

int Wait(int t0, int t)
{
	if (MeasureTimeMs()>t0+t)
		return 1;
	Wait(t-(MeasureTimeMs()-t0));
	return 0;
}


/*!
  \ingroup libtime
  \brief wait t  miliseconds from now
  \param t time to wait
  \return 1 the function did wait, 0 the time was already over
*/

void Wait(int t)
{
	int tfin=MeasureTimeMs()+t;
	while(MeasureTimeMs()<tfin);
}

void 
DateString(string &s)
{
  s = "" ;
  
}

#endif
#if (defined(__Linux_) || defined(__SunOS_)|| defined(__Darwin_)|| defined(__Cygwin_))



// Unix depend version


#include <sys/time.h>

long
MeasureTime()
{
  struct timeval tp;

  gettimeofday(&tp,0);
  return(tp.tv_usec);
}


/*!
  \ingroup libtime
  \brief Return the time in  milliseconds
*/
int MeasureTimeMs()
{
   struct timeval tp;
   gettimeofday(&tp,0);
   return(1000*tp.tv_sec + tp.tv_usec/1000);
}



/*!
  \ingroup libtime
  \brief Wait t miliseconds after t0 ms

  \param t0 : reference time (in ms)
  \param t  : time to wait (in ms)

  \return 1 the function did wait, 0 the time was already over
*/

int Wait(int t0,int t)
{
  struct timeval tp;

  gettimeofday(&tp, 0);
  if ((1000*tp.tv_sec + tp.tv_usec/1000 - t0) > t) return(1);
  else
    {
      do
	{
	  gettimeofday(&tp, 0);
	}
      while ((1000*tp.tv_sec + tp.tv_usec/1000 - t0) < t);

 return(0);
    }
}


/*!
  \ingroup libtime
  \brief wait t  miliseconds from now
  \param t time to wait
  \return 1 the function did wait, 0 the time was already over
*/
void Wait(int t)
{
  Wait(MeasureTimeMs(),t);
}

void 
DateString(string &s)
{
  time_t rawtime;
  time ( &rawtime );
  s = ctime (&rawtime) ;
  
}

#endif // Partie dependante de la plateforme



/*!
  \ingroup libtime
  \brief Return the time in  seconds
*/
double  MeasureTimeSecond()
{
  return MeasureTimeMs()/1000.0 ;
}



