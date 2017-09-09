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

#include <include/constant.h>

#include <entry/CEntry.h>
#include <entry/CVariousEntry.h>
#include <database/CDataBase.h>
#include <database/html.h>

#include <tools/String.h>
#include <tools/divers.h>
#include <include/constant.h>

#define DEBUG_LEVEL2 0
/*!
  Basic Constructor
*/
CDataBase::CDataBase()
{

  LEntry.Kill() ;
}

/*!
  Destructor
*/
CDataBase::~CDataBase()
{
  LEntry.Kill() ;
}

void
CDataBase::Delete()
{
  LEntry.Front() ;
  while (!LEntry.Outside())
    {
      LEntry.Value()->~CEntry() ;
      LEntry.Next() ;
    }

  LEntry.Kill() ;
}

/*!
  copy operator
*/
CDataBase&
CDataBase::operator=( CDataBase &ib)
{

  LEntry = ib.LEntry ;
  cnf = ib.cnf ;

  return *this ;
}

/*!
  copy constructor
*/
CDataBase::CDataBase( CDataBase &ib)
{
  *this = ib ;
}


int
GetTypeOfEntry(string &s)
{
  int type ;
  type = ENTRY_NOT_DEFINED ;
  if ( 
       (instring(s,"@INPROCEEDINGS{"))||
       (instring(s,"@CONFERENCE{")))
    type = INPROCEEDINGS ;
  else
    if ( instring(s,"@ARTICLE{"))
      type = JOURNAL ;
    else
      if (instring(s,"@TECHREPORT{"))
	type = RR ;
      else
	if ( instring(s,"@PHDTHESIS{"))
	  type = PHDTHESIS ;
	else
	  if (( instring(s,"@MASTERTHESIS{")) ||
	      ( instring(s,"@MASTERSTHESIS{")) ||
	      ( instring(s,"@MASTER{")))
	    type = MASTERTHESIS ;
	  else
	    if ((instring(s,"@MISC{")) ||
		(instring(s,"@MANUAL{")) )
	      type = MISC ;
	    else
	      if ( ( instring(s,"@BOOK{" ) ) ||
		   ( instring(s,"@BOOKLET{" ) )||
		   ( instring(s,"@PROCEEDINGS{" )))
		type = BOOK ;
	      else
		if ( (instring(s,"@INCOLLECTION{")) ||
		     ( instring(s,"@INBOOK{")))
		  {
		    type = INBOOK ;
		  }
		else
		  if ( instring(s,"@STRING{"))
		    type = STRING ;
		  else
		  if ( (instring(s,"@FILM{"))||
		       (instring(s,"@AUDIOVISUAL{"))||
		       (instring(s,"@UNPUBLISHED{")))
		    type = FILM ;
		  else
		    if (instring(s,"@DEFINE{"))
		      type = DEFINE ;
		    else
		      if (instring(s,"@KEYWORD{"))
			type = KEYWORD ;
		      else
			if (instring(s,"@AUTHOR{"))
			  type = AUTHOR ;     else
			    if (instring(s,"@YEAR{"))
			      type = YEAR ;   else
				if (instring(s,"@MONTH{"))
				  type = MONTH ; else
				    if (instring(s,"@BIBFILE{"))
				      type = BIBFILE ; else
					if (instring(s,"@CONFIGFILE{"))
					  type = CONFIGFILE ;
					else
					{
					  cout << "Error in Reference ["<<"] : " ;
					  cout << s << "not define " << endl ;
					}
  return type ;
}

