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
#ifndef __CFieldString_h_
#define __CFieldString_h_

#include <field/CField.h>
#include <string>

class CFieldString : public CField
{

 public:
  CFieldString() ;
  ~CFieldString() ;

  CFieldString( CFieldString& f) ;
  CFieldString& operator=( CFieldString &f) ;

  string s ;

  CFieldString(string &s) ;

  int Print(ostream& f)  ;
  int Print(string& s) ;
  virtual string PrintBIBTEX() =0 ;
  virtual string PrintEE() =0 ;
} ;

class CFieldTitle :  public CFieldString
{
 public:
  CFieldTitle() : CFieldString()  { ;}
  ~CFieldTitle() { ;}

  CFieldTitle( CFieldTitle& f): CFieldString(f){;}
  CFieldTitle(string &s)  : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldJournal :  public CFieldString
{
 public:
  CFieldJournal() : CFieldString()  { ;}
  ~CFieldJournal() { ;}

  CFieldJournal( CFieldJournal& f): CFieldString(f){;}
  CFieldJournal(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldBookTitle :  public CFieldString
{
 public:
  CFieldBookTitle() : CFieldString()  { ;}
  ~CFieldBookTitle(){ ;}

  CFieldBookTitle( CFieldBookTitle& f): CFieldString(f){;}
  CFieldBookTitle(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldVolume :  public CFieldString
{
 public:
  CFieldVolume() : CFieldString()  { ;}
  ~CFieldVolume(){ ;}

  CFieldVolume( CFieldVolume& f): CFieldString(f){;}
  CFieldVolume(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldAddress :  public CFieldString
{
 public:
  CFieldAddress() : CFieldString()  { ;}
  ~CFieldAddress(){ ;}

  CFieldAddress( CFieldAddress& f): CFieldString(f){;}
  CFieldAddress(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldAddresse :  public CFieldString
{
 public:
  CFieldAddresse() : CFieldString()  { ;}
  ~CFieldAddresse(){ ;}

  CFieldAddresse( CFieldAddresse& f): CFieldString(f){;}
  CFieldAddresse(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldPublisher :  public CFieldString
{
 public:
  CFieldPublisher() : CFieldString()  { ;}
  ~CFieldPublisher(){ ;}

  CFieldPublisher( CFieldPublisher& f): CFieldString(f){;}
  CFieldPublisher(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;


class CFieldSeries :  public CFieldString
{
 public:
  CFieldSeries() : CFieldString()  { ;}
  ~CFieldSeries(){ ;}

  CFieldSeries( CFieldSeries& f): CFieldString(f){;}
  CFieldSeries(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;


class CFieldArxiv :  public CFieldString
{
 public:
  CFieldArxiv() : CFieldString()  { ;}
  ~CFieldArxiv(){ ;}

  CFieldArxiv( CFieldArxiv& f): CFieldString(f){;}
  CFieldArxiv(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldURL :  public CFieldString
{
 public:
  CFieldURL() : CFieldString()  { ;}
  ~CFieldURL(){ ;}

  CFieldURL( CFieldURL& f): CFieldString(f){;}
  CFieldURL(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldDOI :  public CFieldString
{
 public:
  CFieldDOI() : CFieldString()  { ;}
  ~CFieldDOI(){ ;}

  CFieldDOI( CFieldDOI& f): CFieldString(f){;}
  CFieldDOI(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldURLinterne :  public CFieldString
{
 public:
  CFieldURLinterne() : CFieldString()  { ;}
  ~CFieldURLinterne(){ ;}

  CFieldURLinterne( CFieldURLinterne& f): CFieldString(f){;}
  CFieldURLinterne(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldURLtransp :  public CFieldString
{
 public:
  CFieldURLtransp() : CFieldString()  { ;}
  ~CFieldURLtransp(){ ;}

  CFieldURLtransp( CFieldURLtransp& f): CFieldString(f){;}
  CFieldURLtransp(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldHowpublished :  public CFieldString
{
 public:
  CFieldHowpublished() : CFieldString()  { ;}
  ~CFieldHowpublished(){ ;}

  CFieldHowpublished( CFieldHowpublished& f): CFieldString(f){;}
  CFieldHowpublished(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldAbstract :  public CFieldString
{
 public:
  CFieldAbstract() : CFieldString()  { ;}
  ~CFieldAbstract(){ ;}

  CFieldAbstract( CFieldAbstract& f): CFieldString(f){;}
  CFieldAbstract(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldInstitution :  public CFieldString
{
 public:
  CFieldInstitution() : CFieldString()  { ;}
  ~CFieldInstitution(){ ;}

  CFieldInstitution( CFieldInstitution& f): CFieldString(f){;}
  CFieldInstitution(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldSchool :  public CFieldString
{
 public:
  CFieldSchool() : CFieldString()  { ;}
  ~CFieldSchool(){ ;}

  CFieldSchool( CFieldSchool& f): CFieldString(f){;}
  CFieldSchool(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldType :  public CFieldString
{
 public:
  CFieldType() : CFieldString()  { ;}
  ~CFieldType(){ ;}

  CFieldType( CFieldType& f): CFieldString(f){;}
  CFieldType(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldNote :  public CFieldString
{
 public:
  CFieldNote() : CFieldString()  { ;}
  ~CFieldNote(){ ;}

  CFieldNote( CFieldNote& f): CFieldString(f){;}
  CFieldNote(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldXNote :  public CFieldString
{
 public:
  CFieldXNote() : CFieldString()  { ;}
  ~CFieldXNote(){ ;}

  CFieldXNote( CFieldXNote& f): CFieldString(f){;}
  CFieldXNote(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

class CFieldXMisc :  public CFieldString
{
 public:
  CFieldXMisc() : CFieldString()  { ;}
  ~CFieldXMisc(){ ;}

  CFieldXMisc( CFieldXMisc& f): CFieldString(f){;}
  CFieldXMisc(string &s) : CFieldString(s) {;}
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

#endif

