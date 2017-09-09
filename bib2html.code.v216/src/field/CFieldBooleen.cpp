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

#include <field/CFieldBooleen.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1 
/*!
  Basic Constructor
*/
CFieldBoolean::CFieldBoolean() : CField() 
{
}

/*!
  Destructor
*/
CFieldBoolean::~CFieldBoolean()
{
}


/*!
  copy operator
*/
CFieldBoolean&
CFieldBoolean::operator=(CFieldBoolean &f)
{
  s = f.s ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldBoolean::CFieldBoolean( CFieldBoolean &ib)
{
  *this = ib ; 
}

CFieldBoolean::CFieldBoolean(string &_s)
{
  
  string tmp1, tmp2 ;  
  suppress_white_and_tab(_s,  tmp1) ;
  tmp2 = upcase(tmp1) ;
  
  if ((tmp2=="TRUE") || (tmp2=="YES"))
    s = TRUE ;
  else
    s = FALSE ;
}

CFieldBoolean::CFieldBoolean(int a)
{
  if (a==1)
    s = TRUE ;
  else
    s= FALSE ;
}

int CFieldBoolean::Print(ostream& f) 
{
  
    f << s  ;
    
    return 0 ;
}

int CFieldBoolean::Print(string& _s) 
{
  _s= s;
  return 0 ;
}
