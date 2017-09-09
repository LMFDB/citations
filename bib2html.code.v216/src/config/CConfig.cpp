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
#include <tools/String.h>

#define DEBUG_LEVEL1 1
#define DEBUG_LEVEL2 0


//-------------------------------------------------------------------
CString&
CString::operator=( CString &f)
{
  key = f.key ;
  st = f.st ;
  return *this ;
}

CString::CString( CString& f)
{
  *this = f ;
}

//-------------------------------------------------------------------
CMonth&
CMonth::operator=( CMonth &f)
{
  n = f.n ;
  month = f.month ;
  return *this ;
}



CMonth::CMonth( CMonth& f)
{
  n = f.n ;
  month = f.month ;
}

CMonth::CMonth(int _n, const string &_m)
{
  n = _n ;
  month = _m ;
}

void
CMonth::Set(int _n, const string &_m)
{
  n = _n ;
  month = _m ;
}

//-------------------------------------------------------------------
CConfigAuthor&
CConfigAuthor::operator=( CConfigAuthor &f)
{
   name = f.name;
   given_name = f.given_name;

   url = f.url;
   email = f.email ;
   filename = f.filename;

   I = f.I ;
   return *this ;
}


//-------------------------------------------------------------------
int
CConfigAuthor::operator==( CConfigAuthor &f)
{
  string a1, a2 ;
  a1 = (given_name)[0] ;
  a2 = (f.given_name)[0] ;

  string n1, n2 ;
  n1 = supress_slash(name) ;
  n2 = supress_slash(f.name) ;
  return ((upcase(suppress_white_and_tab(suppressaccent(n1)))== upcase(suppress_white_and_tab(suppressaccent(n2))))  &&
  	  (upcase(suppressaccent(a1)) == upcase(suppressaccent(a2)))) ;
}



CConfigAuthor::CConfigAuthor( CConfigAuthor& f)
{
  *this = f ;
}


//-------------------------------------------------------------------
CConfigKeyword&
CConfigKeyword::operator=(CConfigKeyword &f)
{
   key = f.key;
   key_language1 = f.key_language1;
   key_language2 = f.key_language2;

   return *this ;
}

//-------------------------------------------------------------------
int
CConfigKeyword::operator==(CConfigKeyword &f)
{
  return ((upcase(key)== upcase(key))) ;
}

//-------------------------------------------------------------------
CConfigKeyword::CConfigKeyword(CConfigKeyword &f)
{
  *this = f ;
}

//-------------------------------------------------------------------
CConfigKeyword::CConfigKeyword(string  &k)
{
  key = k ;
  key_language1 = k ;
  key_language1 = k ;
}