int
CDataBase::ReadNextEntry(istream &f)
{
  static int n =0 ;
  string ligne ;
  int type_of_entry = ENTRY_NOT_DEFINED;
  // on recherche le prochain @ du fichier
  bool find_entry_marker = false ;
  while (find_entry_marker == false )
  {
    // lit une ligne
    getline(f,ligne,'\n') ;
    if (f.eof()) return OK  ;
    filter_string(ligne) ;
    if (DEBUG_LEVEL2) cout << "Lecture ligne : [ "<< ligne << " ] "<<endl ;
    unsigned int i =0 ;
    string us = upcase(ligne) ;
    while ((i < ligne.length() 	   ) &&  (find_entry_marker == false ))
    {
      if (ligne[i] == '@')
      {
	type_of_entry  = GetTypeOfEntry(us) ;
	if (type_of_entry != ENTRY_NOT_DEFINED)
	{
	  find_entry_marker = true ;
	}
      }
      i++ ;
    }
  }
  // On doit chercher ce qu'il y a entre les deux prochaines { }
  string s ;
  s = ligne +" ";
  int nbbrace = count(s,'{') - count(s,'}') ;

  while (nbbrace!=0)
  {
    getline(f,ligne,'\n') ;
    if (f.eof()) return OK  ;
    filter_string(ligne) ;
    nbbrace += count(ligne,'{') - count(ligne,'}') ;
    s += ligne  +" ";
  }
  switch (type_of_entry)
  {
  case YEAR :
    cnf->ExtractYear(s) ;
    break ;
   case MONTH :
    cnf->ExtractMonth(s) ;
    break ;
  case BIBFILE :
    cnf->ExtractBibFile(s) ;
    break ;
  case CONFIGFILE :
    cnf->ExtractConfigFile(s) ;
    break ;
  case STRING :
    ExtractString(s, cnf) ;
    break ;
  case DEFINE:
    cnf->ExtractString(s) ;
    break ;
  case AUTHOR:
    cnf->all_author = false ;
    cnf->ExtractAuthor(s) ;
    break ;
  case KEYWORD:
    cnf->all_keyword = false ;
    cnf->ExtractKeyword(s) ;
    break ;
  default:
    {

      if (   find_entry_marker == true)
      {
	CEntry *entry ;
	entry = (CEntry *)new CEntry(type_of_entry, s, cnf) ;
	LEntry += entry ;

	if ((cnf->verbose==true) && (cnf->debug==false))
	{
	  cout << "[" << entry->key <<"]"   ;
	}
	if ((cnf->debug==true))
	{
	  cout <<n++ << "[" << entry->key <<"]" <<endl ;
	  string s ;
	  entry->Print(s) ;
	  cout << s<< endl ;
	}
      }
    }
    break ;
  }
  return 1 ;
}


int
ExtractString(string &s, CConfig *cnf)
{
  string s_config = s;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_config,TAB," ") ;
  gsub(s_config,"  "," ") ;


  string key ;
  after(s_config,"{",s_config) ;

  before(s_config,"=",key) ;

  after(s_config,"=",s) ;
  unsigned int pos_brace = s.find('{',0) ;
  unsigned int pos_guillemet = s.find('"',0) ;


  string s_field ;
  if ((pos_brace < pos_guillemet))
  {
      after(s,"{", s) ;

      int nbbrace = 1 ;
      int i =-1 ;
      while (nbbrace !=0)
      {
	i++ ;
	if (s[i] == '{') nbbrace++ ;
	if (s[i] == '}') nbbrace-- ;
      }
      s_field = s.substr(0,i) ;
  }
  else
  {
    after(s,"\"", s) ;
    before(s,"\"", s_field) ;
  }


  key = suppress_white_and_tab(key) ;

  CString st ;
  st.key = key ;
  st.st = s_field ;
  cnf->LString += st ;

  //  cout << "KEY: " << key << "    " << st.st << endl ;

  return OK ;
}

void
CDataBase::SortName()
{
  int n_item = LEntry.NbElement();
  if (n_item > 1)
  {
    CEntry *tab[n_item] ;
    int i = 0 ;
    LEntry.Front() ;
    while (!LEntry.Outside())
    {
      tab[i++] = LEntry.Value() ;
      LEntry.Next() ;
    }
    int j ;

    for (i = n_item-1 ; i>=0 ; i--)
      for (j=1 ; j <=i ; j++)
      {
	string name1, name2 ;
	if (tab[j-1]->f_author!=NULL)
	{
	  tab[j-1]->f_author->LName.Front() ;
	  name1 =  tab[j-1]->f_author->LName.Value().last ;
	}
	else name1 = "zzzzzzzzz" ;
	if (tab[j]->f_author !=NULL)
	{
	  tab[j]->f_author->LName.Front() ;
	  name2 =  tab[j]->f_author->LName.Value().last ;
	}
	else name2 = "zzzzzzzzz" ;
	if (upcase(name1) > upcase(name2))
	{
	  CEntry *tmp ;
	  tmp = tab[j-1] ;
	  tab[j-1] = tab[j] ;
	  tab[j] = tmp ;
	}
      }

    LEntry.Kill() ;
    for (i=0 ; i < n_item ; i++)
    {
      LEntry += tab[i] ;
    }
  }
}


