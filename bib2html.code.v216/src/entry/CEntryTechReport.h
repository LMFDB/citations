#ifndef __CEntryTechReport_h_
#define __CEntryTechReport_h_

#include <entry/CEntry.h>

class CEntryTechReport : public CEntry
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