//-------------------------------------------------------------------
int
CConfig::Init()
{
  CMonth m(1,"Janvier") ;  LMonth += m ;
  m.Set(2,"Fevrier") ;  LMonth += m ;
  m.Set(2,"Février") ;  LMonth += m ;
  m.Set(3,"Mars") ;  LMonth += m ;
  m.Set(4,"Avril") ;  LMonth += m ;
  m.Set(5,"Mai") ;  LMonth += m ;
  m.Set(6,"Juin") ;  LMonth += m ;
  m.Set(7,"Juillet") ;  LMonth += m ;
  m.Set(8,"Aout") ;  LMonth += m ;
  m.Set(8,"Août") ;  LMonth += m ;
  m.Set(9,"Septembre") ;  LMonth += m ;
  m.Set(10,"Octobre") ;  LMonth += m ;
  m.Set(11,"Novembre") ;  LMonth += m ;
  m.Set(12,"Décembre") ;  LMonth += m ;
  m.Set(12,"Decembre") ;  LMonth += m ;

  m.Set(1,"January") ;  LMonth += m ;
  m.Set(2,"February") ;  LMonth += m ;
  m.Set(3,"March") ;  LMonth += m ;
  m.Set(1,"Jan") ;  LMonth += m ;
  m.Set(2,"Feb") ;  LMonth += m ;
  m.Set(3,"Mar") ;  LMonth += m ;
  m.Set(4,"Apr") ;  LMonth += m ;
  m.Set(4,"April") ;  LMonth += m ;
  m.Set(5,"May") ;  LMonth += m ;
  m.Set(6,"June") ;  LMonth += m ;
  m.Set(7,"July") ;  LMonth += m ;
  m.Set(7,"Jul") ;  LMonth += m ;
  m.Set(8,"August") ;  LMonth += m ;
  m.Set(9,"September") ;  LMonth += m ;
  m.Set(10,"October") ;  LMonth += m ;
  m.Set(11,"November") ;  LMonth += m ;
  m.Set(12,"December") ;  LMonth += m ;
  m.Set(6,"Jun") ;  LMonth += m ;
  m.Set(8,"Augt") ;  LMonth += m ;
  m.Set(8,"Aug") ;  LMonth += m ;
  m.Set(9,"Sept") ;  LMonth += m ;
  m.Set(9,"Sep") ;  LMonth += m ;
  m.Set(10,"Oct") ;  LMonth += m ;
  m.Set(11,"Nov") ;  LMonth += m ;
  m.Set(12,"Déc") ;  LMonth += m ;
  m.Set(12,"Dec") ;  LMonth += m ;


  month_f[1]="Janvier" ;
  month_f[2]="Février" ;
  month_f[3]="Mars" ;
  month_f[4]="Avril" ;
  month_f[5]="Mai" ;
  month_f[6]="Juin" ;
  month_f[7]="Juillet" ;
  month_f[8]="Août" ;
  month_f[9]="Septembre" ;
  month_f[10]="Octobre" ;
  month_f[11]="Novembre" ;
  month_f[12]="Décembre" ;


  month_e[1]="January" ;
  month_e[2]="February" ;
  month_e[3]="March" ;
  month_e[4]="April" ;
  month_e[5]="May" ;
  month_e[6]="June" ;
  month_e[7]="July" ;
  month_e[8]="August" ;
  month_e[9]="September" ;
  month_e[10]="October" ;
  month_e[11]="November";
  month_e[12]="December";

  page_footer_language1 = "" ;
  page_header_language1 = "" ;
  page_footer_language2 = "" ;
  page_header_language2 = "" ;

  tex_postfix = ".tex";
  html_postfix = ".html";
  language2_postfix = "-fra" ;
  language1_postfix = "-eng";

  bibtex_link=true ;
  page_start_language1  ="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"        \"http://www.w3.org/TR/html4/loose.dtd\"> <html>";
  page_start_language2  ="<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"        \"http://www.w3.org/TR/html4/loose.dtd\"> <html>";


  page_end_language1   ="</html>";
  page_end_language2   ="</html>";

  page_header_language1  ="<body>";
  page_footer_language1  ="</body>" ;
  page_header_language2  ="<body>";
  page_footer_language2  ="</body>" ;

  page_acknowledgment = "<p> This document was translated automatically from BibTEX by <a href=\"http://www.irisa.fr/prive/marchand/bib2html\">bib2html</a> (Copyright 2003 &copy Eric Marchand, INRIA, Vista  Project).</body>" ;

  unsigned int pos ;
  pos =  page_footer_language1.find("</body>") ;
  if (pos != string::npos)
  {
    page_footer_language1.erase(pos,7) ;
  }
  page_footer_language1.append(page_acknowledgment) ;

  pos =  page_footer_language2.find("</body>") ;
  if (pos != string::npos)
  {
    page_footer_language2.erase(pos,7) ;
  }
  page_footer_language2.append(page_acknowledgment) ;

 /*
  name_start ="" ;
  name_end  ="";

  title_journal_start  = "<b>" ;
  title_journal_end  = "</b>" ;

  title_inproc_start  = "<b>" ;
  title_inproc_end  = "</b>" ;

  title_book_start = "<b>";
  title_book_end  = "</b>";

  journal_start = "<em>";
  journal_end  = "</em>";

  booktitle_start = "<em>";
  booktitle_end  = "</em>";
 */

  list_start ="<ol>";
  list_item ="<li>";
  list_end ="</ol>";


  copyright_notice_language2 ="Les documents contenus dans ces répertoires sont rendus disponibles par les auteurs qui y ont contribué en vue d'assurer la diffusion à temps de travaux savants et techniques sur une base non-commerciale. Les droits de copie et autres droits sont gardés par les auteurs et par les détenteurs du copyright, en dépit du fait qu'ils présentent ici leurs travaux sous forme électronique. Les personnes copiant ces informations doivent adhérer aux termes et contraintes couverts par le copyright de chaque auteur. Ces travaux ne peuvent pas être rendus disponibles ailleurs sans la permission explicite du détenteur du copyright.";

  copyright_notice_language1  = "This material is presented to ensure timely dissemination of scholarly and   technical work. Copyright and all rights therein are retained by authors or   by other copyright holders. All persons copying this information are expected   to adhere to the terms and constraints invoked by each author's   copyright. These works may not be reposted without the explicit permission of   the copyright holder.";

  index_filename = "index" ;
  title_index_language2 = "Publications" ;
  title_index_language1 = "Publications" ;

  category_phd_language2 = "Thèses";
  category_master_language2 = "Rapports de Master";
  master_language2 = "Rapport de master";
  category_journal_language2 = "Articles de journaux";
  category_book_language2 = "Livres";
  category_bookchapter_language2 = "Chapitres de livres";
  category_conf_internationale_language2 = " Conférences Internationales";
  category_conf_nationale_language2  = "Conférences nationales ";
  category_conf_workshop_language2 = "Workshops et symposiums";
  category_rr_language2 = "Rapports de recherche";
  category_misc_language2 = "Divers";
  category_invited_language2 = "Conférences invitées" ;
  category_popularization_language2 =  "Culture scientifique / vulgarisation" ;
  category_journalnat_language2 =  "Articles de journaux nationaux" ;


  category_phd_language1 = "Thesis";
  category_master_language1 = "Master's thesis";
  master_language1 = "Master's theses";
  category_journal_language1 = " Academic Journals";
  category_book_language1 = "Books";
  category_bookchapter_language1 = "Book Chapters";
  category_conf_internationale_language1 = "International Conferences";
  category_conf_nationale_language1 = "National Conferences";
  category_conf_workshop_language1  = "Workshops and Symposiums";
  category_rr_language1  = "Research Reports";
  category_misc_language1 = "Misc";
  category_invited_language1 = "Invited Conferences" ;
  category_popularization_language1 =  "Scientific Popularization" ;
  category_journalnat_language1 =  "Academic Journals (National audience)" ;


  category_phd =     category_phd_language1 ;
  category_master =     category_master_language1 ;
  category_journal =     category_journal_language1 ;
  category_book =    category_book_language1 ;
  category_bookchapter = category_bookchapter_language1 ;
  category_conf_internationale = category_conf_internationale_language1 ;
  category_conf_nationale =  category_conf_nationale_language1 ;
  category_conf_workshop  =  category_conf_workshop_language1  ;
  category_rr  = category_rr_language1  ;
  category_misc =  category_misc_language1 ;
  category_invited =  category_invited_language1 ;
  category_journalnat =category_journalnat_language1 ;
  category_popularization = category_popularization_language1 ;

  language1 = true ;
  language2 = true ;
  language = FRENCH ;
  html = true ;
  verbose =true ;
  debug =false ;
  last_modified =false ;

  check_url = true;
  check_pdf = true ;
  check_abstract = true ;

  author_create_pages  = true;
  category_create_pages  = true;
  keyword_create_pages  = true;
  year_create_pages = true ;
  biblio_create_pages = true ;
  create_pages_all = true ;
  create_pages_tex = true ;
  generate_national_journals_pages = true;
  generate_national_conferences_pages = true;
  generate_workshop_pages = false ;
  generate_popularization_pages = false ;
  generate_invited_pages = false ;
  generate_rr_pages = true ;

 
  base_http = "/tmp/";
  directory_base = "/tmp/";
  directory_author = "Author/";
  directory_keyword = "Keyword/";
  directory_year = "Year/";
  directory_category = "Category/";
  directory_ps = "Papers/";
  directory_publi = "Publi/";
  directory_all = "All/";
  directory_bibtex = "Bibtex/";

  url_icon_arxiv = "" ;
  url_icon_ppt = "" ;
  url_icon_word = "" ;
  url_icon_key = "" ;
  url_icon_compressed = "" ;
  url_icon_html = "" ;
  url_icon_ps = "" ;
  url_icon_pdf = "" ;
  url_icon_abstract = "" ;
  url_icon_doi = "" ;
  url_download_help ="" ;

  no_head_no_foot = true ;

  all_author = true ;
  all_keyword = true ;

  //  workshop = false ;

  //-------------------------------------------------------------------
  // Tex Stuff
  tex = true ;

  item_key_tex = true ;

  list_start_tex ="bibli";
  list_item_tex ="\\next";
  list_end_tex ="bibli";
  directory_tex = "./" ;

  //-------------------------------------------------------------------

  return OK ;

}


