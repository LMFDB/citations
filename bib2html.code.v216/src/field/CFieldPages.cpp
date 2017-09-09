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

#include <field/CFieldPages.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1 
/*!
  Basic Constructor
*/
CFieldPages::CFieldPages() : CField() 
{
  pe = pf =0 ;
  s="" ;
}

/*!
  Destructor
*/
CFieldPages::~CFieldPages()
{
}


/*!
  copy operator
*/
CFieldPages&
CFieldPages::operator=(CFieldPages &f)
{
  pe = f.pe ;
  pf = f.pf ;
  s = f.s ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldPages::CFieldPages( CFieldPages &ib)
{
  *this = ib ; 
}

CFieldPages::CFieldPages(string &_s)
{
  pf = -1 ;
  pe = -1 ;

  unsigned int pos =  _s.find("+",0);
  if (pos == string::npos)
  {
    string   tmp1, tmp2 ;
    suppress_white_and_tab(_s,  tmp1) ;
    gsub(tmp1,"--","-") ;
    gsub(tmp1,",","-") ;
    before(tmp1,"-",tmp2) ;
    pf = atoi(tmp2.c_str()) ;
    after(tmp1,"-",tmp2) ;
    pe = atoi(tmp2.c_str()) ;
    Print(s) ;
  }
  else
  {
    string   tmp1, tmp2 ;
    suppress_white_and_tab(_s,  tmp1) ;
    before(tmp1,"+",tmp2) ;
    pf = atoi(tmp2.c_str()) ;
    Print(s) ;
    pe = -1 ;
  }
}

int CFieldPages::Print(ostream& f) 
{
  if ((pe !=-1) && (pf !=-1))
    f << itoa(pf) <<"-" << itoa(pe)   ;
  else
    if ((pe !=-1) && (pf ==-1))
      f << itoa(pe)    ;
    else
      if ((pe ==-1) && (pf !=-1))
	f << itoa(pf)    ;
  return 0 ;
}

int CFieldPages::Print(string& _s) 
{
 
  if ((pe !=-1) && (pf !=-1))
    _s= itoa(pf) +"-" +itoa(pe)   ;
  else
  {
    if ((pe !=-1) && (pf ==-1))
       _s= itoa(pe)    ;
    else
    {
      if ((pe ==-1) && (pf !=-1))
	 _s=  itoa(pf)    ;
    }
  }
  return 0 ;
}

string
CFieldPages::PrintBIBTEX()
{
  string st ;

  if ((pe !=-1) && (pf !=-1))
  st += "Pages = {" + itoa(pf) +"--"+itoa(pe) + "}" ;   
  else
    if ((pe !=-1) && (pf ==-1))
  st += "Pages = {" + itoa(pe) +"}" ;  
    else
      if ((pe ==-1) && (pf !=-1))
	 st += "Pages = {" + itoa(pf) + "}" ;
  return st ;
}

string
CFieldPages::PrintEE()
{
  string st ;
  if ((pe !=-1) && (pf !=-1))
    st += "%P " +  itoa(pf) +"-"+itoa(pe)  ;
  else
    if ((pe !=-1) && (pf ==-1))
      st += "%P " +  itoa(pe)  ;
    else
      if ((pe ==-1) && (pf !=-1))
	st += "%P " +  itoa(pf)  ;

  return st ;
}
