#ifndef __CEntryPhdThesis_h_
#define __CEntryPhdThesis_h_

#include <entry/CEntry.h>

class  CEntryPhdThesis: public CEntry
{
 public:
  int CheckValidity() ;
  void Print(string &s) ;
  void PrintHTML(string &s) ;
  void PrintLATEX(string &s) ;
  void PrintBIBTEX(string &s) ;
  void PrintEE(string &s) ;
} ;

#endif
