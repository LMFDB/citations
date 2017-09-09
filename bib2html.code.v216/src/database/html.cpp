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
#include <stdio.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <tools/time.h>


void
PageBegin(ofstream &f, CConfig *cnf)
{
    if (cnf->language == LANGUAGE2)
      f << cnf->page_start_language2 <<endl ;
    else
      f << cnf->page_start_language1 <<endl ;

    if (!cnf->no_head_no_foot)
    {
      f << "<head><title></title> " << endl ;
      f << cnf->css <<endl ;
      f << "<meta name=\"GENERATOR\" content=\"bib2html 2.00 http://www.irisa.fr/prive/marchand/bib2html \"> " <<endl ;

      f << "</head> " << endl ;
     if (cnf->language == LANGUAGE2)
       f << cnf->page_header_language2 <<endl ;
     else
       f << cnf->page_header_language1 <<endl ;
    }
}

void
PageEnd(ofstream &f, CConfig *cnf)
{

  if (	cnf->language == LANGUAGE2 )
    if  (cnf->copyright_notice_language2.length() !=0 ) f << "<h1></h1><p><span class=\"BibCopyright\">" + cnf->copyright_notice_language2 + "</span><p>" ;
  if (	cnf->language == LANGUAGE1 )
    if  (cnf->copyright_notice_language1.length() !=0 )  f << "<h1></h1><p><span class=\"BibCopyright\">" + cnf->copyright_notice_language1 + "</span><p>" ;

  if (cnf->last_modified ==true)
    {
      
      string s ; DateString(s) ;
      if (	cnf->language == LANGUAGE2 )
	f << "<p><span class=\"BibCopyright\"> Dernières modifications " + s + "</span><p>" ;
      if (	cnf->language == LANGUAGE1 )
	f << "<p><span class=\"BibCopyright\"> Last update " + s + "</span><p>" ;
      
    }

  if (!cnf->no_head_no_foot)
    {

      if (cnf->language==LANGUAGE2)
	f << cnf->page_footer_language2 <<endl ;
      else
	f << cnf->page_footer_language1 <<endl ;
    }

    if (cnf->language==LANGUAGE2)
      f << cnf->page_end_language2 <<endl ;
    else
      f << cnf->page_end_language1 <<endl ;

}

void
PageEndNoCopyright(ofstream &f, CConfig *cnf)
{
  if (!cnf->no_head_no_foot)
    {

      if (cnf->language==LANGUAGE2)
	f << cnf->page_footer_language2 <<endl ;
      else
	f << cnf->page_footer_language1 <<endl ;
    }

    if (cnf->language==LANGUAGE2)
      f << cnf->page_end_language2 <<endl ;
    else
      f << cnf->page_end_language1 <<endl ;

}