void
CDataBase::SortYear()
{
  //  cout << "Sort Year " <<endl ;
  //  cout <<"----------------------------------------------------------"<<endl;

  int n_item = LEntry.NbElement();
  if (n_item >1)
  {
    CEntry *tab[n_item] ;
    int i = 0 ;
    string s ;
    LEntry.Front() ;
    while (!LEntry.Outside())
    {
      tab[i] = LEntry.Value() ;
      //    s = "" ;
      //tab[i]->Print(s) ;
      //cout << s << endl ;
      i++ ;
      LEntry.Next() ;
    }
    int j ;

    for (i = n_item-1 ; i>=0 ; i--)
      for (j=1 ; j <=i ; j++)
      {
	int date1= 2220, date2=2220 ;
	if (tab[j-1]->f_year != NULL)
	  date1 =  tab[j-1]->f_year->s ;
	if (tab[j]->f_year != NULL)
	  date2 =  tab[j]->f_year->s ;

	int month1=14, month2=14 ;

	if (tab[j-1]->f_month != NULL)
	  month1 =  tab[j-1]->f_month->s ;

	if (tab[j]->f_month!= NULL)
	  month2 =  tab[j]->f_month->s ;


	if (date1 < date2) // || ((date1==date2) && (month1<month2)))
	{
	  CEntry *tmp ;
	  tmp = tab[j-1] ;
	  tab[j-1] = tab[j] ;
	  tab[j] = tmp ;
	}
	else
	  if    ((date1==date2) && (month1<month2))
	  {
	    CEntry *tmp ;
	    tmp = tab[j-1] ;
	    tab[j-1] = tab[j] ;
	    tab[j] = tmp ;
	  }

      }
    LEntry.Kill() ;
    for (i=0 ; i < n_item ; i++)
    {
      LEntry += tab[i] ;

      //    s="" ;
      //    tab[i]->Print(s) ;
      //    cout << s << endl ;

    }
    //      cout << "ok " <<endl ;
  }
}

void
CDataBase::SortYearInverse()
{
  //  cout << "Sort Year " <<endl ;
  //  cout <<"----------------------------------------------------------"<<endl;

  int n_item = LEntry.NbElement();
  if (n_item >1)
  {
    CEntry *tab[n_item] ;
    int i = 0 ;
    string s ;
    LEntry.Front() ;
    while (!LEntry.Outside())
    {
      tab[i] = LEntry.Value() ;
      //    s = "" ;
      //tab[i]->Print(s) ;
      //cout << s << endl ;
      i++ ;
      LEntry.Next() ;
    }
    int j ;

    for (i = n_item-1 ; i>=0 ; i--)
      for (j=1 ; j <=i ; j++)
      {
	int date1= 2020, date2=2020 ;
	if (tab[j-1]->f_year != NULL)
	  date1 =  tab[j-1]->f_year->s ;
	if (tab[j]->f_year != NULL)
	  date2 =  tab[j]->f_year->s ;

	int month1=14, month2=14 ;

	if (tab[j-1]->f_month != NULL)
	  month1 =  tab[j-1]->f_month->s ;

	if (tab[j]->f_month!= NULL)
	  month2 =  tab[j]->f_month->s ;


	if (date1 > date2) // || ((date1==date2) && (month1<month2)))
	{
	  CEntry *tmp ;
	  tmp = tab[j-1] ;
	  tab[j-1] = tab[j] ;
	  tab[j] = tmp ;
	}
	else
	  if    ((date1==date2) && (month1>month2))
	  {
	    CEntry *tmp ;
	    tmp = tab[j-1] ;
	    tab[j-1] = tab[j] ;
	    tab[j] = tmp ;
	  }

      }
    LEntry.Kill() ;
    for (i=0 ; i < n_item ; i++)
    {
      LEntry += tab[i] ;

      //    s="" ;
      //    tab[i]->Print(s) ;
      //    cout << s << endl ;

    }
    //      cout << "ok " <<endl ;
  }
}