CConfig::CConfig()
{
  Init() ;
}


CConfig::CConfig(const char *name)
{
  Init() ;
  LoadConfiguration(name) ;
}

CConfig::~CConfig()
{
  LMonth.Kill() ;
  LBibfile.Kill() ;
  LAuthor.Kill() ;

  LYear.Kill() ;
  LKeyword.Kill() ;
  LString.Kill() ;
}
int
CConfig::LoadConfiguration(const char *name)
{
  return MergeConfiguration(name) ;
}

int
CConfig::MergeConfiguration(const char *name)
{
  ifstream f(name) ;
  cout << "Open " << name << endl ;
  if (f==NULL) {cout <<"Cannot open " << name <<endl ; return -1 ; }
  while(!f.eof())
    ReadNextEntry(f) ;
  f.close() ;
  cout << "---------------------------------" << endl ;


  return OK ;
}



static int
GetTypeOfEntry(string &s)
{
  int type ;
  type = ENTRY_NOT_DEFINED ;
  if (instring(s,"@DEFINE{"))
    type = DEFINE ;
  else
    if (instring(s,"@AUTHOR{"))
      type = AUTHOR ;
    else
      if (instring(s,"@YEAR{"))
	type = YEAR ;
      else
	if (instring(s,"@MONTH{"))
	  type = MONTH ;
	else
	  if (instring(s,"@BIBFILE{"))
	    type = BIBFILE ;
	  else
	    if (instring(s,"@CONFIGFILE{"))
	      type = CONFIGFILE ;
	    else
	      if ((instring(s,"@KEYWORD{"))||( instring(s,"@KEYWORDS{")))
		type = KEYWORD ;
	      else
	      {
		cout << "Error  " <<  s << "not define " << endl ;
	      }
  return type ;
}


int
CConfig::ReadNextEntry(istream &f)
{

  string ligne ;
  int type_of_entry = ENTRY_NOT_DEFINED;
  // on recherche le prochain @ du fichier
  bool find_entry_marker = false ;
  while (find_entry_marker == false )
  {
    // lit une ligne
    getline(f,ligne,'\n') ;
    if (f.eof()) return OK  ;
    if (DEBUG_LEVEL2) cout << "Lecture ligne : [ "<< ligne << " ] "<<endl ;
    for (unsigned int i=0 ; i < ligne.length() ; i++)
    {
      if (ligne[i] == '@')
      {
	string us = upcase(ligne) ;
	type_of_entry  = GetTypeOfEntry(us) ;
	if (type_of_entry != ENTRY_NOT_DEFINED) find_entry_marker = true ;
      }
    }
  }

  // On doit chercher ce qu'il y a entre les deux prochaines { }
  string s ;
  s = ligne  + '\n';
  int nbbrace = count(s,'{') - count(s,'}') ;

  while (nbbrace!=0)
  {
    getline(f,ligne,'\n') ;
    if (f.eof()) return OK  ;
    nbbrace += count(ligne,'{') - count(ligne,'}') ;
    s += ligne   + '\n' ;
  }

  if (   find_entry_marker == true)
  {
    if (type_of_entry == DEFINE) ExtractString(s) ;
    if (type_of_entry == AUTHOR)
    {
      all_author = false ;
      ExtractAuthor(s) ;
    }
    if (type_of_entry == YEAR) ExtractYear(s) ;
    if (type_of_entry == MONTH) ExtractMonth(s) ;
    if (type_of_entry == KEYWORD)
    {
      all_keyword = false ;
      ExtractKeyword(s) ;
    }
    if (type_of_entry == BIBFILE) ExtractBibFile(s) ;
    if (type_of_entry == CONFIGFILE) ExtractConfigFile(s) ;
  }
  return 1 ;
}

