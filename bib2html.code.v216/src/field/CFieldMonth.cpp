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

#include <field/CFieldMonth.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL2 1
/*!
  Basic Constructor
*/
CFieldMonth::CFieldMonth() : CField()
{
}

/*!
  Destructor
*/
CFieldMonth::~CFieldMonth()
{
}


/*!
  copy operator
*/
CFieldMonth&
CFieldMonth::operator=(CFieldMonth &f)
{
  s = f.s ;
  return *this ;
}

/*!
  copy ructor
*/
CFieldMonth::CFieldMonth( CFieldMonth &ib)
{
  *this = ib ;
}

CFieldMonth::CFieldMonth(string &_s, CConfig *c)
{

  cnf = c ;
  string tmp ;
  suppress_white_and_tab(_s,  tmp) ;
  _s = upcase(tmp) ;

  s = 0 ;
  cnf->LMonth.Front() ;
  while(!cnf->LMonth.Outside())
  {
    CMonth m = cnf->LMonth.Value() ;
    if (upcase(m.month) == upcase(_s)) {s = m.n ; break ; }
    cnf->LMonth.Next() ;
  }
  if (s==0)
  {
    if (cnf->debug)
    {
    cerr << "Cannot find month "<<_s<< " in months defined " <<endl ;
    cerr << "in the configuration file "<< endl ;
    cerr << "Check the configuration file or change the bib file "<<endl ;
    }
  }

  s_french = cnf->month_f[s] ;
  s_english = cnf->month_e[s] ;
}

int CFieldMonth::Print(ostream& f)
{
    f << s  ;

    return 0 ;
}

int CFieldMonth::Print(string& _s)
{

  _s= itoa(s) ;
  return 0 ;
}

string
CFieldMonth::PrintBIBTEX()
{
  string st ;

  st += "Month = {" + cnf->month_e[s] +"}" ;
  return st ;
}

string
CFieldMonth::PrintEE()
{
  string st ;
  st += "%8 " + cnf->month_e[s]  ;
  return st ;
}