void CDataBase::Print()
{
  LEntry.Front() ;
  while (!LEntry.Outside())
  {
    CEntry *entry ;
    entry = LEntry.Value() ;
    string s ;
    entry->Print(s) ;
    cout << s <<endl ;
    LEntry.Next() ;
  }
}


void CDataBase::PrintHTML(ofstream &f)
{
  f << cnf->list_start <<endl ;

  LEntry.Front() ;
  while (!LEntry.Outside())
  {
    CEntry *entry ;
    entry = LEntry.Value() ;
    //    if (cnf->debug==true)  cout << "output ["<<entry->key <<"] entry" << endl ; // EM
    string s ; s = "" ;
    entry->PrintHTML(s) ;

    if (cnf->biblio_create_pages==true)
    {

      if (suppress_white_and_tab(cnf->url_icon_abstract)!="")
      {
	s += " <a href=\""+cnf->base_http+"/" +cnf->directory_publi+"/"+entry->key ;
	if (cnf->language ==LANGUAGE1)
	  s+= cnf->language1_postfix ;
	else
	  s+= cnf->language2_postfix ;
	s+= cnf->html_postfix +"\">";
	s += "<img src=\""+suppress_white_and_tab(cnf->url_icon_abstract)+"\" align=top border=0 alt=\"details\">" ;
	s += "</a>" ;

      }
      else
      {
	s += " (<a href=\""+cnf->base_http+"/" +cnf->directory_publi+"/"+entry->key ;
	if (cnf->language ==LANGUAGE1)
	  s+= cnf->language1_postfix ;
	else
	  s+= cnf->language2_postfix ;
	s+= cnf->html_postfix +"\">";
	if (cnf->language==ENGLISH)
	  s += "more" ;
	else
	  s += "détails" ;
	s += "</a>)" ;

      }
    }
    //----------------------------
    if (entry->f_doi != NULL)
    {
      entry->DownloadIcon(entry->f_doi->s, s) ;
    }
    //----------------------------
    if (entry->f_url != NULL)
    {
      entry->DownloadIcon(entry->f_url->s, s) ;
    }
  //----------------------------
    if (entry->f_arxiv != NULL)
    {
      entry->DownloadArxiv(entry->f_arxiv->s, s) ;
    }

    //---------------------------------


    f << cnf->list_item << s <<endl ;
    LEntry.Next() ;
  }
  f << cnf->list_end <<endl ;
}