int
CConfig::ExtractString(string &s)
{

  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;
  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;

  unsigned int pos ;
  pos = s_config.find("=",0) ;

  string tmp ;
  if (pos != string::npos)
  {
    before(s_config,"=",key) ;
    key = suppress_white_and_tab(key) ;
    beforelast(s_config,"}", s_config) ;

    after(s_config,"=", tmp) ;

  }
  else
  {
    beforelast(s_config,"}", key) ;
    key = suppress_white_and_tab(key) ;
  }

  if (key == "file_css")
      file_css = suppress_white_and_tab(tmp) ;

  //  css = "<link rel=STYLESHEET type=\"text/css\" HREF=\""+file_css +"\">" ;
  css = "<link rel=STYLESHEET  HREF=\""+file_css +"\">" ;

    //  cout << css << endl ;
  if (key == "directory.base")
    directory_base = suppress_white_and_tab(tmp) ;
  if (key == "base.http")
    base_http = suppress_white_and_tab(tmp) ;
  if (key == "directory.config")
    directory_config = suppress_white_and_tab(tmp) ;
  if (key == "directory.author")
    directory_author = suppress_white_and_tab(tmp) ;
  if (key == "directory.keyword")
    directory_keyword = suppress_white_and_tab(tmp) ;
  if (key == "directory.keywords")
    directory_keyword = suppress_white_and_tab(tmp) ;
  if (key == "directory.year")
    directory_year = suppress_white_and_tab(tmp) ;
  if (key == "directory.category")
    directory_category = suppress_white_and_tab(tmp) ;
  if (key == "directory.ps")
    directory_ps = suppress_white_and_tab(tmp) ;
  if (key == "directory.publi")
    directory_publi = suppress_white_and_tab(tmp) ;
  if (key == "directory.all")
    directory_all = suppress_white_and_tab(tmp) ;
  if (key == "directory.tex")
    directory_tex = suppress_white_and_tab(tmp) ;
  if (key == "directory.bibtex")
    directory_bibtex = suppress_white_and_tab(tmp) ;
  if (key == "url.download.help")
    url_download_help = suppress_white_and_tab(tmp) ;

  if (directory_author.length()==0) directory_author = "/./" ;
  if (directory_keyword.length()==0) directory_author = "/./" ;
  if (directory_publi.length()==0) directory_author=  "/./" ;
  if (directory_category.length()==0) directory_author=  "/./" ;
  if (directory_year.length()==0) directory_author=  "/./" ;
  if (directory_bibtex.length()==0) directory_author=  "/./" ;
  if (directory_all.length()==0) directory_author=  "/./" ;
  if (directory_tex.length()==0) directory_author=  "/./" ;



  // title.index
  if (key == "title.index.french")
    title_index_language2 = tmp ;
  if (key == "title.index.language2")
    title_index_language2 = tmp ;
  if (key == "title.index.english")
    title_index_language1 = tmp ;
  if (key == "title.index.language1")
    title_index_language1 = tmp ;
  if (key == "index.filename.language1")
    title_index_language1 = tmp ;
  if (key == "index.filename.language2")
    title_index_language2 = tmp ;
  if (key == "index.filename")
    title_index_language1 = tmp ;

  // page.start
  if (key == "page.start")
    page_start_language1 = tmp ;
  if (key == "page.start.english")
    page_start_language1 = tmp ;
  if (key == "page.start.french")
    page_start_language2 = tmp ;
  if (key == "page.start.language1")
    page_start_language1 = tmp ;
  if (key == "page.start.language2")
    page_start_language2 = tmp ;

  // page.end
  if (key == "page.end")
    page_end_language1 = tmp ;
  if (key == "page.end.english")
    page_end_language1 = tmp ;
  if (key == "page.end.french")
    page_end_language2 = tmp ;
  if (key == "page.end.language1")
    page_end_language1 = tmp ;
  if (key == "page.end.language2")
    page_end_language2 = tmp ;


  // page.footer
  if (key == "page.footer")
    page_footer_language1 = tmp ;
  if (key == "page.footer.english")
    page_footer_language1 = tmp ;
  if (key == "page.footer.french")
    page_footer_language2 = tmp ;
  if (key == "page.footer.language1")
    page_footer_language1 = tmp ;
  if (key == "page.footer.language2")
    page_footer_language2 = tmp ;


  // page.header
  if (key == "page.header")
    page_header_language1 = tmp ;
  if (key == "page.header.english")
    page_header_language1 = tmp ;
  if (key == "page.header.french")
    page_header_language2 = tmp ;
  if (key == "page.header.language1")
    page_header_language1 = tmp ;
  if (key == "page.header.language2")
    page_header_language2 = tmp ;


  pos =  page_footer_language1.find("</body>") ;
  if (pos != string::npos)
  {
    page_footer_language1.erase(pos,7) ;
  }
  page_footer_language1.append(page_acknowledgment) ;

  pos =  page_footer_language2.find("</body>") ;
  if (pos != string::npos)
  {
    page_footer_language2.erase(pos,7) ;
  }
  page_footer_language2.append(page_acknowledgment) ;

  if (key == "category.phd.french")
    { 
      cout << "deprecated " << endl ;
      category_phd_language2=tmp ;
    }
  if ((key == "category.masters.french")
      || (key == "category.master.french"))
    category_master_language2=tmp ;
  if (key == "category.journal.french")
    category_journal_language2=tmp ;
  if (key == "category.book.french")
    category_book_language2=tmp ;
  if (key == "category.bookchapter.french")
    category_bookchapter_language2=tmp ;
  if (key == "category.conf.internationale.french")
    category_conf_internationale_language2=tmp ;
  if (key == "category.conf.nationale.french")
    category_conf_nationale_language2=tmp ;
  if (key == "category.conf.workshop.french")
    category_conf_workshop_language2=tmp ;
  if (key == "category.rr.french")
    category_rr_language2=tmp ;
  if (key == "category.misc.french")
    category_misc_language2=tmp ;

  if (key == "category.phd.language2")
    category_phd_language2=tmp ;
  if ((key == "category.masters.language2")
      || (key == "category.master.language2"))
    category_master_language2=tmp ;
  if (key == "category.journal.language2")
    category_journal_language2=tmp ;
  if (key == "category.book.language2")
    category_book_language2=tmp ;
  if (key == "category.bookchapter.language2")
    category_bookchapter_language2=tmp ;
  if (key == "category.conf.internationale.language2")
    category_conf_internationale_language2=tmp ;
  if (key == "category.conf.nationale.language2")
    category_conf_nationale_language2=tmp ;
  if (key == "category.conf.workshop.language2")
    category_conf_workshop_language2=tmp ;
  if (key == "category.rr.language2")
    category_rr_language2=tmp ;
  if (key == "category.misc.language2")
    category_misc_language2=tmp ;
 if (key == "category.invited.language2")
    category_invited_language2=tmp ;
 if (key == "category.journalnat.language2")
    category_journalnat_language2=tmp ;
 if (key == "category.popularization.language2")
    category_popularization_language2=tmp ;




  if (key == "category.phd.language1")
    category_phd_language1=tmp ;
  if ((key == "category.master.language1")
      || (key == "category.masters.language1"))
    category_master_language1=tmp ;
  if (key == "category.journal.language1")
    category_journal_language1=tmp ;
  if (key == "category.book.language1")
    category_book_language1=tmp ;
  if (key == "category.bookchapter.language1")
    category_bookchapter_language1=tmp ;
  if (key == "category.conf.internationale.language1")
    category_conf_internationale_language1=tmp ;
  if (key == "category.conf.nationale.language1")
    category_conf_nationale_language1=tmp ;
  if (key == "category.conf.workshop.language1")
    category_conf_workshop_language1 =tmp ;
  if (key == "category.rr.language1")
    category_rr_language1 =tmp ;
  if (key == "category.misc.language1")
    category_misc_language1=tmp ;

 if (key == "category.invited.language1")
    category_invited_language1=tmp ;
 if (key == "category.journalnat.language1")
    category_journalnat_language1=tmp ;
 if (key == "category.popularization.language1")
    category_popularization_language1=tmp ;


  if ((key == "category.master.english") || (key == "category.masters.english"))
    category_master_language1=tmp ;
  if (key == "category.journal.english")
    {
      cout << "category.journal.english deprecated" <<endl ;
      category_journal_language1=tmp ;
    }
  if (key == "category.book.english")
    category_book_language1=tmp ;
  if (key == "category.bookchapter.english")
    category_bookchapter_language1=tmp ;
  if (key == "category.conf.internationale.english")
    category_conf_internationale_language1=tmp ;
  if (key == "category.conf.nationale.english")
    category_conf_nationale_language1=tmp ;
  if (key == "category.conf.workshop.english")
    category_conf_workshop_language1 =tmp ;
  if (key == "category.rr.english")
    category_rr_language1 =tmp ;
  if (key == "category.misc.english")
    category_misc_language1=tmp ;


  if (key == "french.postfix")
    language2_postfix=suppress_white_and_tab(tmp) ;
  if (key == "language2.postfix")
    language2_postfix=suppress_white_and_tab(tmp) ;

  if (key == "english.postfix")
    language1_postfix=suppress_white_and_tab(tmp) ;
  if (key == "language1.postfix")
    language1_postfix=suppress_white_and_tab(tmp) ;


 if (key == "master.french")
    master_language2=tmp ;
 if (key == "master.language2")
    master_language2=tmp ;
 if (key == "master.language1")
    master_language1=tmp ;
 if (key == "master.english")
    master_language1=tmp ;

  if (key == "html.postfix")
    html_postfix=suppress_white_and_tab(tmp) ;


  if (key=="list.start")   list_start = tmp ;
  if (key=="list.item")     list_item = tmp ;
  if (key=="list.end")     list_end = tmp ;

  if ( (key == "name.start")   ||
       (key == "name.end")     ||

       (key=="title.journal.start") ||
       (key=="title.journal.end" )||
       (key=="title.inproc.start")||
       (key=="title.inproc.end")||

       (key=="title.book.start")||
       (key=="title.book.end")||
       (key=="journal.start")||
       (key=="journal.end")||
       (key=="booktitle.start")||
       (key=="booktitle.end"))
    cout << "   Using " << key <<" is obsolete, use CSS style file " << endl ;

  if (key=="copyright.notice") copyright_notice_language1 = tmp ;
  if (key=="copyright.notice.english") copyright_notice_language1 = tmp ;
  if (key=="copyright.notice.language1") copyright_notice_language1 = tmp ;
  if (key=="copyright.notice.french") copyright_notice_language2 = tmp ;
  if (key=="copyright.notice.language2") copyright_notice_language2 = tmp ;

  if (key=="url.icon.key") url_icon_key = tmp ;
  if (key=="url.icon.compressed") url_icon_compressed = tmp ;
  if (key=="url.icon.Z") url_icon_compressed = tmp ;
  if (key=="url.icon.gz") url_icon_compressed = tmp ;
  if (key=="url.icon.winzip") url_icon_compressed = tmp ;
  if (key=="url.icon.html") url_icon_html = tmp ;
  if (key=="url.icon.ps") url_icon_ps = tmp ;
  if (key=="url.icon.pdf") url_icon_pdf = tmp ;
  if (key=="url.icon.doi") url_icon_doi = tmp ;
  if (key=="url.icon.details") url_icon_abstract = tmp ;
  if (key=="url.icon.more") url_icon_abstract = tmp ;
  if (key=="url.icon.abstract") url_icon_abstract = tmp ;
  if (key=="url.icon.powerpoint") url_icon_ppt = tmp ;
  if (key=="url.icon.arxiv") url_icon_arxiv = tmp ;
  if (key=="url.icon.ppt") url_icon_ppt = tmp ;
  if (key=="url.icon.word") url_icon_word = tmp ;
  if (key=="url.icon.doc") url_icon_word = tmp ;

  if (key =="no.head.no.foot") no_head_no_foot = true ;
  if (key =="no.head.no.foot.yes") no_head_no_foot = true ;
  if (key =="no.head.no.foot.no") no_head_no_foot = false ;


  if (key =="french") language2 = true ;
  if (key =="language2") language2 = true ;
  if (key =="french.yes") language2 = true ;
  if (key =="language2.yes") language2 = true ;
  if (key =="french.no")  language2= false ;
  if (key =="language2.no") language2 = false ;


  if (key =="english") language1 = true ;
  if (key =="language1") language1 = true ;
  if (key =="english.yes") language1 = true ;
  if (key =="language1.yes") language1 = true ;
  if (key =="english.no") language1 = false ;
  if (key =="language1.no") language1 = false ;
  if (key =="bibtex.no") bibtex_link = false ;
  if (key =="bibtex.yes") bibtex_link = true ;
  if (key =="bibtex.link") bibtex_link = false ;

  if ((key =="author.create.pages") && ( instring(tmp,"false")))
   {
     author_create_pages  = false ;
     all_author = false ;
   }
   if ((key =="author.create.pages") && ( instring(tmp,"true")))
     author_create_pages  = true ;

   if (key =="author.create.pages.no")  {
     author_create_pages  = false ;
     all_author = false ;
   }
   if (key =="author.create.pages.yes")  author_create_pages  = true ;

   if ((key =="year.create.pages") && ( instring(tmp,"false")))
     year_create_pages  = false ;

   if ((key =="year.create.pages") && ( instring(tmp,"true")))
     year_create_pages  = true ;

   if (key =="year.create.pages.no")  year_create_pages  = false ;
   if (key =="year.create.pages.yes")  year_create_pages  = true ;

   if ((key =="workshop") && ( instring(tmp,"false")))  
     generate_workshop_pages  = false ;
   if ((key =="workshop") && ( instring(tmp,"true")))  
     generate_workshop_pages  = true ;

   if (key =="workshop.no")  generate_workshop_pages  = false ;
   if (key =="workshop.yes") generate_workshop_pages  = true ;

   if (key =="generate.workshop.pages.no")  generate_workshop_pages  = false ;
   if (key =="generate.workshop.pages.yes") generate_workshop_pages  = true ;

   if (key =="generate.national.conferences.pages.no")
     generate_national_conferences_pages  = false ;
   if (key =="generate.national.conferences.pages.yes")
     generate_national_conferences_pages  = true ; 
   if (key =="national.conferences.no") 
     generate_national_conferences_pages  = false ;
   if (key =="national.conferences.yes")
     generate_national_conferences_pages  = true ;

   if (key =="generate.national.journals.pages.no")  
     generate_national_journals_pages  = false ;
   if (key =="generate.national.journals.pages.yes") 
     generate_national_journals_pages  = true ; 
   if (key =="national.journals.no")  
     generate_national_journals_pages  = false ;
   if (key =="national.journals.yes") 
     generate_national_journals_pages  = true ;

 if (key =="generate.popularization.pages.no")  
     generate_popularization_pages  = false ;
   if (key =="generate.popularization.pages.yes") 
     generate_popularization_pages  = true ; 
   if (key =="popularization.no")  
     generate_popularization_pages  = false ;
   if (key =="popularization.yes") 
     generate_popularization_pages  = true ;

 if (key =="generate.invited.pages.no")      generate_invited_pages  = false ;
   if (key =="generate.invited.pages.yes")   generate_invited_pages  = true ; 
   if (key =="invited.no")       generate_invited_pages  = false ;
   if (key =="invited.yes")      generate_invited_pages  = true ;

   if (key =="generate.rr.pages.no")       generate_rr_pages  = false ;
   if (key =="generate.rr.pages.yes")     generate_rr_pages  = true ; 
   if (key =="rr.no")       generate_rr_pages  = false ;
   if (key =="rr.yes")      generate_rr_pages  = true ;

   if ((key =="category.create.pages") && ( instring(tmp,"false")))
     category_create_pages  = false ;
   if ((key =="category.create.pages") && ( instring(tmp,"true")))
     category_create_pages  = true ;
   if (key =="category.create.pages.no")  category_create_pages  = false ;
   if (key =="category.create.pages.yes")  category_create_pages  = true ;

   if ((key =="keyword.create.pages") && ( instring(tmp,"false")))
     keyword_create_pages  = false ;
   if ((key =="keyword.create.pages") && ( instring(tmp,"true")))
     keyword_create_pages  = true ;
   if (key =="keyword.create.pages.no")  keyword_create_pages  = false ;
   if (key =="keyword.create.pages.yes")  keyword_create_pages  = true ;

   if ((key =="biblio.create.pages") && ( instring(tmp,"false")))
     biblio_create_pages  = false ;
   if ((key =="biblio.create.pages") && ( instring(tmp,"true")))
     biblio_create_pages  = true ;

   if (key =="biblio.create.pages.no")  biblio_create_pages  = false ;
   if (key =="biblio.create.pages.yes")  biblio_create_pages  = true ;


   //-------------------------------------------------------------------
   //  Tex Stuff
   if ((key =="tex") && ( instring(tmp,"true")))  tex = true ;
   if (key == "tex")     tex = true ;
   if (key == "tex.yes") tex = true ;
   if (key == "tex.no") tex = false ;
   if (key == "last.modified.no")  last_modified = false ;
   if (key == "last.modified.yes")  last_modified = true ;


   if (key == "check.url.no")  check_url = false ;
   if (key == "check.url.yes")  check_url = true ;
   if (key == "check.url")  check_url = true ;


   if (key == "check.pdf.no")  check_pdf = false ;
   if (key == "check.pdf.yes")  check_pdf = true ;
   if (key == "check.pdf")  check_pdf = true ;


   if (key == "check.abstract.no")  check_abstract = false ;
   if (key == "check.abstract.yes")  check_abstract = true ;
   if (key == "check.abstract")  check_abstract = true ;


   if (key == "check.doi.no")  check_doi = false ;
   if (key == "check.doi.yes")  check_doi = true ;
   if (key == "check.doi")  check_doi = true ;

   if (key == "check.pages.no")  check_pages = false ;
   if (key == "check.pages.yes")  check_pages = true ;
   if (key == "check.pages")  check_pages = true ;


   if (key=="list.item.key")         item_key_tex = true ;
   if (key=="list.item.key.true")    item_key_tex = true ;
   if (key=="list.item.key.false")   item_key_tex = false ;


  if (key=="list.start.tex")   list_start = tmp ;
  if (key=="list.item.tex")    list_item = tmp ;
  if (key=="list.end.tex")     list_end = tmp ;
   //-------------------------------------------------------------------

  if (debug)    cout << "Key : " << key <<endl ;

  return OK ;
}

