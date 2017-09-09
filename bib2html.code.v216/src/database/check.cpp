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

using namespace std ;

#include <database/html.h>
#include <tools/String.h>
#include <include/constant.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <tools/time.h>

int CheckURL(CDataBase& B) 
{
}


int CheckPDF(CDataBase& B) 
{ 

  B.LEntry.Front() ;

  cout << endl <<"The following entries have no link toward a pdf files " << endl ;
  while (!B.LEntry.Outside())
  {
    CEntry *entry ;
    entry = B.LEntry.Value() ; 

    if (entry->f_url == NULL)
    {
      cout << "["<< entry->key<<"]" ;
    }
    B.LEntry.Next() ;
  }

  cout << endl ;
  return 0 ;
}

int 
CheckAbstract(CDataBase& B) 
{
  B.LEntry.Front() ;

  cout << endl <<"The following entries have no abstract " << endl ;
  while (!B.LEntry.Outside())
  {
    CEntry *entry ;
    entry = B.LEntry.Value() ; 

    if (entry->f_abstract == NULL)
    {
      cout << "["<< entry->key<<"]" ;
    }
    B.LEntry.Next() ;
  }
  cout << endl ;

  return 0 ;
}



int 
CheckDOI(CDataBase& B) 
{
  B.LEntry.Front() ;

  cout << endl <<"The following entries have no DOI " << endl ;
  while (!B.LEntry.Outside())
  {
    CEntry *entry ;
    entry = B.LEntry.Value() ; 

    if (entry->f_doi == NULL)
    {
      cout << "["<< entry->key<<"]" ;
    }
    B.LEntry.Next() ;
  }
  cout << endl ;

  return 0 ;
}

int 
CheckPages(CDataBase& B) 
{
  B.LEntry.Front() ;

  cout << endl <<"The following journal or conference have no pages numbers " << endl ;
  while (!B.LEntry.Outside())
  {
    CEntry *entry ;
    entry = B.LEntry.Value() ; 

    if ((entry->type_of_entry ==JOURNAL) ||
	(entry->type_of_entry ==INPROCEEDINGS)||
	(entry->type_of_entry ==CONFNAT)||
	(entry->type_of_entry ==WORKSHOP))
      if (entry->f_pages == NULL)
	{
	  cout << "["<< entry->key<<"]" ;
	}
    B.LEntry.Next() ;
  }
  cout << endl ;

  return 0 ;
}
