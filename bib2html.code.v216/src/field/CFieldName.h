/*
  Copyright © INRIA 2003, INRIA Eric Marchand
  
 
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
#ifndef __CFieldName_h_
#define __CFieldName_h_

#include <field/CField.h>
#include <string>
#include <tools/CList.h>
#include <config/CConfig.h>

class CName
{
 public:
  CName() ;
  ~CName() ;

  CName( CName& a) ;
  CName(string &_name, string &_given_name , string &_von, string &_jr)   ;

  CName& operator=( CName &a) ;
  CName& operator=( CConfigAuthor &a) ;
  int operator==( CName &a) ;
  int operator!=( CName &a) ;
  string last ;
  string von;
  string jr ;
  string first ;
  
  int Print(ostream& f) ;
  int  ExtractName(string &s) ;
} ;

class CFieldName : public CField
{

 public:
  CFieldName() ;
  ~CFieldName() ;

  CFieldName( CFieldName& f) ;
  CFieldName& operator=( CFieldName &f) ;

  CList<CName> LName ;
  
  CFieldName(string &s) ;
  
  int Print(ostream& f)  ;
  int Print(string& s) ;
  virtual string PrintBIBTEX()  =0 ;;
  virtual string PrintEE() =0 ;

} ;

class CFieldAuthor :  public CFieldName
{
 public:
  CFieldAuthor()  ; 
  ~CFieldAuthor() ;

  CFieldAuthor( CFieldAuthor& f);
  CFieldAuthor(string &s)  ;
  CFieldAuthor& operator=( CFieldAuthor &f) ;
  string PrintBIBTEX() ;
  string PrintEE() ;
  
} ;

class CFieldEditor :  public CFieldName
{
 public:
  CFieldEditor()  ;
  ~CFieldEditor() ;

  CFieldEditor( CFieldEditor& f);
  CFieldEditor(string &s)  ;
  CFieldEditor& operator=( CFieldEditor &f) ;
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;
#endif
