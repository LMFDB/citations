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
#ifndef __CFieldPages_h_
#define __CFieldPages_h_

#include <field/CField.h>
#include <string>

class CFieldPages : public CField
{

 public:
  CFieldPages() ;
  ~CFieldPages() ;

  CFieldPages( CFieldPages& f) ;
  CFieldPages& operator=( CFieldPages &f) ;

  int pf, pe ;
  string s ;
  
  CFieldPages(string &s) ;
  
  int Print(ostream& f)  ;
  int Print(string& s) ;
  string PrintBIBTEX() ;
  string PrintEE() ;
} ;

#endif
 