int
CConfig::ExtractAuthor(string &s)
{

  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;

  gsub(s_config,RC," ") ;

  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;
  beforelast(s_config,"}",s_config) ;

  CConfigAuthor a ;


  while(suppress_white_and_tab(s_config).length()!=0)
  {
    string tag ; before(s_config,"=",tag) ;
    after(s_config,"=",s_config) ;
    if (upcase(suppress_white_and_tab(tag)) == "NAME")
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.name) ;
	after(s_config,",",s_config) ;
      }
      else
      {	a.name = s_config ;   ;break ; }

    }
    if (upcase(suppress_white_and_tab(tag)) == "GIVENNAME")
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.given_name) ;
	after(s_config,",",s_config) ;
      }
      else
      {	a.given_name = s_config ; break ; }
    }
    if (upcase(suppress_white_and_tab(tag)) == "EMAIL")
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.email) ;
	after(s_config,",",s_config) ;
      }
      else
      { a.email = s_config ; break ; }
    }
    if (upcase(suppress_white_and_tab(tag)) == "FILENAME")
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.filename) ;
	after(s_config,",",s_config) ;
      }
      else
      { a.filename = s_config ; break ; }
    }
    if (upcase(suppress_white_and_tab(tag)) == "URL")
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.url) ;
	after(s_config,",",s_config) ;
      }
      else
      {	a.url=  s_config ; break ;}
    }
  }
  a.name = suppress_white_and_tab(a.name) ;

  // a.given_name =
    suppress_first_and_last_space(a.given_name) ; //suppress_white_and_tab(a.given_name) ;
  a.email = suppress_white_and_tab( a.email) ;
  a.url = suppress_white_and_tab(a.url) ;
  a.filename = suppress_white_and_tab(a.filename) ;

  a.I = upcase(a.given_name)[0] ;
  if (a.I == 'É') a.I = 'E' ;

  LAuthor += a ;

  //  if(debug)
  { cout << "Read New author " ;
    cout << "\t" <<a.name <<"\t" <<a.given_name <<endl ;
    cout << "\t name \t\t" <<a.name <<endl ;
    cout << "\t given name \t\t" <<a.given_name <<endl ;
    cout << "\t email \t\t" <<a.email <<endl ;
    cout << "\t filename \t\t" <<a.filename <<endl ;
    cout << "\t url \t\t" <<a.url <<endl ;
  }

  return OK ;
}