void
CreateIndexPage(CConfig &cnf)
{
  int ok = 1 ;

  if (cnf.language1)
    cnf.language = LANGUAGE1 ;
  else
    if (cnf.language2)
      cnf.language = LANGUAGE2 ;
  while(ok==1)
  {
    string filename ;
    ofstream f ;
    if (cnf.language==LANGUAGE2)
      filename = cnf.directory_base + "/"+"index"+cnf.language2_postfix + cnf.html_postfix  ;
    else
      filename = cnf.directory_base + "/"+"index"+cnf.language1_postfix + cnf.html_postfix  ;
    suppress_white_and_tab(filename) ;
    f.open(filename.c_str()) ;
    int n=0 ;

    PageBegin(f,&cnf) ;

   

    if  (cnf.year_create_pages)
    {
      if (cnf.language==LANGUAGE2)
      {
	f << "<h1> " << cnf.title_index_language2  << "</h1>" <<endl ;
	filename = cnf.base_http + "/"+cnf.directory_all +"/all"+cnf.language2_postfix + cnf.html_postfix  ;
	f<<"<p> <a href=\""+filename+ "\"> Toutes les publications </a> <p>" <<endl ;
	f<< "<h2> Bibliographie par années </h2> <p> "<< endl ;
      }
      else
      {
	f << "<h1> " << cnf.title_index_language1  << "</h1>" <<endl ;
	filename = cnf.base_http + "/"+cnf.directory_all +"/all"+cnf.language1_postfix + cnf.html_postfix  ;

	f<<"<p> <a href=\""+filename+ "\"> All the publications </a> <p>" <<endl ;
	f<< "<h2> Bibliography by years </h2> <p> "<< endl ;
      }


      cnf.LYear.Front() ;
      f << "<table><tr> "<<endl ;
      while(!cnf.LYear.Outside())
      {

	int year = cnf.LYear.Value() ;

	if (cnf.language==LANGUAGE2)
	  filename = cnf.base_http + "/"+cnf.directory_year +"/"+itoa(year)+cnf.language2_postfix + cnf.html_postfix  ;
	else
	  filename = cnf.base_http + "/"+cnf.directory_year +"/"+itoa(year)+cnf.language1_postfix + cnf.html_postfix ;
	      suppress_white_and_tab(filename) ;

	f << "<td><a href=\"" + filename + "\">" +itoa(year) + "</a> </td> " ;
	n++ ;
	if (n > 5) {f << "</tr><tr>" << endl ; n=0 ;}
	cnf.LYear.Next() ;
      }

      f <<"</tr></table><p>" << endl ;
    }

    if  (cnf.author_create_pages)
    {
    if (cnf.language==LANGUAGE2)
      f<< "<h2> Bibliographie par auteurs </h2> <p> "<< endl ;
    else
      f<< "<h2> Bibliography by authors </h2> <p> "<< endl ;

    n=0 ;
    cnf.LAuthor.Front() ;
    f << "<table><tr> "<<endl ;
    while(!cnf.LAuthor.Outside())
    {
      CConfigAuthor na = cnf.LAuthor.Value() ;

      string filename1 ;

      string name = na.name ;
      name = supress_slash(name) ;
      name = suppressaccent(name) ;
      string gv = suppressaccent(na.given_name) ;

      if (na.filename.length()==0)
	filename1= (gv)+"."+(name) ;
      else
	filename1 = na.filename ;

      if (cnf.language==LANGUAGE2)
	filename = cnf.base_http +"/"+cnf.directory_author+"/"+filename1+cnf.language2_postfix + cnf.html_postfix  ;
      else
	filename = cnf.base_http +"/"+cnf.directory_author+"/"+filename1+cnf.language1_postfix + cnf.html_postfix ;
       suppress_white_and_tab(filename) ;

      f << "<td><a href=\"" + filename + "\">" + na.given_name +" " + na.name + "</a> </td> " ;
      n++ ;
       if (n > 3) {f << "</tr><tr>" << endl ; n=0 ;}

      cnf.LAuthor.Next() ;
    }
     f <<"</tr></table><p>" << endl ;
    }
    if (cnf.category_create_pages)
    {
      if (cnf.language==LANGUAGE1)
      {
	cnf.category_phd =     cnf.category_phd_language1 ;
	cnf.category_master =     cnf.category_master_language1 ;
	cnf.category_journal =     cnf.category_journal_language1 ;
	cnf.category_book =    cnf.category_book_language1 ;
	cnf.category_bookchapter = cnf.category_bookchapter_language1 ;
	cnf.category_conf_internationale = cnf.category_conf_internationale_language1 ;
	cnf.category_conf_nationale =  cnf.category_conf_nationale_language1 ;
	cnf.category_conf_workshop  =  cnf.category_conf_workshop_language1  ;
	cnf.category_rr  = cnf.category_rr_language1  ;
	cnf.category_misc =  cnf.category_misc_language1 ;
	cnf.category_invited =  cnf.category_invited_language1 ;
	cnf.category_journalnat =cnf.category_journalnat_language1 ;
	cnf.category_popularization = cnf.category_popularization_language1 ;
      }
      else
	{
	  cnf.category_phd =     cnf.category_phd_language2 ;
	cnf.category_master =     cnf.category_master_language2 ;
	cnf.category_journal =     cnf.category_journal_language2 ;
	  cnf.category_book =    cnf.category_book_language2 ;
	  cnf.category_bookchapter = cnf.category_bookchapter_language2 ;
	  cnf.category_conf_internationale = cnf.category_conf_internationale_language2 ;
	  cnf.category_conf_nationale =  cnf.category_conf_nationale_language2 ;
	  cnf.category_conf_workshop  =  cnf.category_conf_workshop_language2  ;
	  cnf.category_rr  = cnf.category_rr_language2  ;
	  cnf.category_misc =  cnf.category_misc_language2 ;
	  cnf.category_invited =  cnf.category_invited_language2 ;
	  cnf.category_journalnat =cnf.category_journalnat_language2 ;
	  cnf.category_popularization = cnf.category_popularization_language2 ;
      }
      string l ;
      if ( cnf.language == LANGUAGE1) l = cnf.language1_postfix ;
      if ( cnf.language == LANGUAGE2) l = cnf.language2_postfix ;

      if (cnf.language==LANGUAGE2)
	f<< "<h2> Bibliographie par catégorie </h2> <p> "<< endl ;
      else
	f<< "<h2> Bibliography by categories </h2> <p> "<< endl ;
      {
	f << "<table><tr> "<<endl ;
	filename = cnf.base_http +"/"+cnf.directory_category + "/Theses"+l+cnf.html_postfix ;

	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_phd != 0)
	  {
	    f << "<td>" << filename << cnf.category_phd ;
	    f << "</a></td>" ;
	  }

	filename = cnf.base_http +"/"+cnf.directory_category + "/Master"+l+cnf.html_postfix ;

	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_master != 0)
	  {
	    f << "<td>" << filename << cnf.category_master ;
	    f << "</a></td>" ;
	  }
	    f << "</tr><tr>" ;

	filename = cnf.base_http +"/"+cnf.directory_category + "/Journal"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_journal != 0)
	  {
	    f << "<td>" <<  filename <<cnf.category_journal ;
	    f << "</a></td>" ;
	  }


	filename = cnf.base_http +"/"+cnf.directory_category + "/JournalNat"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_journalnat != 0)
	  {
	    f << "<td>" <<  filename <<cnf.category_journalnat;
	    f << "</a></td>" ;
	  }

	filename = cnf.base_http +"/"+cnf.directory_category + "/Book"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_book != 0)
	  {
	    f << "<td>" <<  filename <<  cnf.category_book ;
	    f << "</a></td>" ;
	  }
	filename = cnf.base_http +"/"+cnf.directory_category + "/InBook"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_bookchapter != 0)
	  {	
	    f << "<td>" << filename << cnf.category_bookchapter ;
	    f << "</a></td>";
	  }
	f<<"</tr><tr>" ;
	filename = cnf.base_http +"/"+cnf.directory_category + "/Conference"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_conf_internationale != 0)
	  {
	    f << "<td>" << filename << cnf.category_conf_internationale ;
	    f << "</a></td>" ;
	  }
	if (cnf.generate_workshop_pages==true)
	{
	  filename = cnf.base_http +"/"+cnf.directory_category + "/Workshop"+l+cnf.html_postfix ;
	  suppress_white_and_tab(filename) ;
	  filename = "<a href=\"" + filename + "\">" ;
	  if (cnf.nb_conf_workshop != 0)
	    {	
	      f << "<td>" << filename <<  cnf.category_conf_workshop ;
	      f << "</a></td>" ;
	    }
	}
	filename = cnf.base_http +"/"+cnf.directory_category + "/Conference_nat"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_conf_nationale != 0)
	  {		
	    f << "<td>" << filename <<  cnf.category_conf_nationale ;
	    f << "</a></td>" ;
	  }
	f <<"</tr><tr>" ;
	filename = cnf.base_http +"/"+cnf.directory_category + "/RR"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_rr != 0)
	  {
	    f << "<td>" << filename <<  cnf.category_rr ;
	    f << "</a></td>" ;
	  }
	filename = cnf.base_http +"/"+cnf.directory_category + "/Misc"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_misc != 0)
	  {
	    f << "<td>" <<filename <<   cnf.category_misc ;
	    f << "</a></td>" ;
	  }	
	filename = cnf.base_http +"/"+cnf.directory_category + "/Popularization"+l+cnf.html_postfix ;
	suppress_white_and_tab(filename) ;
	filename = "<a href=\"" + filename + "\">" ;
	if (cnf.nb_popularization != 0)
	  {
	    f << "<td>" <<filename <<   cnf.category_popularization ;
	    f << "</a></td>" ;
	  }
	f << "</tr></table>"<<endl ;
      }
    }
    if (cnf.keyword_create_pages)
    {
      if (cnf.language==LANGUAGE2)
	f<< "<h2> Bibliographie par mots clés </h2> <p> "<< endl ;
      else
	f<< "<h2> Bibliography by keywords </h2> <p> "<< endl ;

      n=0 ;
      f << "<table><tr> "<<endl ;
      cnf.LKeyword.Front() ;
      while(!cnf.LKeyword.Outside())
      {
	string keyword = cnf.LKeyword.Value().key ;
	if (cnf.language==LANGUAGE2)
	  filename = cnf.base_http +"/"+cnf.directory_keyword +"/"+lowcase(suppress_white_and_tab(keyword))+cnf.language2_postfix + cnf.html_postfix  ;
	else
	  filename = cnf.base_http +"/"+cnf.directory_keyword +"/"+lowcase(suppress_white_and_tab(keyword))+cnf.language1_postfix + cnf.html_postfix ;
	suppress_white_and_tab(filename) ;

	f << "<td><a href=\"" + filename + "\">" ;
	if (cnf.language==LANGUAGE2)
	  f<< cnf.LKeyword.Value().key_language2 << endl ;
	else
	  f<< cnf.LKeyword.Value().key_language1<< endl ;
	f << "</a> </td> " ;
	n++ ;
	if (n > 3) {f << "</tr><tr>" << endl ; n=0 ;}

	cnf.LKeyword.Next() ;
      }
      f <<"</tr></table><p>" << endl ;
    }


    PageEnd(f,&cnf) ;

    f.close() ;
    if (cnf.language == LANGUAGE2)
    {
      ok =0 ;
    }
    else
    {
      if (cnf.language2)
	cnf.language = LANGUAGE2 ;
      else
	ok =0 ;
    }
    }
  }