void
CDataBase::PrintTex(ofstream &f)
{
  CEntry *entry ;
  entry = LEntry.Value() ;
  string s1 ;
  s1 = "\\begin{" ;
  s1 +=  cnf->list_start_tex ;
  switch(entry->type_of_entry)
  {
  case JOURNAL :
    s1+="journal";
    break ; 
  case JOURNALNAT :
    s1+="journalnat";
    break ;
  case INVITED :
    s1 += "invited" ;
    break ; 
  case POPULARIZATION :
    s1 += "popularization" ;
    break ;
  case INPROCEEDINGS :
    s1 += "conference" ;
    break ;
 
  case CONFNAT :
    s1 += "conferencenat" ;
      break ;
  case WORKSHOP :
    s1 += "workshop" ;
    break ;
  case INBOOK :
    s1 += "inbook" ;
    break ;
  case RR :
    s1 += "rr" ;
    break ;
  case PHDTHESIS :
    s1 += "these" ;
    break ;
  case MASTERTHESIS :
    s1 += "ms" ;
    break ;
  case BOOK :
    s1 += "book" ;
    break ;
  case MISC :
    s1 += "misc" ;
    break ;
  }
  f << s1 <<"}"<<endl ;


  LEntry.Front() ;
  while (!LEntry.Outside())
  {
    CEntry *entry ;
    entry = LEntry.Value() ;
    string s ; s = "" ;
    s1 = "" ;

    s1 += cnf->list_item_tex ;
    switch(entry->type_of_entry)
    {
    case JOURNAL :
      s1+="journal";
      break ;
   case JOURNALNAT :
    s1+="journalnat";
    break ;
  case INVITED :
    s1 += "invited" ;
    break ; 
  case POPULARIZATION :
    s1 += "popularization" ;
    break ;
   case INPROCEEDINGS :
      s1 += "conference" ;
      break ;
    case CONFNAT :
      s1 += "conferencenat" ;
      break ;
    case WORKSHOP :
       s1 += "workshop" ;
     break ;
    case INBOOK :
       s1 += "inbook" ;
      break ;
    case RR :
       s1 += "rr" ;
      break ;
    case PHDTHESIS :
       s1 += "these" ;
      break ;
    case MASTERTHESIS :
       s1 += "ms" ;
      break ;
    case BOOK :
       s1 += "book" ;
      break ;
    case MISC :
       s1 += "misc" ;
      break ;
    }
    if (cnf->item_key_tex==true)  s1 += "{" + entry->key + "}" ;

    entry->PrintLATEX(s) ;

    f << s1 <<"  " << s <<endl ;
    LEntry.Next() ;
  }

  s1 = "\\end{" ;
  s1 +=  cnf->list_start_tex ;
  switch(entry->type_of_entry)
  {
  case JOURNAL :
    s1+="journal";
    break ;
  case JOURNALNAT :
    s1+="journalnat";
    break ;
  case INVITED :
    s1 += "invited" ;
    break ; 
  case POPULARIZATION :
    s1 += "popularization" ;
    break ;
  case INPROCEEDINGS :
    s1 += "conference" ;
    break ;
  case CONFNAT :
    s1 += "conferencenat" ;
    break ;
  case WORKSHOP :
    s1 += "workshop" ;
    break ;
  case INBOOK :
    s1 += "inbook" ;
    break ;
  case RR :
    s1 += "rr" ;
      break ;
    case PHDTHESIS :
       s1 += "these" ;
      break ;
    case MASTERTHESIS :
       s1 += "ms" ;
      break ;
    case BOOK :
       s1 += "book" ;
      break ;
    case MISC :
       s1 += "misc" ;
      break ;
    }
  f << s1 <<"}"<<endl ;
}

int
CDataBase::LoadBase(const char *nom, CConfig *_cnf)
{

  cnf = _cnf ;

  return MergeBase(nom) ;
  /*ifstream f(nom) ;

    if(cnf->verbose)
    cout << "Loading database " << nom <<endl ;

    if (f==NULL) { cout << "cannot open "<<nom << endl ;return -1 ; }

    while(!f.eof())
    {
    ReadNextEntry(f) ;
    }

    if(cnf->verbose)
    cout << endl ;

    f.close() ;*/
  // return OK ;
}

int
CDataBase::MergeBase(const char *nom)
{
  ifstream f(nom) ;

  if(cnf->verbose)
    cout << "Loading database " << nom <<endl ;

  if (f==NULL) { cout << "cannot open "<<nom << endl ;return -1 ; }
  while(!f.eof())
    ReadNextEntry(f) ;

  if(cnf->verbose)
    cout << endl ;

  f.close() ;
  return OK ;

}

int
CDataBase::SaveBaseRef(const char *nom)
{
  ofstream f(nom) ;


  if (f==NULL) { cout << "cannot open "<<nom << endl ;return -1 ; }
  LEntry.Front() ;
  while(!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;

    string s ;
    item->PrintEE(s) ;
    f << s <<endl <<endl ;

    LEntry.Next() ;
  }


  f.close() ;
  return OK ;

}


int
CDataBase::SaveBaseBib(string &nom)
{
  ofstream f(nom.c_str()) ;

  if (f==NULL) { cout << "cannot open "<<nom << endl ;return -1 ; }
  LEntry.Front() ;
  while(!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;

    string s ;
    item->PrintBIBTEX(s) ;
    f << s <<endl <<endl ;

    LEntry.Next() ;
  }

  f.close() ;
  return OK ;

}


