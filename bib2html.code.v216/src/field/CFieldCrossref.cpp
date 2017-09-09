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

#include <field/CFieldCrossref.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1 
/*!
  Basic Constructor
*/
CFieldCrossref::CFieldCrossref() : CField() 
{
  LCrossref.Kill() ;
}

/*!
  Destructor
*/
CFieldCrossref::~CFieldCrossref()
{
  LCrossref.Kill() ;
}


/*!
  copy operator
*/
CFieldCrossref&
CFieldCrossref::operator=( CFieldCrossref &f)
{
  LCrossref = f.LCrossref ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldCrossref::CFieldCrossref( CFieldCrossref &ib)
{
  *this = ib ; 
}

CFieldCrossref::CFieldCrossref(string &s)
{
  LCrossref.Kill() ;

  gsub(s,";",",") ;

  unsigned int pos =  s.find(",",0);
  string s_keyword ;
  //  string keyword ;

  while (pos != string::npos)
  {
    before(s,",", s_keyword) ;
    after(s,",", s) ;

    s_keyword = suppress_white_and_tab(s_keyword) ;
    LCrossref += s_keyword ;
    pos =  s.find(",",0);
  }
  s = suppress_white_and_tab(s) ;

  LCrossref += s;
}
string
CFieldCrossref::PrintEE()
{
  
  string st ;
  return st ;
}