int
CreatePageYears(CDataBase& B)
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
    B.cnf->LYear.Front() ;
    while(!B.cnf->LYear.Outside())
    {
      ofstream f ;
      string filename ;

      int year = B.cnf->LYear.Value() ;
      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base + "/"+B.cnf->directory_year +"/"+itoa(year)+B.cnf->language2_postfix + B.cnf->html_postfix  ;
      else
	filename = B.cnf->directory_base + "/"+B.cnf->directory_year +"/"+itoa(year)+B.cnf->language1_postfix + B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout <<"open " << filename <<endl ;
      nb++ ;
      f.open(filename.c_str()) ;

      CreatePageYear(f,B,year) ;

      printf(" %d %%\r", (int)(nb*100.0/nmax)) ;
      cout <<flush ;
      f.close() ;

      B.cnf->LYear.Next() ;
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

int
CreatePageYears_ab(CDataBase& B)
{
  int nb =0 ;

  int ok = 1 ;

  if (B.cnf->language1)
    B.cnf->language = LANGUAGE1 ;
  else
    if (B.cnf->language2)
      B.cnf->language = LANGUAGE2 ;
  while(ok==1)
  {
    if (B.cnf->ayear !=0)
    {
      ofstream f ;
      string filename ;

      int year = B.cnf->ayear ;
      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base + "/"+B.cnf->directory_year +"/+"+itoa(year)+B.cnf->language2_postfix + B.cnf->html_postfix  ;
      else
	filename = B.cnf->directory_base + "/"+B.cnf->directory_year +"/+"+itoa(year)+B.cnf->language1_postfix + B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout <<"open " << filename <<endl ;
      nb++ ;
      f.open(filename.c_str()) ;

      CreatePageYear(f,B,year,AFTER) ;

      f.close() ;
    }
    if (B.cnf->byear !=0)
    {
      ofstream f ;
      string filename ;

      int year = B.cnf->byear ;
      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base + "/"+B.cnf->directory_year +"/"+itoa(year)+"-"+B.cnf->language2_postfix + B.cnf->html_postfix  ;
      else
	filename = B.cnf->directory_base + "/"+B.cnf->directory_year +"/"+itoa(year)+"-"+B.cnf->language1_postfix + B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout <<"open " << filename <<endl ;
      nb++ ;
      f.open(filename.c_str()) ;

      CreatePageYear(f,B,year,BEFORE) ;

      f.close() ;
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

int
CreatePageAll(CDataBase& B)
{
  int nb =0 ;

  int ok = 1 ;

  if (B.cnf->language1)
    B.cnf->language = LANGUAGE1 ;
  else
    if (B.cnf->language2)
      B.cnf->language = LANGUAGE2 ;
  while(ok==1)
  {
      ofstream f ;
      string filename ;

      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base + "/"+B.cnf->directory_all +"/all"+B.cnf->language2_postfix + B.cnf->html_postfix  ;
      else
	filename = B.cnf->directory_base + "/"+B.cnf->directory_all +"/all"+B.cnf->language1_postfix + B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
      //     if (B.cnf->debug)

      nb++ ;
      f.open(filename.c_str()) ;

      PageBegin(f,B.cnf) ;

      if (	B.cnf->language == LANGUAGE2 )
	f<<"<h1> Toutes les publications </h1>" <<endl ;
      else
	f<<"<h1>All the publications </h1>" <<endl ;

     if (B.cnf->bibtex_link)
      {
	filename = B.cnf->directory_base + "/"+B.cnf->directory_bibtex +"/all.bib" ;
	B.SaveBaseBib(filename) ;
	filename = B.cnf->base_http + "/"+B.cnf->directory_bibtex +"/all.bib" ;
	f << "<p> \n <p align=\"right\"> Load the <a href=\""+filename+"\">BibTeX file</a>" <<endl ;
      }
      CreateMainPageCategory(f,B,1) ;

      PageEnd(f,B.cnf) ;

      f.close() ;

      if (B.cnf->bibtex_link)
      {
	filename = B.cnf->directory_base + "/"+B.cnf->directory_bibtex +"/all.bib" ;
	B.SaveBaseBib(filename) ;
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

int
CreatePageKeywords(CDataBase& B)
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
    B.cnf->LKeyword.Front() ;
    while(!B.cnf->LKeyword.Outside())
    {
      ofstream f ;
      string filename ;

      string keyword = B.cnf->LKeyword.Value().key ;
      if (B.cnf->language==LANGUAGE2)
	filename = B.cnf->directory_base + "/"+B.cnf->directory_keyword +"/"+lowcase(suppress_white_and_tab(keyword))+B.cnf->language2_postfix + B.cnf->html_postfix  ;
      else
	filename = B.cnf->directory_base +"/"+B.cnf->directory_keyword +"/"+lowcase(suppress_white_and_tab(keyword))+B.cnf->language1_postfix + B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout <<"open " << filename <<endl ;
      f.open(filename.c_str()) ;
      nb++ ;

      CreatePageKeyword(f,B,B.cnf->LKeyword.Value() ) ;
   printf("%d %%\r", (int)(nb*100.0/nmax)) ;
      cout <<flush ;
      f.close() ;
      if (B.cnf->bibtex_link)
      {
	filename = B.cnf->directory_base + "/"+B.cnf->directory_bibtex +"/"+lowcase(suppress_white_and_tab(keyword))+".bib" ;
	B.SaveBaseBib(filename) ;
      }
      B.cnf->LKeyword.Next() ;
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

int
CreatePageAuthors(CDataBase& B)
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
    cout << (int)(nb*100.0/nmax) << "% \r";
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
	filename = B.cnf->directory_base +"/"+B.cnf->directory_author+"/"+filename1+B.cnf->language2_postfix + B.cnf->html_postfix  ;
      else
	filename = B.cnf->directory_base +"/"+B.cnf->directory_author+"/"+filename1+B.cnf->language1_postfix + B.cnf->html_postfix ;

      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout <<nitem++ <<"/"<<ntotal << " open " << filename <<endl ;
      f.open(filename.c_str()) ;
      nb++ ;


      CreatePageAuthor(f,B,n) ;
 
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
CreatePageYear(ofstream& f, CDataBase& B, int year, int ab)
{
  CDataBase A ;
  int x = B.ExtractYear(A,year, ab) ;
  PageBegin(f,B.cnf) ;

  if (ab==AFTER)
  {
    if (x<=year)
      f << "<h1> " << "Publications " << year << "</h1>" <<endl ;
    else
      f << "<h1> " << "Publications " << year << "-" << x << "</h1>" <<endl ;
  }
  else if (ab==BEFORE)
  {
    if (x>=year)
      f << "<h1> " << "Publications " << year << "</h1>" <<endl ;
    else
      f << "<h1> " << "Publications " << x << "-" << year << "</h1>" <<endl ;
  }
  else
    if (year !=0)
      f << "<h1> " << "Publications " << year << "</h1>" <<endl ;
   //  else
//     {
//       if (	B.cnf->language == LANGUAGE2 )
// 	f << "<h1> " << "Toutes les publications</h1>" <<endl ;
//       else
// 	f << "<h1> " << "All the publications</h1>" <<endl ;
//     }
  CreateMainPageCategory(f,A,1) ;
  if (B.cnf->bibtex_link)
  {
    string filename ;
    filename = B.cnf->directory_base + "/"+B.cnf->directory_bibtex +"/"+itoa(year)+".bib" ;
    A.SaveBaseBib(filename) ;
  }
  PageEnd(f,B.cnf) ;

}

void
CreatePageKeyword(ofstream& f, CDataBase& B, CConfigKeyword &keyword)
{
  CDataBase A ;

  B.ExtractKeyword(A,keyword) ;

  PageBegin(f,B.cnf) ;

  if (	B.cnf->language == LANGUAGE2 )
    f << "<h1> " << keyword.key_language2 << "</h1>" <<endl ;
  else
    f << "<h1> " <<keyword.key_language1 << "</h1>" <<endl ;

  CreateMainPageCategory(f,A,1) ;

  PageEnd(f,B.cnf) ;
}

void
CreatePageAuthor(ofstream& f,
		 CDataBase& B,
		 CConfigAuthor &author)
{
  CDataBase A ;

  CName a ;
  a = author ;
  B.ExtractAuthor(A,a) ;

  PageBegin(f,B.cnf) ;

  if (	B.cnf->language == LANGUAGE2 )
    f << "<h1> " << "Publications de " << author.given_name <<" " << author.name << "</h1>" <<endl ;
  else
    f << "<h1> " << "Publications of " << author.given_name <<" " << author.name << "</h1>" <<endl ;

  if (B.cnf->bibtex_link)
  {
    string filename ;
    string filename1 ;

    string name = author.name ;
    name = supress_slash(name) ;
    name = suppressaccent(name) ;
    string gv = suppressaccent(author.given_name) ;
    if (author.filename.length()==0)
      filename1=(gv)+"."+(name) ;
    else
      filename1 = author.filename ;
    filename = B.cnf->directory_base + "/"+B.cnf->directory_bibtex +"/"+filename1+".bib" ;
    A.SaveBaseBib(filename) ;



    filename = B.cnf->base_http + "/"+B.cnf->directory_bibtex +"/"+filename1+".bib" ;
    f << "<p> \n <p align=\"right\"> Load the <a href=\""+filename+"\">BibTeX file</a>" <<endl ;

  }

  CreateMainPageCategory(f,A,0) ;

  PageEnd(f,B.cnf) ;


}


void
CreateMainPageCategory(ofstream& f, CDataBase &B, int ra)
{
  CDataBase These ;
  CDataBase Master ;
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
     B.cnf->category_master =     B.cnf->category_master_language1 ;
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
     B.cnf->category_master =     B.cnf->category_master_language2 ;
     
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
  if (ra==1)
  {
  B.ExtractTypeRA_sort_year(Book,BOOK) ;
  B.ExtractTypeRA_sort_year(These,PHDTHESIS) ;
  B.ExtractTypeRA_sort_year(Master,MASTERTHESIS) ;
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
  else
  {
    B.ExtractType(Book,BOOK) ; 
    B.ExtractType(These,PHDTHESIS) ; 
    B.ExtractType(Master,MASTERTHESIS) ;
    B.ExtractType(Journal,JOURNAL) ;
    B.ExtractType(Invited,INVITED) ;
    B.ExtractType(JournalNat,JOURNALNAT) ;
    B.ExtractType(Chapter,INBOOK) ;
    B.ExtractType(Conf,INPROCEEDINGS) ;
    B.ExtractType(Workshop,WORKSHOP) ;
    B.ExtractType(Confnat,CONFNAT) ;
    B.ExtractType(Misc,MISC) ;
    B.ExtractType(RReport,RR) ;
    B.ExtractType(Popularization,POPULARIZATION) ;

 }
  if (B.cnf->language!=LANGUAGE1)
  {
    if (These.LEntry.NbElement() !=0)
    {
      f << "<h2>" << B.cnf->category_phd << "</h2>" << endl ;
      These.PrintHTML(f) ;
    }

  }

  if (Book.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_book << "</h2>" << endl ;
    Book.PrintHTML(f) ; ;
  }

  if (Journal.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_journal << "</h2>" << endl ;
    Journal.PrintHTML(f) ; ;
  }
  if (JournalNat.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_journalnat << "</h2>" << endl ;
    JournalNat.PrintHTML(f) ; ;
  }

  if (Chapter.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_bookchapter << "</h2>" << endl ;
    Chapter.PrintHTML(f) ; ;
  }

  if (Conf.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_conf_internationale << "</h2>" << endl ;
    Conf.PrintHTML(f) ; ;
  }

  if (B.cnf->generate_workshop_pages == true)
  if (Workshop.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_conf_workshop << "</h2>" << endl ;
    Workshop.PrintHTML(f) ;
  }

  if (Invited.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_invited << "</h2>" << endl ;
    Invited.PrintHTML(f) ; ;
  }

  if (Confnat.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_conf_nationale << "</h2>" << endl ;
    Confnat.PrintHTML(f) ; ;
  }

  if (Popularization.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_popularization << "</h2>" << endl ;
    Popularization.PrintHTML(f) ; ;
  }

  if (RReport.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_rr << "</h2>" << endl ;
    RReport.PrintHTML(f) ; ;
  }

  if (Misc.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_misc << "</h2>" << endl ;
    Misc.PrintHTML(f) ; ;
  }

  if (B.cnf->language==LANGUAGE1)
  {
    if (These.LEntry.NbElement() !=0)
    {
      f << "<h2>" << B.cnf->category_phd << "</h2>" << endl ;
      These.PrintHTML(f) ;
    }

  }
  if (Master.LEntry.NbElement() !=0)
  {
    f << "<h2>" << B.cnf->category_master << "</h2>" << endl ;
    Master.PrintHTML(f) ;
  }
}



int
CreatePageCategories(CDataBase& B)
{
  int nb =0 ;
  int ok = 1 ;
   B.cnf->SortYearInverse() ;

  if (B.cnf->language1)
    B.cnf->language = LANGUAGE1 ;
  else
    if (B.cnf->language2)
      B.cnf->language = LANGUAGE2 ;
  while(ok==1)
  {
    ofstream f ;

    string l ;
    if ( B.cnf->language == LANGUAGE1) l = B.cnf->language1_postfix ;
    if ( B.cnf->language == LANGUAGE2) l = B.cnf->language2_postfix ;
    string filename ;
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Journal"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, JOURNAL) ;
    f.close() ;
 filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/JournalNat"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, JOURNALNAT) ;
    f.close() ;
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Conference"+l+B.cnf->html_postfix ;
       suppress_white_and_tab(filename) ;
   if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;

    CreatePageCategory(f,B, INPROCEEDINGS) ;
    f.close() ;
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Theses"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, PHDTHESIS) ;
    f.close() ;
  filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Master"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, MASTERTHESIS) ;
    f.close() ;

    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/RR"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, RR ) ;
    f.close() ;
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Book"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, BOOK) ;
    f.close() ;
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/InBook"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
    if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, INBOOK) ;
    f.close() ;
    if(B.cnf->generate_workshop_pages==true)
    {
      filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Workshop"+l+B.cnf->html_postfix ;
      suppress_white_and_tab(filename) ;
      if (B.cnf->debug) cout << "Open " << filename <<endl ;
      f.open(filename.c_str()) ;
     nb++ ;
     CreatePageCategory(f,B, WORKSHOP) ;
      f.close() ;
    }
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Misc"+l+B.cnf->html_postfix ;
       suppress_white_and_tab(filename) ;
   if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
    nb++ ;
    CreatePageCategory(f,B, MISC) ;
    f.close() ;
    filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Conference_nat"+l+B.cnf->html_postfix ;
       suppress_white_and_tab(filename) ;
   if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
     nb++ ;
   CreatePageCategory(f,B, CONFNAT) ;
    f.close() ;
 filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Invited_conf"+l+B.cnf->html_postfix ;
       suppress_white_and_tab(filename) ;
   if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
     nb++ ;
   CreatePageCategory(f,B, INVITED) ;
    f.close() ;
 filename = B.cnf->directory_base +"/"+B.cnf->directory_category + "/Popularization"+l+B.cnf->html_postfix ;
       suppress_white_and_tab(filename) ;
   if (B.cnf->debug) cout << "Open " << filename <<endl ;
    f.open(filename.c_str()) ;
     nb++ ;
   CreatePageCategory(f,B, POPULARIZATION) ;
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
  B.cnf->SortYear() ;

  return nb ;
}


void
CreatePageCategory(ofstream& f, CDataBase& B, int type)
{
   CDataBase A ;
   //   String S ;
   B.ExtractType(A,type) ;

   if (B.cnf->language==LANGUAGE1)
   {
     B.cnf->category_master =     B.cnf->category_master_language1 ;
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
     B.cnf->category_master =     B.cnf->category_master_language2 ;
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

      PageBegin(f,B.cnf) ;

   f << "<h1> " ;
   switch (type)
   {
   case INPROCEEDINGS:
     f <<  B.cnf->category_conf_internationale << endl ;
     break ;
 case INVITED:
     f <<  B.cnf->category_invited << endl ;
     break ;
case POPULARIZATION:
     f <<  B.cnf->category_popularization << endl ;
     break ;
   case JOURNAL:
     f <<  B.cnf->category_journal << endl ;
     break ;
  case JOURNALNAT:
     f <<  B.cnf->category_journalnat << endl ;
     break ;
   case BOOK:
     f <<   B.cnf->category_book << endl ;
     break ;
   case INBOOK:
     f <<   B.cnf->category_bookchapter<< endl ;
     break ;
   case RR:
     f << B.cnf->category_rr << endl ;
     break ;
   case PHDTHESIS:
     f <<  B.cnf->category_phd  << endl ;
     break ;
   case MASTERTHESIS:
     f <<  B.cnf->category_master  << endl ;
     break ;
   case WORKSHOP:
     f << B.cnf->category_conf_workshop << endl ;
     break ;
   case CONFNAT:
     f << B.cnf->category_conf_nationale << endl ;
     break ;
   case MISC:
     f <<  B.cnf->category_misc << endl ;
     break ;
   }
   f <<  "</h1>" <<endl ;
   B.cnf->LYear.Front() ;
   while (!B.cnf->LYear.Outside())
   {
     CDataBase DByear ;
     int year = B.cnf->LYear.Value() ;
     A.ExtractYear(DByear,year) ;

     if (DByear.LEntry.NbElement() != 0)
     {
       DByear.SortYear() ;

       f << "<h2> "<< year <<"</h2>" << endl ;

       DByear.PrintHTML(f) ; ;
     }
     B.cnf->LYear.Next() ;
   }


  PageEnd(f,B.cnf) ;


}

void
CountEntries(CDataBase &B)
{
  CDataBase These ;
  CDataBase Master ;
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
  
  {
    B.ExtractType(Book,BOOK) ; 
    B.ExtractType(These,PHDTHESIS) ; 
    B.ExtractType(Master,MASTERTHESIS) ;
    B.ExtractType(Journal,JOURNAL) ;
    B.ExtractType(Invited,INVITED) ;
    B.ExtractType(JournalNat,JOURNALNAT) ;
    B.ExtractType(Chapter,INBOOK) ;
    B.ExtractType(Conf,INPROCEEDINGS) ;
    B.ExtractType(Workshop,WORKSHOP) ;
    B.ExtractType(Confnat,CONFNAT) ;
    B.ExtractType(Misc,MISC) ;
    B.ExtractType(RReport,RR) ;
    B.ExtractType(Popularization,POPULARIZATION) ;

    B.cnf->nb_conf_nationale = Confnat.LEntry.NbElement() ;
    B.cnf->nb_misc = Misc.LEntry.NbElement() ;
    B.cnf->nb_rr = RReport.LEntry.NbElement() ;
    B.cnf->nb_popularization = Popularization.NbEntries() ;
    B.cnf->nb_book = Book.NbEntries() ;
    B.cnf->nb_conf_workshop = Workshop.NbEntries() ;
    B.cnf->nb_conf_internationale = Conf.NbEntries() ;
    B.cnf->nb_bookchapter = Chapter.NbEntries() ;
    B.cnf->nb_invited = Invited.NbEntries() ;
    B.cnf->nb_journal = Journal.LEntry.NbElement() ;
    B.cnf->nb_journalnat = JournalNat.LEntry.NbElement() ;
    B.cnf->nb_master = Master.NbEntries() ;
    B.cnf->nb_phd = These.NbEntries() ;
 }

}

