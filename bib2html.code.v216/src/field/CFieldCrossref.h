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
#ifndef __CFieldCrossref_h_
#define __CFieldCrossref_h_

#include <field/CField.h>
#include <string>
#include <tools/CList.h>
#include <config/CConfig.h>

class CFieldCrossref : public CField
{

 public:
  CFieldCrossref() ;
  ~CFieldCrossref() ;

  CFieldCrossref( CFieldCrossref& f) ;
  CFieldCrossref& operator=( CFieldCrossref &f) ;

  CList<string> LCrossref ;
  
  CFieldCrossref(string &s) ;
  
  int Print(ostream& f)  { return OK ; }
  int Print(string& s)  { return OK ; };
  
  string PrintBIBTEX() { string s ; return s ;}
  string PrintEE()  ;

} ;

#endif
