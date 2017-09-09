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

#include <field/CFieldKeyword.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1 
/*!
  Basic Constructor
*/
CFieldKeyword::CFieldKeyword() : CField() 
{
  LKeyword.Kill() ;
}

/*!
  Destructor
*/
CFieldKeyword::~CFieldKeyword()
{
  LKeyword.Kill() ;
}


/*!
  copy operator
*/
CFieldKeyword&
CFieldKeyword::operator=( CFieldKeyword &f)
{
  LKeyword = f.LKeyword ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldKeyword::CFieldKeyword( CFieldKeyword &ib)
{
  *this = ib ; 
}

CFieldKeyword::CFieldKeyword(string &s)
{
  LKeyword.Kill() ;

  gsub(s,";",",") ;

  unsigned int pos =  s.find(",",0);
  string s_keyword ;
  //  string keyword ;

  while (pos != string::npos)
  {
    before(s,",", s_keyword) ;
    after(s,",", s) ;

    //    s_keyword = suppress_white_and_tab(s_keyword) ;
    LKeyword += s_keyword ;
    pos =  s.find(",",0);
  }
  //  s = suppress_white_and_tab(s) ;

  LKeyword += s;
}
string
CFieldKeyword::PrintEE()
{
  
  string st ;
  string n ;
  LKeyword.Front() ;
  while (!LKeyword.Outside())
  {
    n = LKeyword.Value() ;
    st += "%K "+ n +"\n" ;
    LKeyword.Next() ;
  }
  return st ;
}


