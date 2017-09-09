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
#ifndef __CFieldBoolean_h_
#define __CFieldBoolean_h_

#include <field/CField.h>
#include <string>

class CFieldBoolean : public CField
{

 public:
  CFieldBoolean() ;
  ~CFieldBoolean() ; 

  CFieldBoolean( CFieldBoolean& f) ;
  CFieldBoolean& operator=( CFieldBoolean &f) ;

  int s ;
  
  CFieldBoolean(string &s) ;
  CFieldBoolean(int a) ;

  int Print(ostream& f)  ;
  int Print(string& s) ;

  string PrintBIBTEX() { string s ; return s ;}
  string PrintEE() { string s ; return s ;}
} ;

class CFieldToAppear :  public CFieldBoolean
{
 public:
  CFieldToAppear() : CFieldBoolean()  { ;} 
  ~CFieldToAppear() { ;}

  CFieldToAppear( CFieldToAppear& f): CFieldBoolean(f){;}
  CFieldToAppear(string &s)  : CFieldBoolean(s) {;} 
  CFieldToAppear(int a)  : CFieldBoolean(a) {;} 
} ;

class CFieldWorkshop :  public CFieldBoolean
{
 public:
  CFieldWorkshop() : CFieldBoolean()  { ;} 
  ~CFieldWorkshop() { ;}

  CFieldWorkshop( CFieldWorkshop& f): CFieldBoolean(f){;}
  CFieldWorkshop(string &s)  : CFieldBoolean(s) {;} 
} ;

class CFieldRA :  public CFieldBoolean
{
 public:
  CFieldRA() : CFieldBoolean()  { ;} 
  ~CFieldRA() { ;}

  CFieldRA( CFieldRA& f): CFieldBoolean(f){;}
  CFieldRA(string &s)  : CFieldBoolean(s) {;} 
} ;

class CFieldConfnat :  public CFieldBoolean
{
 public:
  CFieldConfnat() : CFieldBoolean()  { ;} 
  ~CFieldConfnat() { ;}

  CFieldConfnat( CFieldConfnat& f): CFieldBoolean(f){;}
  CFieldConfnat(string &s)  : CFieldBoolean(s) {;} 
} ;

class CFieldHDR :  public CFieldBoolean
{
 public:
  CFieldHDR() : CFieldBoolean()  { ;} 
  ~CFieldHDR() { ;}
  CFieldHDR(int a) : CFieldBoolean(a) {;}

  CFieldHDR( CFieldHDR& f): CFieldBoolean(f){;}
  CFieldHDR(string &s)  : CFieldBoolean(s) {;} 
} ;

#endif
 
