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
#ifndef __CFieldInteger_h_
#define __CFieldInteger_h_

#include <field/CField.h>
#include <string>

class CFieldInteger : public CField
{

 public:
  CFieldInteger() ;
  ~CFieldInteger() ;

  CFieldInteger( CFieldInteger& f) ;
  CFieldInteger& operator=( CFieldInteger &f) ;

  int s ;
  
  CFieldInteger(string &s) ;
  
  int Print(ostream& f)  ;
  int Print(string& s) ;
  virtual string PrintBIBTEX()  =0 ;;
  virtual string PrintEE() =0 ;
} ;

class CFieldYear :  public CFieldInteger
{
 public:
  CFieldYear() : CFieldInteger()  { ;} 
  ~CFieldYear() { ;}

  CFieldYear( CFieldYear& f): CFieldInteger(f){;}
  CFieldYear(string &s)  : CFieldInteger(s) {;} 
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldNumber :  public CFieldInteger
{
 public:
  CFieldNumber() : CFieldInteger()  { ;} 
  ~CFieldNumber() { ;}

  CFieldNumber( CFieldNumber& f): CFieldInteger(f){;}
  CFieldNumber(string &s)  : CFieldInteger(s) {;} 
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldChapter :  public CFieldInteger
{
 public:
  CFieldChapter() : CFieldInteger()  { ;} 
  ~CFieldChapter() { ;}

  CFieldChapter( CFieldChapter& f): CFieldInteger(f){;}
  CFieldChapter(string &s)  : CFieldInteger(s) {;} 
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;


#endif
 
