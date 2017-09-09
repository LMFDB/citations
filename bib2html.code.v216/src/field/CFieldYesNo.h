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
#ifndef __CFieldYesNo_h_
#define __CFieldYesNo_h_

#include <field/CField.h>
#include <string>

class CFieldYesNo : public CField
{

 public:
  CFieldYesNo() ;
  ~CFieldYesNo() ; 

  CFieldYesNo( CFieldYesNo& f) ;
  CFieldYesNo& operator=( CFieldYesNo &f) ;

  int s ;
  
  CFieldYesNo(string &s) ;
  CFieldYesNo(int a) ;

  int Print(ostream& f)  ;
  int Print(string& s) ;

  string PrintBIBTEX() { string s ; return s ;}
  string PrintEE() { string s ; return s ;}
} ;

class CFieldXEditorialBoard :  public CFieldYesNo
{
 public:
  CFieldXEditorialBoard() : CFieldYesNo()  { ;} 
  ~CFieldXEditorialBoard() { ;}

  CFieldXEditorialBoard( CFieldXEditorialBoard& f): CFieldYesNo(f){;}
  CFieldXEditorialBoard(string &s)  : CFieldYesNo(s) {;} 
} ;

class CFieldXProceedings :  public CFieldYesNo
{
 public:
  CFieldXProceedings() : CFieldYesNo()  { ;} 
  ~CFieldXProceedings() { ;}

  CFieldXProceedings( CFieldXProceedings& f): CFieldYesNo(f){;}
  CFieldXProceedings(string &s)  : CFieldYesNo(s) {;} 
} ;

class CFieldXInternationalAudience :  public CFieldYesNo
{
 public:
  CFieldXInternationalAudience() : CFieldYesNo()  { ;} 
  ~CFieldXInternationalAudience() { ;}

  CFieldXInternationalAudience( CFieldXInternationalAudience& f): CFieldYesNo(f){;}
  CFieldXInternationalAudience(string &s)  : CFieldYesNo(s) {;} 
} ;

class CFieldXInvitedConference :  public CFieldYesNo
{
 public:
  CFieldXInvitedConference() : CFieldYesNo()  { ;} 
  ~CFieldXInvitedConference() { ;}

  CFieldXInvitedConference( CFieldXInvitedConference& f): CFieldYesNo(f){;}
  CFieldXInvitedConference(string &s)  : CFieldYesNo(s) {;} 
} ;

class CFieldXScientificPopularization :  public CFieldYesNo
{
 public:
  CFieldXScientificPopularization() : CFieldYesNo()  { ;} 
  ~CFieldXScientificPopularization() { ;}
  CFieldXScientificPopularization(int a) : CFieldYesNo(a) {;}

  CFieldXScientificPopularization( CFieldXScientificPopularization& f): CFieldYesNo(f){;}
  CFieldXScientificPopularization(string &s)  : CFieldYesNo(s) {;} 
} ;
#endif
 
