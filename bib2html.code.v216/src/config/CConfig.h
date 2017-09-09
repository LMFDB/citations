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

#ifndef __CONFIG_HH
#define __CONFIG_HH

#include <fstream>
#include <stdlib.h>

#include <string>
using namespace std ;

#include <tools/CList.h>
#include <include/constant.h>


class CMonth
{
 public:
  int n ;


  string month ;
  CMonth() {;}
  ~CMonth() {;}

  CMonth( CMonth& f) ;
  CMonth& operator=( CMonth &f) ;

  CMonth(int _n, const string &_m) ;
  void Set(int _n, const string &_m) ;
} ;

class CString
{
 public:
  string key ;
  string st ;
  CString() {;}
  ~CString() {;}

  CString( CString& f) ;
  CString& operator=( CString &f) ;
} ;

class CConfigKeyword
{
public:
  string key ;
  string key_language1 ;
  string key_language2 ;

  CConfigKeyword() {;}
  CConfigKeyword( string &k) ;
  CConfigKeyword(CConfigKeyword &f) ;
  CConfigKeyword& operator=(CConfigKeyword &f) ;
  int operator==(CConfigKeyword &f) ;
} ;

class CConfigAuthor
{
 public:
  string name ;
  string given_name ;
  char I ;

  string url ;
  string email ;
  string filename ;

  CConfigAuthor() {;}
  ~CConfigAuthor() {;}

  CConfigAuthor( CConfigAuthor& f) ;
  CConfigAuthor& operator=( CConfigAuthor &f) ;
  int operator==( CConfigAuthor &f) ;

} ;

class CConfig
{
 public:
  bool html ;
  bool verbose ;
  bool debug ;
public:

  string file_month ;

  CList<CMonth> LMonth ;
  CList<CConfigAuthor> LAuthor ;

  int byear ; // before year
  int ayear ; // after year
  CList<int> LYear ;
  CList<CConfigKeyword> LKeyword ;
  CList<string> LBibfile ;
  CList<CString> LString ;


  // maniere d'écrire les  mois dans les fichiers
  string month_f[13] ;
  string month_e[13] ;

  int Init() ;
  ~CConfig() ;
  CConfig() ;
  CConfig(const char *name) ;

  int LoadConfiguration(const char *name) ;
  int MergeConfiguration(const char *name) ;

  bool no_head_no_foot ;


  bool author_create_pages ;
  bool category_create_pages ;
  bool keyword_create_pages ;
  bool year_create_pages ;
  bool biblio_create_pages ;
  bool create_pages_all ;
  bool create_pages_tex ;

  //----------------------------------------------------------
  //  bool workshop ;

  //----------------------------------------------------------
  string file_css ;
  string css ;
  string   url_download_help ;
  string   url_icon_key ;
  string   url_icon_pdf ;
  string   url_icon_ps ;
  string   url_icon_abstract ;
  string   url_icon_doi ;
  string   url_icon_compressed ;
  string   url_icon_html ;
  string   url_icon_ppt ;
  string   url_icon_word ;
  string   url_icon_arxiv ;

  string directory_base ;
  string base_http ;

  string directory_config ;

  string directory_author ;
  string directory_keyword ;
  string directory_year ;
  string directory_category ;
  string directory_ps ;
  string directory_publi ;
  string directory_all ;
  string directory_bibtex ;

  bool bibtex_link ;

  //----------------------------------------------------------

  string index_filename ;

  string title_index_language1 ;
  string title_index_language2 ;

  string page_start_language1 ;
  string page_start_language2 ;

  string page_end_language1 ;
  string page_end_language2 ;

  string page_acknowledgment ;

  string page_footer_language1 ;
  string page_footer_language2 ;

  string page_header_language1 ;
  string page_header_language2 ;

  string list_start ;
  string list_item ;
  string list_end ;


  string copyright_notice_language2 ;
  string copyright_notice_language1 ;

  string category_phd_language2 ;
  string category_master_language2 ;
  string category_journal_language2 ;
  string category_book_language2 ;
  string category_bookchapter_language2 ;
  string category_conf_internationale_language2 ;
  string category_conf_nationale_language2 ;
  string category_conf_workshop_language2 ;
  string category_rr_language2 ;
  string category_misc_language2 ;
  string category_invited_language2 ;
  string category_journalnat_language2 ;
  string category_popularization_language2 ;

  string category_phd_language1 ;
  string category_master_language1 ;
  string category_journal_language1 ;
  string category_book_language1 ;
  string category_bookchapter_language1 ;
  string category_conf_internationale_language1 ;
  string category_conf_nationale_language1 ;
  string category_conf_workshop_language1  ;
  string category_rr_language1  ;
  string category_misc_language1 ;
  string category_invited_language1 ;
  string category_journalnat_language1 ;
  string category_popularization_language1 ;

  string category_phd ;
  string category_master ;
  string category_journal ;
  string category_book ;
  string category_bookchapter ;
  string category_conf_internationale ;
  string category_conf_nationale ;
  string category_conf_workshop  ;
  string category_rr  ;
  string category_misc ;
  string category_invited ;
  string category_journalnat ;
  string category_popularization ;



  string master_language2 ;
  string master_language1 ;

  string language2_postfix ;
  string language1_postfix ;
  string html_postfix ;
  string tex_postfix ;

  bool language1 ;
  bool language2 ;
  int language ;

  bool all_author ;
  bool all_keyword ;

  bool last_modified ;


  bool check_url ;
  bool check_pdf ;
  bool check_abstract ;
  bool check_doi ;
  bool check_pages ;
  //-------------------------------------------------------------------
  bool generate_national_journals_pages ;
  bool generate_national_conferences_pages ;
  bool generate_workshop_pages ;
  bool generate_popularization_pages ;
  bool generate_invited_pages ;
  bool generate_rr_pages ;

  
  //-------------------------------------------------------------------
  // Tex Stuff
  bool tex ;

  bool item_key_tex ;

  string list_start_tex ;
  string list_item_tex ;
  string list_end_tex ;
  string directory_tex ;

  //-------------------------------------------------------------------

  int nb_phd ;
  int nb_master ;
  int nb_journal ;
  int nb_book ;
  int nb_bookchapter ;
  int nb_conf_internationale ;
  int nb_conf_nationale ;
  int nb_conf_workshop  ;
  int nb_rr  ;
  int nb_misc ;
  int nb_invited ;
  int nb_journalnat ;
  int nb_popularization ;


  int ExtractFields(string &s);
  int ReadNextField(string &s) ;
  int ReadNextEntry(istream &f) ;
  int ExtractString(string &s) ;
  int ExtractAuthor(string &s) ;
  int ExtractYear(string &s) ;
  int ExtractMonth(string &s) ;
  int ExtractKeyword(string &s) ;
  int ExtractSet(string &s) ;
  int ExtractConfigFile(string &s) ;
  int ExtractBibFile(string &s) ;
  int AddName(CConfigAuthor &n) ;
  int AddKeyword(string &n) ;
  void  SortYear() ;
  void  SortYearInverse() ;
  void  SortKeyword() ;
  void  SortAuthor() ;
} ;

#endif
