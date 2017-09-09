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
#include <cctype>
#include <stdio.h>
#include <math.h>

#include <include/constant.h>

#include <field/CFieldString.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1
/*!
  Basic Constructor
*/
CFieldString::CFieldString() : CField()
{
}

/*!
  Destructor
*/
CFieldString::~CFieldString()
{
}


/*!
  copy operator
*/
CFieldString&
CFieldString::operator=( CFieldString &f)
{
  s = f.s ;
  return *this ;
}

/*!
  copy constructor
*/
CFieldString::CFieldString( CFieldString &ib)
{
  *this = ib ;
}

CFieldString::CFieldString(string &_s)
{

  if (_s.length()==0)
    s="" ;
  else
  {
    s = _s ;

    // supression des blanc qd il y en a trop
    gsub(s,"  "," ") ;
    SuppressLastDot(s) ;
  }
}

int CFieldString::Print(ostream& f)
{
    f << s  ;

    return 0 ;
}

int CFieldString::Print(string& _s)
{
  _s= s;
  return 0 ;
}

string
CFieldSchool::PrintBIBTEX()
{
  string st ;
  st += "School = {" + s + "}" ;
  return st ;
}
string
CFieldSchool::PrintEE()
{
  string st ;
  st += "%I " +s ;
  return st ;
}

string
CFieldInstitution::PrintBIBTEX()
{
  string st ;
  st += "Institution = {" + s + "}" ;
  return st ;
}

string
CFieldInstitution::PrintEE()
{
  string st ;
  st += "%I " + s  ;
  return st ;
}

string
CFieldAbstract::PrintBIBTEX()
{
  string st ;
  st += "Abstract = {" + s + "}" ;
  return st ;
}

string
CFieldAbstract::PrintEE()
{
  string st ;
  st += "%X " + s  ;
  return st ;
}

string
CFieldHowpublished::PrintBIBTEX()
{
  string st ;
  st += "Howpublished = {" + s + "}" ;
  return st ;
}

string
CFieldHowpublished::PrintEE()
{
  string st ;
  st += "%I " + s  ;
  return st ;
}
/*
string
CFieldURLtransp::PrintBIBTEX()
{
  string st ;// VOID
  return st ;
}
*/
string
CFieldDOI::PrintBIBTEX()
{
  string st ;// VOID
  return st ;
}

string
CFieldURLtransp::PrintEE()
{
  string st ;// VOID
  return st ;
}

string
CFieldSeries::PrintBIBTEX()
{
  string st ;
  st += "Series = {" + s + "}" ;
  return st ;
}

string
CFieldSeries::PrintEE()
{
  string st ;
  st += "%S " + s  ;
  return st ;
}

string
CFieldPublisher::PrintBIBTEX()
{
  string st ;
  st += "Publisher = {" + s + "}" ;
  return st ;
}

string
CFieldPublisher::PrintEE()
{
  string st ;
  st += "%I " + s  ;
  return st ;
}

string
CFieldAddress::PrintBIBTEX()
{
  string st ;
  st += "Address = {" + s + "}" ;
  return st ;
}

string
CFieldAddress::PrintEE()
{
  string st ;
  st += "%C " + s  ;
  return st ;
}

string
CFieldAddresse::PrintBIBTEX()
{
  string st ; // VOID
  return st ;
}

string
CFieldAddresse::PrintEE()
{
  string st ;// VOID
  return st ;
}

string
CFieldVolume::PrintBIBTEX()
{
  string st ;
  st += "Volume = {" + s + "}" ;
  return st ;
}

string
CFieldVolume::PrintEE()
{
  string st ;
  st += "%V " + s  ;
  return st ;
}

string
CFieldBookTitle::PrintBIBTEX()
{
  string st ;
  st += "BookTitle = {" + s + "}" ;
  return st ;
}

string
CFieldBookTitle::PrintEE()
{
  string st ;
  st += "%B " + s  ;
  return st ;
}

string
CFieldJournal::PrintBIBTEX()
{
  string st ;
  st += "Journal = {" + s + "}" ;
  return st ;
}

string
CFieldJournal::PrintEE()
{
  string st ;
  st += "%J " + s  ;
  return st ;
}

string
CFieldTitle::PrintBIBTEX()
{
  string st ;
  st += "Title = {" + s + "}" ;
  return st ;
}

string
CFieldTitle::PrintEE()
{
  string st ;
  st += "%T " + s  ;
  return st ;
}

string
CFieldArxiv::PrintBIBTEX()
{
  string st ;
  st += "Arxiv = {" + s + "}" ;
  return st ;
}

string
CFieldArxiv::PrintEE()
{
  string st ;
  // st += "%U " + s  ;
  return st ;
}

string
CFieldURL::PrintBIBTEX()
{
  string st ;
  st += "Url = {" + s + "}" ;
  return st ;
}

string
CFieldURL::PrintEE()
{
  string st ;
  st += "%U " + s  ;
  return st ;
}

string
CFieldURLtransp::PrintBIBTEX()
{
  string st ;
  st += "doi = {" + s + "}" ;
  return st ;
}

string
CFieldDOI::PrintEE()
{
  string st ;
  st += "%U " + s  ;
  return st ;
}

string
CFieldURLinterne::PrintBIBTEX()
{
  string st ;
  //  st += "Url = {" + s + "}" ;
  return st ;
}

string
CFieldURLinterne::PrintEE()
{
  string st ;
  //  st += "%U " + s  ;
  return st ;
}


string
CFieldType::PrintBIBTEX()
{
  string st ;
  st += "Type = {" + s + "}" ;
  return st ;
}

string
CFieldType::PrintEE()
{
  string st ;
  // not applied
  return st ;
}


string
CFieldNote::PrintBIBTEX()
{
  string st ;
  // not applied
  return st ;
}

string
CFieldNote::PrintEE()
{
  string st ;
  // not applied
  return st ;
}


string
CFieldXNote::PrintBIBTEX()
{
  string st ;
  // not applied
  return st ;
}

string
CFieldXNote::PrintEE()
{
  string st ;
  // not applied
  return st ;
}


string
CFieldXMisc::PrintBIBTEX()
{
  string st ;
  // not applied
  return st ;
}

string
CFieldXMisc::PrintEE()
{
  string st ;
  // not applied
  return st ;
}

