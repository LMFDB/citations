/*
  Copyright © INRIA 2002, Eric Marchand
  
 
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
#include <string>
#include <string.h>

#include <include/constant.h>

#include <entry/CEntry.h>
#include <database/CDataBase.h>
#include <database/html.h>

#include <tools/String.h>
#include <tools/divers.h>
#include <tools/time.h>

#define DEBUG_LEVEL2 0

#include <tools/ParseArgv.h>

int
main(int ac, char *av[])
{


  CConfig c ;

  CDataBase ib ;
 
  char *name_ref ;
  name_ref = new char[FILENAME_MAX] ;
  
  char *dirbib ;
  dirbib = new char[FILENAME_MAX] ;
  
  char *name_config ;
  name_config = new char[FILENAME_MAX] ;
  strcpy(name_config,"") ; //config.cnf") ;
  strcpy(name_ref,"ref.ref") ; //config.cnf") ;

  /*  char *name_bib;
  name_bib = new char[FILENAME_MAX] ;
  strcpy(name_bib,"") ;
  */
  int exec = FALSE;
  int tms = MeasureTimeMs() ;
  ArgvInfo argTable[] =
  {
    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {NULL, ARGV_HELP, NULL, NULL," bib2ref  © INRIA 2002, Éric Marchand"},

    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {"-config",ARGV_STRING, (char *) 1, (char *) &name_config,
     "name of the configuration file"
    },
    {"-name",ARGV_STRING, (char *) 1, (char *) &name_ref,
     "end note filename (output)"
    },
    {"x", ARGV_REST, (char *) NULL, (char *) &exec, "bibfile to parse."},
    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {NULL, ARGV_HELP, NULL, NULL," Contact Eric Marchand, Eric.Marchand@irisa.fr "},
    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {NULL, ARGV_END, NULL,NULL,NULL}
  } ;

  if (ParseArgv(&ac,av,argTable,0))
  {
    cout << endl << "Usage : " << av[0] << "  [-help] [-option] "<<endl ;
    exit(1) ;
  }

  if (strcmp(name_config,"")!=0)
  {
    c.LoadConfiguration(name_config) ;
    ib.cnf = &c ;
    ib.LoadBibFile(&c) ;
  }
  else
    c.LoadConfiguration("confref.cnf") ;

  for (int i=1 ; i < ac ; i++)
  {
    char *name_bib;
    name_bib = new char[FILENAME_MAX] ;
    strcpy(name_bib,"") ;

    if (strlen(dirbib)!=0)
    {
      strcat(name_bib,dirbib) ;
      strcat(name_bib,"/") ;
    }
    strcat(name_bib,av[i]) ;
    ib.LoadBase(name_bib,&c) ;
    if (name_bib!=NULL)delete []name_bib ;

  }



  ib.LoadBibFile(&c) ;

  cout << "There are " <<ib.LEntry.NbElement() << " entries in the data base" << endl ;
  

  ib.SaveBaseRef(name_ref) ;

  cout << "Processing time : " << ( MeasureTimeMs()-tms)/1000.0 <<" seconds" <<endl ; ;

  ib.Delete() ;
  

  cout << "End bib2html" << endl ;
}