int
CConfig::AddName(CConfigAuthor &n)
{
  //  cout << "begin AddName"<<endl ;
  int find = FALSE ;
  LAuthor.Front() ;
  CConfigAuthor ca ;
  while (!LAuthor.Outside())
  {
    ca = LAuthor.Value() ;
    if (ca==n) { find = TRUE ; break ; }
    LAuthor.Next() ;
  }
  if (find == FALSE) LAuthor += n ;
  //  cout << "end AddName"<<endl ;
  return OK ;
}
int
CConfig::ExtractYear(string &s)
{


  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;

  gsub(s_config,RC," ") ;

  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;
  beforelast(s_config,"}",s_config) ;

  int  a ;
  string tag,tag1 ;

  while(suppress_white_and_tab(s_config).length()!=0)
  {
    if (count(s_config,',') !=0)
    {
      before(s_config,",",tag) ;
      if (instring(tag,"+"))
      {
	before(tag,"+",tag1) ;
	a = atoi(tag1.c_str() ) ;
	ayear =a ;
      }
      else
	if(instring(tag,"-"))
	{
	  before(tag,"-",tag1) ;
	  a = atoi(tag1.c_str() ) ;
	  byear =a ;
	}
	else
	{
	  a = atoi(tag.c_str() ) ; LYear += a ;
	}
      after(s_config,",",s_config) ;
    }
    else
    {
      tag = s_config ;
      if (instring(tag,"+"))
      {
	before(tag,"+",tag1) ;
	a = atoi(tag1.c_str() ) ;
	ayear =a ;
      }
      else
	if(instring(tag,"-"))
	{
	  before(tag,"-",tag1) ;
	  a = atoi(tag1.c_str() ) ;
	  byear =a ;
	}
	else
	{
	  a = atoi(tag.c_str() ) ; LYear += a ;
	}
    //  a = atoi(s_config.c_str()) ; LYear += a ;
     break ;
    }

  }
  return OK ;
}

