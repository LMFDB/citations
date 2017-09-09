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


#include <config/CConfig.h>

CMonth::CMonth(int _n, string &_m)
{
  n = _n ;
  month = _m ;
}

CConfigMonth::CConfigMonth()
{
  LMonth += CMonth(1,"Janvier") ;
  LMonth += CMonth(2,"Février") ;
  LMonth += CMonth(3,"Mars") ;
  LMonth += CMonth(4,"Avril") ;
  LMonth += CMonth(5,"Mai") ;
  LMonth += CMonth(6,"Juin") ;
  LMonth += CMonth(7,"Juillet") ;
  LMonth += CMonth(8,"Août") ;
  LMonth += CMonth(9,"Septembre") ;
  LMonth += CMonth(10,"Octobre") ;
  LMonth += CMonth(11,"Novembre") ;
  LMonth += CMonth(12,"Décembre") ;
}
