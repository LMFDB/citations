#ifndef __CEntryMasterThesis_h_
#define __CEntryMasterThesis_h_

#include <entry/CEntry.h>

class  CEntryMasterThesis: public CEntry
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