void
CDataBase::PrintBase()
{
 LEntry.Front() ;
 while (!LEntry.Outside())
 {
   CEntry *item ;
   item = LEntry.Value() ;
   string s ;
   item->Print(s) ;
   LEntry.Next() ;
 }

}

int
CDataBase::CreatePublicationPage()
{
  int nb = 0 ;
  int k =1 ;
  if (cnf->language1==true)
  {
    cnf->language = LANGUAGE1 ;
    LEntry.Front() ;
    int nmax = LEntry.NbElement() ;
    while (!LEntry.Outside())
    {
      CEntry *item ;
      item = LEntry.Value() ;

      string key = suppress_white_and_tab(item->key) ;
      key = cnf->directory_base +"/"+ cnf->directory_publi +"/" + key +cnf->language1_postfix + cnf->html_postfix ;
      nb++ ;
      if (cnf->debug)    cout << k++ << " | open " << key <<endl ;
      ofstream f(key.c_str()) ;
      if (f==NULL) cout << "cannot open page " << key << endl ;
      item->CreatePublicationPage(f) ;

      printf("language 1 %d %%\r", (int)(nb*100.0/nmax)) ;
      cout <<flush ;

      f.close() ;
      LEntry.Next() ;
    }
  }
  
  if (cnf->language2==true)
  {
    cnf->language=LANGUAGE2 ;
    int nmax = LEntry.NbElement() ;
    LEntry.Front() ;
    while (!LEntry.Outside())
    {
      CEntry *item ;
      item = LEntry.Value() ;

      string key = suppress_white_and_tab(item->key) ;
      key = cnf->directory_base +"/"+ cnf->directory_publi +"/" + key +cnf->language2_postfix + cnf->html_postfix ;
      nb++ ;
      if (cnf->debug)    cout << k++ << " | open " << key <<endl ;
      ofstream f(key.c_str()) ;
      if (f==NULL) cout << "cannot open page " << key << endl ;
      item->CreatePublicationPage(f) ;
 

      printf("language 2 %d %%\r", (int)(nb*100.0/nmax)) ;
      cout <<flush ;
     f.close() ;
      LEntry.Next() ;
    }
  }
  return nb ;
}

ostream& operator<< (ostream& os, CDataBase& p)
{
  p.LEntry.Front() ;
  while (!p.LEntry.Outside())
  {
    CEntry *item ;
    item = p.LEntry.Value() ;
    p.LEntry.Next() ;
    string s ;
    item->Print(s) ;
    os << s << endl ;
  }
  return os ;
}

void
CDataBase::ExtractAuthor(CDataBase& B, CName &author)
{
  LEntry.Front() ;
  B.cnf = cnf ;

  B.LEntry.Kill() ;

  //  cout << "|" <<author.name <<"|" <<endl ;
  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;
    LEntry.Next() ;

    if (item->f_author!=NULL)
    {
      item->f_author->LName.Front() ;
      while(! item->f_author->LName.Outside())
      {
	CName name = item->f_author->LName.Value() ;
	//      cout << "           |" <<name.name <<"|" <<endl ;

	if (name == author)
	{
	  B.LEntry += item ;
	  break  ;
	}
	item->f_author->LName.Next() ;
      }
    }
  }

  //  B.Print() ;
}
/*
void
DataBase::RAok()
{
  LEntry.Front() ;
  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;

    item.RA = 1 ;
    LEntry.Modify(item) ;
    LEntry.Next() ;

  }

}
*/
int
CDataBase::ExtractYear(CDataBase& B, int year, int ab )
{
  LEntry.Front() ;
  B.cnf = cnf ;
  B.LEntry.Kill() ;

  int x = 0;
  if (ab==AFTER) x = -1000;  else x = 3000 ; // attention au bug de l'an 3000
  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;
    LEntry.Next() ;

    if (item->f_ra == NULL)
    {
      if (year == item->f_year->s)
      {
	B.LEntry += item ;
      }
      else
	if (ab==AFTER)
	{
	  if (item->f_year->s >= year)	B.LEntry += item ;
	  if (item->f_year->s>x) x = item->f_year->s ;
	}
	else
	  if (ab==BEFORE)
	  {
	    if (item->f_year->s <= year)  B.LEntry += item ;
	    if (item->f_year->s <x) x= item->f_year->s ;

	  }
    }
  }

    if (ab==0) B.SortName() ;
    else  B.SortYear() ;
  return x ;

}

