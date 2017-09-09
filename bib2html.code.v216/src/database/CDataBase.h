/*
  Copyright © INRIA 2002, Eric Marchand


  modify it under the terms of the GNU General Public License
  as published by the Free Software Foundation; either version 2
  of the License, or any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#ifndef __DATABASE_H_
#define __DATABASE_H_

#include <fstream>
#include <string>

#include <entry/CEntry.h>

class CDataBase
{
 public:
  CList<CEntry *> LEntry ;
  CConfig *cnf ;
 public:
  CDataBase() ;
  ~CDataBase() ;
  void Delete() ;

  CDataBase( CDataBase& f) ;
  CDataBase& operator=( CDataBase &it) ;
  //--------------------------------------------------------------------
  // I/O input
 public:
  int LoadBase(const char *nom, CConfig *cnf1) ;
  int SaveBaseBib(string &nom) ;
  int SaveBaseRef(const char *nom) ;
  int MergeBase(const char *nom) ;
  void PrintBase() ;
  int TestKey() ;
  // private:
  int ReadNextEntry(istream& f) ;


  void ExtractAuthor(CDataBase& B, CName &author) ;
  int  ExtractYear(CDataBase& B, int year, int ab=0) ;
  void ExtractType(CDataBase& B, int type_of_entry ) ;
  void ExtractTypeRA(CDataBase& B, int type_of_entry ) ;
  void ExtractTypeRA_sort_year(CDataBase& B, int type_of_entry ) ;
  void ExtractKeyword(CDataBase& B, CConfigKeyword &keyword) ;

  void SortYear() ;
  void SortYearInverse() ;
  void SortName() ;

  void Print() ;
  void Print(ofstream &f) ;

  void PrintTex(ofstream &f) ;
  void PrintHTML(ofstream &f) ;
  void PrintEE(ofstream &f) ;
  void PrintBIBTEX(ofstream &f) ;

  friend ostream& operator<< (ostream& os, CDataBase& p) ;

  int LoadBibFile(CConfig *cnf) ;
  int CreatePublicationPage() ;

  int NbEntries() { return LEntry.NbElement() ;}
} ;

int ExtractString(string &s, CConfig *cnf) ;

#endif