int
CConfig::ExtractKeyword(string &s)
{


  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;

  gsub(s_config,RC," ") ;

  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;
  beforelast(s_config,"}",s_config) ;

  CConfigKeyword a ;

  between(s_config,"{",",",a.key) ;

  string tmp1 ;
  after(s_config,a.key,tmp1) ;
  after(tmp1,",",s_config) ;

  while(suppress_white_and_tab(s_config).length()!=0)
  {
    string tag ; before(s_config,"=",tag) ;
    after(s_config,"=",s_config) ;
    if ((upcase(suppress_white_and_tab(tag)) == "KEY") ||
	(upcase(suppress_white_and_tab(tag)) == "KEYWORD") )
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.key) ;
	after(s_config,",",s_config) ;
      }
      else
      {	a.key = s_config ;   ;break ; }

    }
    if ((upcase(suppress_white_and_tab(tag)) == "LANGUAGE1")||
	(upcase(suppress_white_and_tab(tag)) == "LG1"))
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.key_language1) ;
	after(s_config,",",s_config) ;
      }
      else
      {	a.key_language1 = s_config ; break ; }
    }
    if ((upcase(suppress_white_and_tab(tag)) == "LANGUAGE2")||
	(upcase(suppress_white_and_tab(tag)) == "LG2"))
    {
      if (count(s_config,',') !=0)
      {
	before(s_config,",",a.key_language2) ;
	after(s_config,",",s_config) ;
      }
      else
      { a.key_language2 = s_config ; break ; }
    }
  }
  a.key = suppress_white_and_tab(a.key) ;

  if (suppress_white_and_tab(a.key_language1).length()==0)
    a.key_language1 = a.key ;
  if (suppress_white_and_tab(a.key_language2).length()==0)
    a.key_language2 = a.key ;

  LKeyword += a ;

  // if(debug)
  {
    cout << "Read New Keyword " ;
    cout << "\t  key \t\t|" <<a.key <<"|\t" << a.key <<endl ;
    cout << "\t lg1 \t\t|" << a.key_language1  <<"|\t"<<endl ;
    cout << "\t lg2 \t\t|" << a.key_language2  <<"|\t" <<endl ;
  }

  return OK ;
}

