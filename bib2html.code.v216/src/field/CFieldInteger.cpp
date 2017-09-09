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

#include <field/CFieldInteger.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1 
/*!
  Basic Constructor
*/
CFieldInteger::CFieldInteger() : CField() 
{
}

/*!
  Destructor
*/
CFieldInteger::~CFieldInteger()
{
}


/*!
  copy operator
*/
CFieldInteger&
CFieldInteger::operator=(CFieldInteger &f)
{
  s = f.s ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldInteger::CFieldInteger( CFieldInteger &ib)
{
  *this = ib ; 
}

CFieldInteger::CFieldInteger(string &_s)
{
  gsub(_s," ","") ;
  _s = suppress_white_and_tab(_s) ;
  s = atoi(_s.c_str()) ;

  //  cout << "_s = |" << _s << "|  " << s << endl ;
}

int CFieldInteger::Print(ostream& f) 
{
  
    f << s  ;
    
    return 0 ;
}

int CFieldInteger::Print(string& _s) 
{
  _s= s;
  return 0 ;
}
string
CFieldChapter::PrintBIBTEX()
{
  string st ;
  st += "Chapter= {" + itoa(s) + "}" ;
  return st ;
}

string
CFieldChapter::PrintEE()
{
  string st ;
  // st += "%????????????? " +  itoa(s)  ;
  return st ;
}
string
CFieldNumber::PrintBIBTEX()
{
  string st ;
  st += "Number = {" +  itoa(s) + "}" ;
  return st ;
}

string
CFieldNumber::PrintEE()
{
  string st ;
  st += "%N " +  itoa(s)  ;
  return st ;
}

string
CFieldYear::PrintBIBTEX()
{
  string st ;
  st += "Year = {" +  itoa(s) + "}" ;
  return st ;
}

string
CFieldYear::PrintEE()
{
  string st ;
  st += "%D " +  itoa(s)  ;
  return st ;
}