void
CDataBase::ExtractTypeRA(CDataBase& B, int type_of_entry )
{
  LEntry.Front() ;
  B.cnf = cnf ;
  B.LEntry.Kill() ;

  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;
    LEntry.Next() ;

   if (item->f_ra ==NULL)
    if (type_of_entry == item->type_of_entry)
    {
      B.LEntry += item ;
    }
  }

  B.SortName() ;
}

void
CDataBase::ExtractTypeRA_sort_year(CDataBase& B, int type_of_entry )
{
  LEntry.Front() ;
  B.cnf = cnf ;
  B.LEntry.Kill() ;

  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;
    LEntry.Next() ;

   if (item->f_ra ==NULL)
    if (type_of_entry == item->type_of_entry)
    {
      B.LEntry += item ;
    }
  }

  B.SortYear() ;
}

void
CDataBase::ExtractType(CDataBase& B, int type_of_entry )
{
  LEntry.Front() ;
  B.cnf = cnf ;
  B.LEntry.Kill() ;

  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;
    LEntry.Next() ;

    if (type_of_entry == item->type_of_entry)
    {
      B.LEntry += item ;
    }
  }

  B.SortYear() ;
}

void
CDataBase::ExtractKeyword(CDataBase& B, CConfigKeyword &keyword )
{
  B.cnf = cnf ;
  B.LEntry.Kill() ;
  LEntry.Front() ;
  while (!LEntry.Outside())
  {
    CEntry *item ;
    item = LEntry.Value() ;
    LEntry.Next() ;
    if (item->f_ra == NULL)
      if (item->f_keyword!=NULL)
      {
	item->f_keyword->LKeyword.Front() ;

	while(!item->f_keyword->LKeyword.Outside())
	{
	  string key = item->f_keyword->LKeyword.Value() ;

	  string s1, s2 ;
	  s1 = upcase(suppress_white_and_tab(key));
	  s2 = upcase(suppress_white_and_tab(keyword.key));
	  if (s1 == s2)
	  {
	    B.LEntry += item ;
	    break  ;
	  }
	  item->f_keyword->LKeyword.Next() ;
	}
      }
  }

  B.SortYear() ;

}


int
CDataBase::LoadBibFile(CConfig *cnf)
{
  if (cnf->LBibfile.NbElement() !=0)
  {
    cnf->LBibfile.Front() ;
    while (!cnf->LBibfile.Outside())
    {
      string s =  cnf->LBibfile.Value() ;
      cnf->LBibfile.Next() ;
      char s1[FILENAME_MAX] ;
      sprintf(s1,"%s", s.c_str()) ;
      LoadBase(s1, cnf) ;
    }
  }

  return OK ;
}

int
CDataBase::TestKey()
{
   //  cout << "Sort Year " <<endl ;
  //  cout <<"----------------------------------------------------------"<<endl;

  int n_item = LEntry.NbElement();
  if (n_item >1)
  {
    CEntry *tab[n_item] ;
    int i = 0 ;
    string s ;
    LEntry.Front() ;
    while (!LEntry.Outside())
    {
      tab[i] = LEntry.Value() ;
      //    s = "" ;
      //tab[i]->Print(s) ;
      //cout << s << endl ;
      i++ ;
      LEntry.Next() ;
    }
    int j ;

    for (i = 0 ; i < n_item ; i++)
      for (j=1 ; j < i ; j++)
      {
	if (tab[i]->key == tab[j]->key)
	{
	  cout << "Multiple definition of " << tab[j]->key <<" key in the bibtex dtabase " <<endl;
	  cout <<"These keys are for paper : " <<endl ;
	  string s1, s2 ;
	  tab[i]->Print(s1) ;
	  tab[j]->Print(s2) ;
	  cout << "- " <<  s1 <<endl << "and" <<endl ;
	  cout << "- " << s2 << endl ;

	}
      }
    //      cout << "ok " <<endl ;
  }

  return OK ;
}
