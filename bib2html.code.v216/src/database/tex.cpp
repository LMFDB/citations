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

#include <database/tex.h>
#include <tools/String.h>
#include <include/constant.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

int
CreatePageAuthorsTex(CDataBase& B)
{
  int nb  =0 ;
  int ok = 1 ;
  int nitem =1 ;

  int ntotal = B.cnf->LAuthor.NbElement() ;
  if (B.cnf->language1)
    B.cnf->language = LANGUAGE1 ;
  else
    if (B.cnf->language2)
      B.cnf->language = LANGUAGE2 ;  
int nmax ;
  if (B.cnf->language1)
    nmax = B.cnf->LAuthor.NbElement() ;
  if (B.cnf->language2)
    nmax += B.cnf->LAuthor.NbElement() ;
  while(ok==1)
  {
    B.cnf->LAuthor.Front() ;
    while(!B.cnf->LAuthor.Outside())
    {
      ofstream f ;
      string filename ;

      CConfigAuthor n = B.cnf->LAuthor.Value() ;


      string filename1 ;

      string name = n.name ;
      name = supress_slash(name) ;
      name = suppressaccent(name) ;
      string gv = suppressaccent(n.given_name) ;

      if (n.filename.length()==0)
	filename1=(gv)+"."+(name) ;
      else
	filename1 = n.filename ;

      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base +"/"+B.cnf->directory_author+"/"+filename1+B.cnf->language2_postfix + B.cnf->tex_postfix  ;
      else
	filename = B.cnf->directory_base +"/"+B.cnf->directory_author+"/"+filename1+B.cnf->language1_postfix + B.cnf->tex_postfix ;

      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout <<nitem++ <<"/"<<ntotal << " open " << filename <<endl ;
      f.open(filename.c_str()) ;
      nb++ ;


      CreatePageAuthorTex(f,B,n) ;

      printf("%d %% \r", (int)(nb*100.0/nmax)) ;
      cout <<flush ;
      f.close() ;
      B.cnf->LAuthor.Next() ;
    }
    if (B.cnf->language == LANGUAGE2)
    {
      ok =0 ;
    }
    else
    {
      if (B.cnf->language2)
	B.cnf->language = LANGUAGE2 ;
      else
	ok =0 ;
    }
  }


  return nb ;
}


void
CreatePageAuthorTex(ofstream& f,
		 CDataBase& B,
		 CConfigAuthor &author)
{
  CDataBase A ;

  CName a ;
  a = author ;
  B.ExtractAuthor(A,a) ;


  CreateMainPageCategoryTex(f,A,0) ;



}
int
CreatePageAllTex(CDataBase& B)
{
  int nb =0 ;

  int ok = 1 ;

  if (B.cnf->language1)
    B.cnf->language = LANGUAGE1 ;
  else
    if (B.cnf->language2)
      B.cnf->language = LANGUAGE2 ;
int nmax ;
  if (B.cnf->language1)
    nmax = B.cnf->LAuthor.NbElement() ;
  if (B.cnf->language2)
    nmax += B.cnf->LAuthor.NbElement() ;
  while(ok==1)
  {
      ofstream f ;
      string filename ;

      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base + "/"+B.cnf->directory_tex +"/tex"+B.cnf->language2_postfix + B.cnf->tex_postfix  ;
      else
	filename = B.cnf->directory_base + "/"+B.cnf->directory_tex +"/tex"+B.cnf->language1_postfix + B.cnf->tex_postfix ;
      suppress_white_and_tab(filename) ;

      nb++ ;

      f.open(filename.c_str()) ;

      CreateMainPageCategoryTex(f,B,0) ;

      printf("%d %% \r", (int)(nb*100.0/nmax)) ;
      cout <<flush ;
      f.close() ;

      if (B.cnf->language == LANGUAGE2)
      {
	ok =0 ;
      }
      else
      {
	if (B.cnf->language2)
	  B.cnf->language = LANGUAGE2 ;
	else
	  ok =0 ;
      }
  }
  return nb ;
}

