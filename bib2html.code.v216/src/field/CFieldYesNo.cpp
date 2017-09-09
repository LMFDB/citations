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

#include <field/CFieldYesNo.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1 
/*!
  Basic Constructor
*/
CFieldYesNo::CFieldYesNo() : CField() 
{
}

/*!
  Destructor
*/
CFieldYesNo::~CFieldYesNo()
{
}


/*!
  copy operator
*/
CFieldYesNo&
CFieldYesNo::operator=(CFieldYesNo &f)
{
  s = f.s ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldYesNo::CFieldYesNo( CFieldYesNo &ib)
{
  *this = ib ; 
}

CFieldYesNo::CFieldYesNo(string &_s)
{
  
  string tmp1, tmp2 ;  
  suppress_white_and_tab(_s,  tmp1) ;
  tmp2 = upcase(tmp1) ;
  
  if (tmp2=="YES")
    s = TRUE ;
  else
    s = FALSE ;
}

CFieldYesNo::CFieldYesNo(int a)
{
  if (a==1)
    s = TRUE ;
  else
    s= FALSE ;
}

int CFieldYesNo::Print(ostream& f) 
{
  
    f << s  ;
    
    return 0 ;
}

int CFieldYesNo::Print(string& _s) 
{
  _s= s;
  return 0 ;
}