int
CConfig::AddKeyword(string &n)
{
  //  cout << "begin AddName"<<endl ;
  int find = FALSE ;
  LKeyword.Front() ;

  while (!LKeyword.Outside())
  {
    string ca ;
    ca = upcase(suppress_white_and_tab(LKeyword.Value().key)) ;
    ca = suppressaccent(ca) ;

    string s = upcase(suppress_white_and_tab(n)) ;
    s = suppressaccent(s) ;
    if (ca==s)
    { find = TRUE ; break ; }
    LKeyword.Next() ;
  }
  if (find == FALSE)
  {
    CConfigKeyword k(n) ;
    LKeyword += k ;
  }
  //  cout << "end AddName"<<endl ;
  return OK ;
}
int
CConfig::ExtractConfigFile(string &s)
{

  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;

  gsub(s_config,RC," ") ;

  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;
  beforelast(s_config,"}",s_config) ;

  string configfile ;

  while(suppress_white_and_tab(s_config).length()!=0)
  {
    if (count(s_config,',') !=0)
    {
      before(s_config,",",configfile) ;
      configfile = suppress_white_and_tab(configfile) ;

      cout << "Reading " << configfile  <<endl ;
      char s1[FILENAME_MAX] ;
      sprintf(s1,"%s",configfile.c_str()) ;
      MergeConfiguration(s1) ;
      //      LConfigFile += configfile ;
      after(s_config,",",s_config) ;
    }
    else
    {
      configfile = suppress_white_and_tab(s_config) ;

      char s1[FILENAME_MAX] ;
      sprintf(s1,"%s",configfile.c_str()) ;
      cout << "Reading " << configfile  <<endl ;
      MergeConfiguration(s1) ;
      //      LConfigFile += configfile ;

      break ;
    }

  }


  return OK ;
}

int
CConfig::ExtractBibFile(string &s)
{

  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;

  gsub(s_config,RC," ") ;

  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;
  beforelast(s_config,"}",s_config) ;

  string bibfile ;

  while(suppress_white_and_tab(s_config).length()!=0)
  {
    if (count(s_config,',') !=0)
    {
      before(s_config,",",bibfile) ;
      bibfile = suppress_white_and_tab(bibfile) ;

      cout << "Setting  " << bibfile  <<endl ;
      LBibfile += bibfile ;
      after(s_config,",",s_config) ;
    }
    else
    {
      bibfile = suppress_white_and_tab(s_config) ;
      LBibfile += bibfile ;
      cout << "Setting " << bibfile  <<endl ;

      break ;
    }

  }


  return OK ;
}

int
CConfig::ExtractMonth(string &s)
{

  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;

  gsub(s_config,RC," ") ;

  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;
  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;
  beforelast(s_config,"}",s_config) ;

  string tag ;
  int m ;
  before(s_config,",",tag) ;
  m = atoi(tag.c_str() ) ;

  string  extracted_month ;
  after(s_config,",",s_config) ;

  while(suppress_white_and_tab(s_config).length()!=0)
  {
    if (count(s_config,',') !=0)
    {
      before(s_config,",",extracted_month) ;

      CMonth month(m,upcase(suppress_white_and_tab(extracted_month))) ;
      LMonth += month ;
      after(s_config,",",s_config) ;
    }
    else
    {
      CMonth month(m,upcase(suppress_white_and_tab(extracted_month))) ;
      LMonth += month ;
      break ;
    }
  }

  return OK ;
}

// ce tri n'est abolument pas optimal...
void
CConfig::SortKeyword()
{
  for (int i =0 ; i < LKeyword.NbElement() ; i++)
  {
    LKeyword.Front() ;
    while(!LKeyword.NextOutside()) {
      string s1, s2 ;
      s1 = upcase(suppress_white_and_tab(LKeyword.Value().key )) ;
      s2 =  upcase(suppress_white_and_tab(LKeyword.NextValue().key  ));
      if (s1>s2)
      {
	CConfigKeyword a = LKeyword.Value()  ;
	LKeyword.Suppress() ;
	LKeyword.AddRight(a) ;
      }
      else
	LKeyword.Next() ;
    }
  }
}

// ce tri n'est abolument pas optimal...
void
CConfig::SortAuthor()
{
  for (int i =0 ; i < LAuthor.NbElement() ; i++)
  {
    printf("%d\r",i) ;
    LAuthor.Front() ;
    string s1, s2 ;
    while(!LAuthor.NextOutside()) {
      s1 = upcase(suppress_white_and_tab(LAuthor.Value().name )) ;
      s2 = upcase(suppress_white_and_tab(LAuthor.NextValue().name ));
      if (s1>s2)
      {
	CConfigAuthor a = LAuthor.Value() ;
	LAuthor.Suppress() ;
	LAuthor.AddRight(a) ;
      }
      else
	LAuthor.Next() ;
    }
  }
}

// ce tri n'est abolument pas optimal...
void
CConfig::SortYear()
{
  for (int i =0 ; i < LYear.NbElement() ; i++)
  {
    LYear.Front() ;
    while(!LYear.NextOutside()) {
      int s1, s2 ;
      s1 = LYear.Value() ;
      s2 = LYear.NextValue() ;
      if (s1>s2)
      {
	LYear.Suppress() ;
	LYear.AddRight(s1) ;
      }
      else
	LYear.Next() ;
    }
  }
}

// ce tri n'est abolument pas optimal...
void
CConfig::SortYearInverse()
{
  for (int i =0 ; i < LYear.NbElement() ; i++)
  {
    LYear.Front() ;
    while(!LYear.NextOutside()) {
      int s1, s2 ;
      s1 = LYear.Value() ;
      s2 = LYear.NextValue() ;
      if (s1<s2)
      {
	LYear.Suppress() ;
	LYear.AddRight(s1) ;
      }
      else
	LYear.Next() ;
    }
  }
}
