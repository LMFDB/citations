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
#include <database/tex.h>
#include <database/check.h>

#include <tools/String.h>
#include <tools/divers.h>
#include <tools/time.h>

#define DEBUG_LEVEL2 0

#include <tools/ParseArgv.h>
#include <tools/system.h>


int
main(int ac, char *av[])
{
  cout << "Bib2html v215  © INRIA 2002-2007, Projet Lagadic, Eric Marchand" << endl ;
  CConfig c ;

  CDataBase ib ;

  char *diroutput ;
  diroutput = new char[FILENAME_MAX] ;

  char *dirbib ;
  dirbib = new char[FILENAME_MAX] ;

  char *name_config ;
  name_config = new char[FILENAME_MAX] ;
  strcpy(name_config,"") ; 

  int exec = FALSE;
  int force = FALSE ;
  int tms = MeasureTimeMs() ;
  ArgvInfo argTable[] =
  {
    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {NULL, ARGV_HELP, NULL, NULL," Bib2html v215  © INRIA 2002-2007, Projet Lagadic, Eric Marchand"},

    {NULL, ARGV_HELP, NULL, NULL,"     "},
    {"-diroutput",ARGV_STRING, (char *) 1, (char *) &diroutput,
     "output directory"
    },
    {"-dirbib",ARGV_STRING, (char *) 1, (char *) &dirbib,
     "bibtex files directorie"
    },
    {"-config",ARGV_STRING, (char *) 1, (char *) &name_config,
     "name of the configuration file"
    },
     {"-force",ARGV_CONSTANT, (char *) 1, (char *) &force,
     "create the needed subdirectories"
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
    if (name_bib!=NULL) delete []name_bib ;

  }
  //  exit(1) ;
  if (c.verbose==1) cout << "Reading time : " << ( MeasureTimeMs()-tms)/1000.0 <<" seconds to read the database" <<endl ; ;

  ib.TestKey() ;
  if (c.verbose==1) cout << "Sorting Keywords" << endl ;
  if(c.keyword_create_pages  == true) c.SortKeyword() ;
  if (c.verbose==1) cout << "Sorting year" << endl ;
  if(c.year_create_pages  == true)  c.SortYear() ;
  if (c.verbose==1) cout << "Sorting Author" << endl ;
  if(c.author_create_pages  == true)  c.SortAuthor() ;
  if (c.verbose==1) cout << "Sorting Ok" << endl ;

  if (force==1)
  {
    cout << "Create  needed subdirectories " << endl ;

    char s[FILENAME_MAX] ;
    sprintf(s,"%s",c.directory_base.c_str()) ;
    if (check_directory(s) <0) {  make_directory(s) ; }

    if(c.author_create_pages  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_author.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }
    if(c.year_create_pages  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_year.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }
    if(c.keyword_create_pages  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_keyword.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }
    if(c.category_create_pages  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_category.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }

    if(c.biblio_create_pages  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_publi.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }
    if(c.create_pages_all  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_all.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }
    if(c.create_pages_tex  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_tex.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }
    if(c.bibtex_link  == true)
    {
      sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_bibtex.c_str()) ;
      if (check_directory(s) <0) { make_directory(s) ; }
    }

    sprintf(s,"%s/%s",c.directory_base.c_str(),  c.directory_publi.c_str()) ;
    if (check_directory(s) <0) { make_directory(s) ; }
  }

  int nb =0 ;

  if (c.verbose==1)
  {
    cout <<  "   " << ib.LEntry.NbElement() << " entries in the database" << endl ;
    cout <<  "   " << ib.cnf->LKeyword.NbElement() << " keywords have to be indexed " <<endl ;
    cout <<  "   " << ib.cnf->LAuthor.NbElement() << " authors have to be indexed" <<endl ;
  }
  if (ib.LEntry.NbElement() !=0)
  {

   if (ib.cnf->author_create_pages)
   {
     if (c.verbose==1) cout << "Creating authors Pages" << endl ;
     int n = CreatePageAuthors(ib) ;
     nb+=n ;
     if (c.verbose==1)
       cout << "   " << n << " pages have been created " << endl ;
   }

   if (ib.cnf->tex)
   {
     if (c.verbose==1) cout << "Creating Tex Pages" << endl ;
     CreatePageAuthorsTex(ib) ;
     CreatePageAllTex(ib) ;
   }
   if (ib.cnf->year_create_pages) 
   {
     if (c.verbose==1) cout << "Creating years Pages" << endl ;
     int n = CreatePageYears(ib) ;
     n += CreatePageYears_ab(ib) ;
     n += CreatePageAll(ib) ;
     nb+=n ;
     if (c.verbose==1)
       cout << "   " << n << " pages have been created " << endl ;
   }
  
   if (ib.cnf->keyword_create_pages)
   {
     if (c.verbose==1) cout << "Creating keywords Pages" << endl ;
     int n = CreatePageKeywords(ib) ;
     nb+=n  ;
     if (c.verbose==1)
       cout << "   " << n << " pages have been created " << endl ;
   }

   if (ib.cnf->category_create_pages)
     {
     if (c.verbose==1) cout << "Creating categories Pages" << endl ;
     int n = CreatePageCategories( ib) ;
     nb+=n ;
     if (c.verbose==1)
       cout << "   " << n << " pages have been created " << endl ;
   }

   if (ib.cnf->biblio_create_pages)
   {
     if (c.verbose==1) cout << "Creating one page for each publication" << endl ;
     int n = ib.CreatePublicationPage() ;
     nb += n ;
     if (c.verbose==1)
       cout << "   " << n << " pages have been created " << endl ;    }
  }



  if(c.keyword_create_pages  == true) c.SortKeyword() ;
  if(c.year_create_pages  == true)  c.SortYear() ;
  if(c.author_create_pages  == true)  c.SortAuthor() ;

  CountEntries(ib) ;

  if (c.verbose==1) cout << "Creating Index Page" << endl ;
  CreateIndexPage(c) ;

  cout << "Number of PhD entries "  <<  c.nb_phd<<endl  ;
  cout << "Number of master thesis entries "  <<  c.nb_master<<endl  ;
  cout << "Number of journal entries "  <<  c.nb_journal<<endl  ;
  cout << "Number of national journal entries "  << c.nb_journalnat <<endl ;
  cout << "Number of book entries "  <<  c.nb_book <<endl ;
  cout << "Number of book chapter entries "  <<  c.nb_bookchapter <<endl ;
  cout << "Number of international conferences entries "  <<  c.nb_conf_internationale<<endl  ;
  cout << "Number of national conferences entries "  <<  c.nb_conf_nationale <<endl ;
  cout << "Number of workshop entries "  <<  c.nb_conf_workshop  <<endl ;
  cout << "Number of rr entries "  <<   c.nb_rr  <<endl ;
  cout << "Number of misc entries "  <<  c.nb_misc <<endl ;
  cout << "Number of invited entries "  <<  c.nb_invited <<endl ;
  cout << "Number of popularization entries "  << c.nb_popularization <<endl ;

  if (c.check_url == true) CheckURL(ib) ;
  if (c.check_pdf == true) CheckPDF(ib) ;
  if (c.check_doi == true) CheckDOI(ib) ;

  if (c.check_abstract == true) CheckAbstract(ib) ;
  if (c.check_pages == true) CheckPages(ib) ;


  ib.Delete() ;
  if (diroutput!=NULL) delete []diroutput ;
  if (dirbib!=NULL) delete []dirbib;

  //NOTE EM l'adresse name_config n'est pas la meme qu'apres le malloc
  //elle est modifie par le parsearcv
  // if (name_config!=NULL) delete []name_config;

  cout << "Total Processing time : " << ( MeasureTimeMs()-tms)/1000.0 <<" seconds" <<endl ; ;
  cout << "   " <<  nb <<" page have been created " << endl ;


  cout << "End bib2html" << endl ;

}