void
CreateMainPageCategoryTex(ofstream& f, CDataBase &B, int ra)
{

  CDataBase These ;
  CDataBase Journal ;
  CDataBase JournalNat ;
  CDataBase Chapter ;
  CDataBase Conf ;
  CDataBase RReport ;
  CDataBase Book ;
  CDataBase Misc ;
  CDataBase Confnat ;
  CDataBase Workshop ;

  CDataBase Invited ;
  CDataBase Popularization ;
   if (B.cnf->language==LANGUAGE1)
   {
     B.cnf->category_phd =     B.cnf->category_phd_language1 ;
     B.cnf->category_journal =     B.cnf->category_journal_language1 ;
     B.cnf->category_book =    B.cnf->category_book_language1 ;
     B.cnf->category_bookchapter = B.cnf->category_bookchapter_language1 ;
     B.cnf->category_conf_internationale = B.cnf->category_conf_internationale_language1 ;
     B.cnf->category_conf_nationale =  B.cnf->category_conf_nationale_language1 ;
     B.cnf->category_conf_workshop  =  B.cnf->category_conf_workshop_language1  ;
     B.cnf->category_rr  = B.cnf->category_rr_language1  ;
     B.cnf->category_misc =  B.cnf->category_misc_language1 ;

  B.cnf->category_invited =  B.cnf->category_invited_language1 ;
  B.cnf->category_journalnat =B.cnf->category_journalnat_language1 ;
  B.cnf->category_popularization = B.cnf->category_popularization_language1 ;
   }
   else
   {
     B.cnf->category_phd =     B.cnf->category_phd_language2 ;
     B.cnf->category_journal =     B.cnf->category_journal_language2 ;
     B.cnf->category_book =    B.cnf->category_book_language2 ;
     B.cnf->category_bookchapter = B.cnf->category_bookchapter_language2 ;
     B.cnf->category_conf_internationale = B.cnf->category_conf_internationale_language2 ;
     B.cnf->category_conf_nationale =  B.cnf->category_conf_nationale_language2 ;
     B.cnf->category_conf_workshop  =  B.cnf->category_conf_workshop_language2  ;
     B.cnf->category_rr  = B.cnf->category_rr_language2  ;
     B.cnf->category_misc =  B.cnf->category_misc_language2 ;
  B.cnf->category_invited =  B.cnf->category_invited_language2 ;
  B.cnf->category_journalnat =B.cnf->category_journalnat_language2 ;
  B.cnf->category_popularization = B.cnf->category_popularization_language2 ;
   }
  {
  B.ExtractTypeRA_sort_year(Book,BOOK) ;
  B.ExtractTypeRA_sort_year(These,PHDTHESIS) ;
  B.ExtractTypeRA_sort_year(Journal,JOURNAL) ;
  B.ExtractTypeRA_sort_year(JournalNat,JOURNALNAT) ;
  B.ExtractTypeRA_sort_year(Invited,INVITED) ;
  B.ExtractTypeRA_sort_year(Chapter,INBOOK) ;
  B.ExtractTypeRA_sort_year(Conf,INPROCEEDINGS) ;
  B.ExtractTypeRA_sort_year(Workshop,WORKSHOP) ;
  B.ExtractTypeRA_sort_year(Confnat,CONFNAT) ;
  B.ExtractTypeRA_sort_year(Misc,MISC) ;
  B.ExtractTypeRA_sort_year(RReport,RR) ;
  B.ExtractTypeRA_sort_year(Popularization,POPULARIZATION) ;
  }


  if (B.cnf->language!=LANGUAGE1)
    if (These.LEntry.NbElement() !=0)
    {

      f << "\\paragraph{" << B.cnf->category_phd << "}" << endl ;
      These.PrintTex(f) ;
    }

  if (Book.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_book << "}" << endl ;
    Book.PrintTex(f) ; ;
  }

  if (Journal.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_journal << "}" << endl ;
    Journal.PrintTex(f) ; ;
  }

  if (JournalNat.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{"  << B.cnf->category_journalnat << "}" << endl ;
    JournalNat.PrintTex(f) ; ;
  }
  if (Chapter.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_bookchapter << "}" << endl ;
    Chapter.PrintTex(f) ; ;
  }

  if (Conf.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_conf_internationale << "}" << endl ;
    Conf.PrintTex(f) ; ;
  }

  if (B.cnf->generate_workshop_pages == true)
  if (Workshop.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_conf_workshop << "}" << endl ;
    Workshop.PrintTex(f) ;
  }

  if (Invited.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_invited << "}" << endl ;
    Invited.PrintTex(f) ; ;
  }


  if (Confnat.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_conf_nationale << "}" << endl ;
    Confnat.PrintTex(f) ;
  }

  if (Popularization.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_popularization << "}" << endl ;
    Popularization.PrintTex(f) ; ;
  }

  if (RReport.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_rr << "}" << endl ;
    RReport.PrintTex(f) ;
  }

  if (Misc.LEntry.NbElement() !=0)
  {
    f << "\\paragraph{" << B.cnf->category_misc << "}" << endl ;
    Misc.PrintTex(f) ;
  }

  if (B.cnf->language==LANGUAGE1)
    if (These.LEntry.NbElement() !=0)
    {
      f << "\\paragraph{" << B.cnf->category_phd << "}" << endl ;
      These.PrintTex(f) ;
    }


}
