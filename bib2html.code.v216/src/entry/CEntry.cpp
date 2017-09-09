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


#include <entry/CEntry.h>
#include <entry/CVariousEntry.h>
#include <tools/String.h>
#include <database/html.h>


#define DEBUG_LEVEL1 0
#define DEBUG_LEVEL2 0

int CheckYear(CConfig *cnf, int year)
{
  bool findyear ;
  findyear = false ;
  cnf->LYear.Front() ;

  while (!cnf->LYear.Outside())
  {
    int  cnfyear = cnf->LYear.Value() ;
    if (cnfyear==year )	findyear = true ;
    cnf->LYear.Next() ;
  }
  if (findyear==true) return 1 ; else return 0 ;
}

void
CEntry::Init()
{
   f_author = NULL;
   f_editor = NULL;
   f_title = NULL;
   f_arxiv= NULL   ;
   f_url= NULL   ;
   f_doi= NULL   ;
   f_urltransp = NULL;
   f_urlinterne = NULL ;

   f_year = NULL;
   f_abstract = NULL;
   f_journal = NULL;
   f_booktitle = NULL;

   f_volume = NULL;
   f_address = NULL;
   f_addresse= NULL ;

   f_publisher= NULL ;
   f_howpublish= NULL ;
   f_series = NULL;
   f_school = NULL;
   f_institution = NULL;
   f_type = NULL;
   f_note = NULL;

  // integer
   f_volume = NULL;
   f_chapter = NULL ;
   f_year = NULL;
   f_number = NULL;

   f_workshop = NULL;
   f_ra = NULL;
   f_toappear= NULL ;
   f_confnat= NULL ;
   f_hdr= NULL ;

   f_pages = NULL;

   f_month = NULL;
   f_keyword = NULL;
   f_crossref= NULL;

   f_xinvitedconference = NULL;
   f_xscientificpopularization= NULL ;
   f_xinternationalaudiance= NULL ;
   f_xeditorialboard = NULL;
   f_xproceedings= NULL;
    f_xmisc = NULL;
   f_xnote= NULL;
   
}
/*!
  constructor
*/
CEntry::CEntry(int _type_of_entry,  string &s, CConfig *_cnf)
{
  if (DEBUG_LEVEL1)
    cout << "begin CEntry::CEntry(int _type_of_entry,  string &s, CConfig *_cnf)" <<endl ;

  cnf = _cnf ;

  Init() ;
  type_of_entry = _type_of_entry ;
  s_entry  = s ;
  ExtractFields(s_entry) ;
  {
    string s ;
    switch( type_of_entry )
    {
    case JOURNAL :
    case JOURNALNAT :
      ((CEntryJournal *)this)->Print(s) ;
      break ;
    case INPROCEEDINGS :
    case CONFNAT :
    case WORKSHOP :
      ((CEntryInProceedings *)this)->Print(s) ;
      break ;
    case INBOOK :
      ((CEntryInBook *)this)->Print(s) ;
      break ;
    case RR :
      ((CEntryTechReport *)this)->Print(s) ;
      break ;
    case PHDTHESIS :
      ((CEntryPhdThesis *)this)->Print(s) ;
      break ;
    case MASTERTHESIS :
      ((CEntryMasterThesis *)this)->Print(s) ;
      break ;
    case BOOK :
      ((CEntryBook *)this)->Print(s) ;
      break ;
    case MISC :
      ((CEntryMisc *)this)->Print(s) ;
      break ;
    }
  }
  if (DEBUG_LEVEL1)
    cout << "end CEntry::CEntry(int _type_of_entry,  string &s, CConfig *_cnf)" <<endl ;
}

/*!
  print HTML
*/
void
CEntry::Print(string &s)
{
    switch( type_of_entry )
    {
    case JOURNAL :
    case JOURNALNAT :
      ((CEntryJournal *)this)->Print(s) ;
      break ;
    case INPROCEEDINGS :
    case CONFNAT :
    case WORKSHOP :
      ((CEntryInProceedings *)this)->Print(s) ;
      break ;
    case INBOOK :
      ((CEntryInBook *)this)->Print(s) ;
      break ;
    case RR :
      ((CEntryTechReport *)this)->Print(s) ;
      break ;
    case MASTERTHESIS :
      ((CEntryMasterThesis *)this)->Print(s) ;
      break ;
     case PHDTHESIS :
      ((CEntryPhdThesis *)this)->Print(s) ;
      break ;
    case BOOK :
      ((CEntryBook *)this)->Print(s) ;
      break ;
    case MISC :
      ((CEntryMisc *)this)->Print(s) ;
      break ;
    }
    gsub(s,"..",".") ;
    gsub(s,".,",",") ;
    gsub(s," ,",",") ;
    gsub(s,"~"," ") ;
}

/*!
  print HTML
*/
void
CEntry::PrintHTML(string &s)
{


    switch( type_of_entry )
    {
    case JOURNAL :
    case JOURNALNAT :
      ((CEntryJournal *)this)->PrintHTML(s) ;
      break ;
    case INPROCEEDINGS :
    case CONFNAT :
     case WORKSHOP :
    case POPULARIZATION :
   case INVITED :
      ((CEntryInProceedings *)this)->PrintHTML(s) ;
      break ;
    case INBOOK :
      ((CEntryInBook *)this)->PrintHTML(s) ;
      break ;
    case RR :
      ((CEntryTechReport *)this)->PrintHTML(s) ;
      break ;
    case MASTERTHESIS :
      ((CEntryMasterThesis *)this)->PrintHTML(s) ;
      break ;
     case PHDTHESIS :
      ((CEntryPhdThesis *)this)->PrintHTML(s) ;
      break ;
    case BOOK :
      ((CEntryBook *)this)->PrintHTML(s) ;
      break ;
    case MISC :
      ((CEntryMisc *)this)->PrintHTML(s) ;
      break ;
    }
    
    if (f_toappear != NULL)
      if (cnf->language ==  LANGUAGE2)
	gsub(s,"to appear"," à paraître") ;
    /*
    if (f_toappear != NULL)
      if (cnf->language ==  LANGUAGE2)
	s += " (À paraître)" ;
    else
      	s += " (To appear)" ;
    */
    gsub(s,"{","") ;
    gsub(s,"}","") ;
    gsub(s,"--","-") ;
    gsub(s,"..",".") ;
    gsub(s,".,",",") ;
    gsub(s," ,",",") ;
    gsub(s,"~"," ") ;
}

/*!
  print HTML
*/
void
CEntry::PrintLATEX(string &s)
{
    switch( type_of_entry )
    {
    case JOURNAL :
    case JOURNALNAT :
      ((CEntryJournal *)this)->PrintLATEX(s) ;
      break ;
    case INPROCEEDINGS :
    case CONFNAT :
   case INVITED :
    case POPULARIZATION :
    case WORKSHOP :
      ((CEntryInProceedings *)this)->PrintLATEX(s) ;
      break ;
    case INBOOK :
      ((CEntryInBook *)this)->PrintLATEX(s) ;
      break ;
    case RR :
      ((CEntryTechReport *)this)->PrintLATEX(s) ;
      break ;
    case MASTERTHESIS :
      ((CEntryMasterThesis *)this)->PrintLATEX(s) ;
      break ;
     case PHDTHESIS :
      ((CEntryPhdThesis *)this)->PrintLATEX(s) ;
      break ;
    case BOOK :
      ((CEntryBook *)this)->PrintLATEX(s) ;
      break ;
    case MISC :
      ((CEntryMisc *)this)->PrintLATEX(s) ;
      break ;
    }

    if (f_toappear != NULL)
      if (cnf->language ==  LANGUAGE2)
	gsub(s,"to appear"," à paraître") ;
    /*
    if (f_toappear != NULL)
      if (cnf->language ==  LANGUAGE2)
	s += " (À paraître)" ;
    else
      	s += " (To appear)" ;
    */
    // gsub(s,"&","\\&") ;
    gsubonetime(s,"&","\\&") ;
    gsub(s,"..",".") ;
    gsub(s,".,",",") ;
    gsub(s," ,",",") ;
}

/*!
  PrintBIBTEX
*/
void
CEntry::PrintBIBTEX(string &s)
{
  s="" ;
  switch( type_of_entry )
  {
  case JOURNAL :
  case JOURNALNAT :
    ((CEntryJournal *)this)->PrintBIBTEX(s) ;
    break ;
  case INPROCEEDINGS :
  case CONFNAT :
  case WORKSHOP :
    case POPULARIZATION :
   case INVITED :
    ((CEntryInProceedings *)this)->PrintBIBTEX(s) ;
    break ;
  case INBOOK :
    ((CEntryInBook *)this)->PrintBIBTEX(s) ;
    break ;
  case RR :
    ((CEntryTechReport *)this)->PrintBIBTEX(s) ;
    break ;
  case MASTERTHESIS :
    ((CEntryMasterThesis *)this)->PrintBIBTEX(s) ;
    break ;
   case PHDTHESIS :
    ((CEntryPhdThesis *)this)->PrintBIBTEX(s) ;
    break ;
  case BOOK :
    ((CEntryBook *)this)->PrintBIBTEX(s) ;
    break ;
  case MISC :
    ((CEntryMisc *)this)->PrintBIBTEX(s) ;
    break ;
  }
  gsub(s,"..",".") ;
  gsub(s,".,",",") ;
  gsub(s," ,",",") ;
  gsub(s,"~"," ") ;
}

/*!
  print HTML
*/
void
CEntry::PrintEE(string &s)
{
    switch( type_of_entry )
    {
    case JOURNAL :
    case JOURNALNAT :
      ((CEntryJournal *)this)->PrintEE(s) ;
      break ;
    case INPROCEEDINGS :
    case CONFNAT :
   case INVITED :
    case WORKSHOP :
    case POPULARIZATION :
      ((CEntryInProceedings *)this)->PrintEE(s) ;
      break ;
    case INBOOK :
      ((CEntryInBook *)this)->PrintEE(s) ;
      break ;
    case RR :
      ((CEntryTechReport *)this)->PrintEE(s) ;
      break ;
    case MASTERTHESIS :
      ((CEntryMasterThesis *)this)->PrintEE(s) ;
      break ;
     case PHDTHESIS :
      ((CEntryPhdThesis *)this)->PrintEE(s) ;
      break ;
    case BOOK :
      ((CEntryBook *)this)->PrintEE(s) ;
      break ;
    case MISC :
      ((CEntryMisc *)this)->PrintEE(s) ;
      break ;
    }
}

void
CEntry::GetKey(string &s)
{
  between(s,"{",",",key) ;
  key = suppress_white_and_tab(key) ;
}


void CEntry::PrintKey()
{
  cout << "Key : " << key <<endl ;
}

int
CEntry::ReadNextField(string &s)
{

  if (DEBUG_LEVEL1)
    cout << "begin CEntry::ReadNextField(string &s) "<<endl ;

  char sRC[3] ;
  sprintf(sRC,"\n") ;
  string RC(sRC) ;


  if (DEBUG_LEVEL1)
    cout << "begin  CEntry::ReadNextField(string &s)" <<endl ;

  string tmp, field_name ;
  before(s,"=", tmp) ;

  suppress_white_and_tab(tmp, field_name) ;

  field_name = upcase(field_name) ;

  after(s,"=", s) ;

  // we seek for either a {, a ',' or a "
  // the first founded of these char defines how
  // we parse the string

  unsigned int pos_brace = s.find('{',0) ;
  unsigned int pos_virgule = s.find(',',0) ;
  unsigned int pos_guillemet = s.find('"',0) ;

  bool nobrace = false ;
  string s_field ;
  if ((pos_brace < pos_virgule) && (pos_brace < pos_guillemet))
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

      s = s.substr(i+1, s.length()) ;
      after(s,",",s) ;
  }

  if ((pos_virgule < pos_brace ) && ( pos_virgule < pos_guillemet))
  {
    before(s,",", s_field) ;
    after(s,",",s) ;
    nobrace = true ;
  }
  else
  if ((pos_guillemet < pos_brace ) && ( pos_guillemet < pos_virgule ))
  {
    after(s,"\"", s) ;
    before(s,"\"", s_field) ;
    after(s,"\"", s) ;
    after(s,",",s) ;
  }

  if ((pos_guillemet==string::npos) &&
      (pos_brace==string::npos)      &&
      (pos_virgule==string::npos))
  {
    s_field =s ;
    s="";
  }

  // dans cette alternative on se retrouve potentiellement avec une
  // definition de type @String
  // on remplace si on trouve
  if ((field_name == "NUMBER") ||
      (field_name == "YEAR") ||
      (field_name == "VOLUME") ||
      (field_name == "CHAPTER"))
  {}
  else
  {
    bool find = false ;
    if (nobrace==true)
    {
      //    cout << "FIELD |"<<s_field<<"|"<<endl ;
      cnf->LString.Front() ;
      while (!cnf->LString.Outside())
      {
	CString st ;
	st = cnf->LString.Value() ;
	cnf->LString.Next() ;
	if (suppress_white_and_tab(st.key)==suppress_white_and_tab(s_field))
	{
	  //	  cout << "String value match !" <<endl ;
	  s_field = st.st ;
	  find = true ;
	  break ;
	}
      }
      //    cout << "FIELD |"<<s_field<<"|"<<endl ;
    }
  }

  //  cout << pos_guillemet <<"  " <<pos_brace<<"  " <<pos_virgule <<endl ;
  if (DEBUG_LEVEL2)
    cout << "field - " << field_name << " -" <<s_field <<"-"<<endl ;

  //  filter_string(s_field) ;
  //---------------------------------------------------------------
  // Name
  if (field_name == "AUTHOR")
  {
    gsub(s_field,"{ ","{") ;
    f_author = new CFieldAuthor(s_field) ;
    if (cnf->all_author == true)
    {

      f_author->LName.Front() ;
      while(!f_author->LName.Outside())
      {
	CConfigAuthor ca ;
	CName can= f_author->LName.Value() ;
	ca.name = can.last ;
	ca.given_name = can.first ;
	//	gsub(ca.given_name,".","") ;
	ca.I = upcase(can.first)[0] ;

	cnf->AddName(ca) ;
	f_author->LName.Next() ;
      }
    }
  }

  if (field_name == "EDITOR" )
  {
    f_editor = new CFieldEditor(s_field) ;
  }

  //---------------------------------------------------------------
  // String
  if (field_name == "TITLE" )//
  {
    f_title = new CFieldTitle(s_field) ;
  }

  if ((field_name == "JOURNAL" ) || (field_name == "JOURNALNAT"))//
  {
    f_journal = new CFieldJournal(s_field) ;
  }

  if (field_name == "BOOKTITLE" )//
  {
    f_booktitle = new CFieldBookTitle(s_field) ;
  }

  if (field_name == "ARXIV" )//
  {
    f_arxiv = new CFieldArxiv(s_field) ;
  }
  if ((field_name == "URL" )||
      (field_name == "PDF" )||
      (field_name == "POSTSCRIPT" ))//
  {
    f_url = new CFieldURL(s_field) ;
  }
  if ((field_name == "DOI" ))//
  {
    f_doi = new CFieldDOI(s_field) ;
  }
  if ((field_name == "URLINTERNE" )||
      (field_name == "PDFINTERNE" ))
  {
    f_urlinterne = new CFieldURLinterne(s_field) ;
  }

  if ((field_name == "URLTRANSP" )||
      (field_name == "SLIDEURL" )||
      (field_name == "SLIDE" ))//
  {
    f_urltransp = new CFieldURLtransp(s_field) ;
  }

  if (field_name == "VOLUME" )//
  {
    f_volume = new CFieldVolume(s_field) ;
  }
  if (field_name == "ADDRESS" )//
  {
    f_address = new CFieldAddress(s_field) ;
  }
  // la faute d'orthographe initiale implique un patch...
  if ((field_name == "ADDRESSE" ) || ((field_name == "ADRESSE" ) )) //
  {
    f_addresse = new CFieldAddresse(s_field) ;
  }
  if  (field_name == "PUBLISHER" )//
  {
    f_publisher = new CFieldPublisher(s_field) ;
  }
  if  (field_name == "HOWPUBLISHED" )//
  {
    f_howpublish = new CFieldHowpublished(s_field) ;
  }
  if  (field_name == "SERIES" )//
  {
    f_series = new CFieldSeries(s_field) ;
  }

  if (field_name == "SCHOOL" )//
  {
    f_school = new CFieldSchool(s_field) ;
  }
  if (field_name == "INSTITUTION" )//
  {
    f_institution = new CFieldInstitution(s_field) ;
  }
  if (field_name == "ABSTRACT" ) //
  {
    f_abstract = new CFieldAbstract(s_field) ;
  }

  if (field_name == "TYPE" ) //
  {
    f_type = new CFieldType(s_field) ;

    if (type_of_entry == INPROCEEDINGS)
    {
      string s = upcase(f_type->s) ;
      unsigned int pos ;
      pos = s.find("CONFNAT",0) ;
      if (pos != string::npos) type_of_entry = CONFNAT ;
      else
      {
	pos = s.find("NATIONAL",0) ;
	if (pos != string::npos) type_of_entry = CONFNAT ;
	else
	  if (cnf->generate_workshop_pages==true)
	  {
	    {
	      pos = s.find("WORKSHOP",0) ;
	      if (pos != string::npos) type_of_entry = WORKSHOP ;
	      else
	      {
		pos = s.find("SYMPOSIUM",0) ;
		if (pos != string::npos) type_of_entry = WORKSHOP ;
	      }
	    }
	  }
      }
    }
    if (type_of_entry == PHDTHESIS)
    {
      string s = upcase(f_type->s) ;
      unsigned int pos ;
      pos = s.find("HDR",0) ;
      if (pos != string::npos) f_hdr = new CFieldHDR(1) ;
      else
      {
	pos = s.find("HABILITATION",0) ;
	if (pos != string::npos) f_hdr = new CFieldHDR(1) ;
      }
    }
  }

  if ((field_name == "NOTE" ) || (field_name == "ANNOTE" )) //
  {
    f_note = new CFieldNote(s_field) ; 
     unsigned int pos ;
      string s = upcase(f_note->s) ;
      pos = s.find("APPEAR",0) ;
      if (pos != string::npos)
	{ 
	f_toappear = new CFieldToAppear(1) ;
	//	gsub(f_note->s,"to appear","") ;
	} 

  } 
  if ((field_name == "X-NOTE" ) ) //
  {
    f_xnote = new CFieldXNote(s_field) ;
   
  } 
  if ((field_name == "X-MISC" ) ) //
  {
    f_xmisc = new CFieldXMisc(s_field) ;
  }
  //-------------------------------------------------------------
  // Entier
  if (field_name == "CHAPTER" )
  {
   f_chapter = new CFieldChapter(s_field) ;
  }

  if (field_name == "YEAR" )
  {
    f_year = new CFieldYear(s_field) ;
    if (CheckYear(cnf, f_year->s ) ==0)
      cnf->LYear += f_year->s ;
  }

  if (field_name == "NUMBER" )
  {
    f_number  = new CFieldNumber(s_field) ;
  }

  //-------------------------------------------------------------
  // Booleen
  if  (field_name == "X-EDITORIAL-BOARD" )
    {
      f_xeditorialboard = new CFieldXEditorialBoard(s_field) ;
      if (f_xeditorialboard->s == FALSE) { type_of_entry = MISC ;}
    }
  if  (field_name == "X-INVITED-CONFERENCE" )
    {
      f_xinvitedconference = new CFieldXInvitedConference(s_field) ;
    if (cnf->generate_invited_pages == true)
      type_of_entry = INVITED ;
    }

  if  (field_name == "X-PROCEEDINGS" )
    {
      f_xproceedings = new CFieldXProceedings(s_field) ;
      // objectivement je sais pas trop quoi en faire de ceux la...
   }
  
  if (field_name == "X-INTERNATIONAL-AUDIENCE")
    { 
     f_xinternationalaudiance = new CFieldXInternationalAudience(s_field) ;
     if (f_xinternationalaudiance->s ==FALSE)
       {
	 if (type_of_entry == INPROCEEDINGS)
	   {
	    if (cnf->generate_national_conferences_pages == true)
	      type_of_entry = CONFNAT ;
	   }
	 if (type_of_entry == JOURNAL)
	   {
	    if (cnf->generate_national_journals_pages == true)
	      type_of_entry = JOURNALNAT ;
	   }
       }
    }

  if (cnf->generate_popularization_pages == true)
    if (field_name == "X-SCIENTIFIC-POPULARIZATION")
      { 
	f_xscientificpopularization = new CFieldXScientificPopularization(s_field) ;  
	type_of_entry = POPULARIZATION ;
	
      }


  if  (field_name == "HDR" )
  {
    f_hdr = new CFieldHDR(s_field) ;
  }
  if (cnf->generate_national_conferences_pages == true)
    if  (field_name == "CONFNAT" )
      {
	cout << "confnat Deprecated " << endl ;
	f_confnat = new CFieldConfnat(s_field) ;
	type_of_entry = CONFNAT ;
      }
  if  (field_name == "RA" )
  {
    f_ra = new CFieldRA(s_field) ;
  }
  if  (field_name == "TOAPPEAR" )
  {
    f_toappear = new CFieldToAppear(s_field) ;
  }
  if (cnf->generate_workshop_pages==true)
    if  (field_name == "WORKSHOP" )
    {
      f_workshop = new CFieldWorkshop(s_field) ;
      type_of_entry = WORKSHOP ;
    }

  if  ((field_name == "KEYWORD" ) ||(field_name == "KEYWORDS" ))
  {
    f_keyword = new CFieldKeyword(s_field) ;
    if (cnf->all_keyword == true)
    {

      f_keyword->LKeyword.Front() ;
      while(!f_keyword->LKeyword.Outside())
      {
	string can= f_keyword->LKeyword.Value() ;

	cnf->AddKeyword(can) ;
	f_keyword->LKeyword.Next() ;

      }
    }
  }

  if  ((field_name == "CROSSREF" )
       || (field_name == "CITES" )
       ||(field_name == "PRECEDES" )
       ||(field_name == "SUCCEEDS" )
       ||(field_name == "SA" )
       ||(field_name == "SEEALSO" ))
  {
    f_crossref = new CFieldCrossref(s_field) ;
  }

  // --------------------------------------------------------
  // Pages
  if (field_name == "PAGES" )
  {
    f_pages = new CFieldPages(s_field) ;
    if ((f_pages->pe ==0) && (f_pages->pf==0))
      {
	delete f_pages ;
	f_pages = NULL ;
      }
  }
  //--------------------------------------------------------
  // Month
  if (field_name == "MONTH" )
  {
    f_month  = new CFieldMonth(s_field, cnf) ;
  }


  if (DEBUG_LEVEL1)
    cout << "end  CEntry::ReadNextField(string &s)" <<endl ;
  // int a ;   cin>>a ;
  return 1 ;
}

int
CEntry::ExtractFields(string &s)
{
 if (DEBUG_LEVEL1)
    cout << "begin  CEntry::ExtractFields(string &s)" <<endl ;

  s_entry =s ;

  char sTAB[3] ;
  sprintf(sTAB,"\r") ;
  string TAB(sTAB) ;

  gsub(s_entry,TAB," ") ;
  gsub(s_entry,"  "," ") ;
  GetKey(s_entry) ;

  if (DEBUG_LEVEL2)
    cout << "Key : " << key <<endl ;
  string tmp1,tmp2 ;
  after(s_entry,key,tmp1) ;
  after(tmp1,",",tmp2) ;

  beforelast(tmp2,"}", s_entry) ;

  string snb ;
  suppress_white_and_tab(s_entry,snb) ;
  while (snb.length() != 0)
  {
    ReadNextField(s_entry) ;
    suppress_white_and_tab(s_entry,snb) ;
  }

  if (f_year == NULL)
  {
    string s = "0" ;
    f_year = new CFieldYear(s) ;
  }
 if (DEBUG_LEVEL1)
    cout << "end  CEntry::ExtractFields(string &s)" <<endl ;
    return 1 ;
}




string
CEntry::CreateBibtex()
{
  string s ;
  if (f_author != NULL) s += "\t"+ f_author->PrintBIBTEX()  + ",\n"  ;
  if (f_title != NULL)    s += "\t"+ f_title->PrintBIBTEX() + ",\n"  ;
  if (f_journal!= NULL) s +="\t"+  f_journal->PrintBIBTEX()  + ",\n"  ;
  if (f_booktitle!= NULL) s +="\t"+  f_booktitle->PrintBIBTEX()  + ",\n"  ;
  if (f_howpublish!= NULL) s +="\t"+  f_howpublish->PrintBIBTEX()  + ",\n"  ;
  if (f_editor!= NULL) s +="\t"+  f_editor->PrintBIBTEX()  + ",\n"  ;
  if (f_volume!= NULL) s +="\t"+  f_volume->PrintBIBTEX()  + ",\n"  ;
  if (f_number!= NULL) s +="\t"+  f_number->PrintBIBTEX()  + ",\n"  ;
  if (f_chapter!= NULL) s +="\t"+  f_chapter->PrintBIBTEX()  + ",\n"  ;
  if (f_pages!= NULL) s +="\t"+  f_pages->PrintBIBTEX()  + ",\n"  ;
  if (f_series!= NULL) s +="\t"+  f_series->PrintBIBTEX()  + ",\n"  ;
  if (f_publisher!= NULL) s +="\t"+  f_publisher->PrintBIBTEX()  + ",\n"  ;
  if (f_school!= NULL) s +="\t"+  f_school->PrintBIBTEX()  + ",\n"  ;
  if (f_institution!= NULL) s +="\t"+  f_institution->PrintBIBTEX()  + ",\n"  ;
  if (f_address != NULL)    s +="\t"+ f_address->PrintBIBTEX() + ",\n " ;
  //if (f_abstract != NULL)     s +="\t"+ f_abstract->PrintBIBTEX()  + ",\n" ;
  // if (f_url != NULL)     s +="\t"+ f_url->PrintBIBTEX()  + ",\n" ;
  if (f_month != NULL)    s +="\t"+ f_month->PrintBIBTEX()  + ",\n" ;
  if (f_year != NULL)     s +="\t"+ f_year->PrintBIBTEX()  + "\n" ;

  return s ;
}

string
CEntry::CreateEE()
{
  string s ;
  s += "%F " + key +"\n" ;
  if (f_author != NULL) s +=  f_author->PrintEE()    ;
  if (f_title != NULL)    s +=  f_title->PrintEE() + "\n"  ;
  if (f_journal!= NULL) s +=  f_journal->PrintEE()  + "\n"  ;
  if (f_booktitle!= NULL) s +=  f_booktitle->PrintEE()  + "\n"  ;
  if (f_howpublish!= NULL) s +=  f_howpublish->PrintEE()  + "\n"  ;
  if (f_editor!= NULL) s +=  f_editor->PrintEE()    ;
  if (f_volume!= NULL) s +=  f_volume->PrintEE()  + "\n"  ;
  if (f_number!= NULL) s +=  f_number->PrintEE()  + "\n"  ;
  if (f_chapter!= NULL) s +=  f_chapter->PrintEE()  + "\n"  ;
  if (f_pages!= NULL) s +=  f_pages->PrintEE()  + "\n"  ;
  if (f_series!= NULL) s +=  f_series->PrintEE()  + "\n"  ;
  if (f_publisher!= NULL) s +=  f_publisher->PrintEE()  + "\n"  ;
  if (f_school!= NULL) s +=  f_school->PrintEE()  + "\n"  ;
  if (f_institution!= NULL) s +=  f_institution->PrintEE()  + "\n"  ;
  if (f_address != NULL)    s += f_address->PrintEE() + "\n" ;
  if (f_abstract != NULL)     s += f_abstract->PrintEE()  + "\n" ;
  if (f_url != NULL)     s += f_url->PrintEE()  + "\n" ;
  if (f_doi != NULL)     s += f_doi->PrintEE()  + "\n" ;
  if (f_month != NULL)    s += f_month->PrintEE()  + "\n" ;
  if (f_year != NULL)     s += f_year->PrintEE()  + "\n" ;
  if (f_keyword != NULL)     s += f_keyword->PrintEE()  + "\n" ;

  s+= "\n\n" ;
  return s ;
}

int
CEntry::Contact(string &s)
{
  int k=0 ;
  if (f_author != NULL)
  {
  f_author->LName.Front() ;
  while(!f_author->LName.Outside())
  {
    CName fn = f_author->LName.Value() ;

    cnf->LAuthor.Front() ;
    while (!cnf->LAuthor.Outside())
    {
      CConfigAuthor n = cnf->LAuthor.Value() ;
      if ((upcase(fn.last) == upcase(n.name) ) &&(((upcase(fn.first))[0] == n.I)))
      {
	if (n.email!="") s+="<a href=\"mailto:"+n.email+"\">"  ;
	s +=  n.given_name + "  " +n.name  ;
	if (n.email!="") s+="</a> "  ;
	if (n.url!="")
	{

	  s+=" <a href=\""+n.url+"\">"  ;
	  if (cnf->url_icon_html=="") s +=  n.url   ;
	  else   s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_html)+"\" align=top border=0 alt =\"\">" ;
	  if (n.url!="") s+="</a>"  ;
	}
	s+="<br> \n" ;

	k++ ;
      }
      cnf->LAuthor.Next() ;
    }
    f_author->LName.Next() ;
  }
  }
  return k ;

}


int
CEntry::Download(string &url, string &s)
{
  unsigned int pos ;

      pos = url.find(".pdf",0) ;
      string ic = "" ;
      if (pos!=string::npos)
	{
	  if (suppress_white_and_tab(cnf->url_icon_pdf)!= "")
	    {
	      s+= " Adobe portable document (pdf) <a href=\""+url+"\">" ;
	      s += "<img src=\""+suppress_white_and_tab(cnf->url_icon_pdf)+"\" align=top border=0 alt =\"pdf\">" ;
	      s+="</a>\n" ;
	    }
	  else
	    s+= " Adobe portable document  (<a href=\""+url+"\">pdf</a>)\n" ;
	  Compressed(url,s) ;
	  return OK ;
	}
      pos = url.find(".ps.gz",0) ;
      if (pos!=string::npos)
	{
	  if (suppress_white_and_tab(cnf->url_icon_ps)!= "")
	    {
	      s+= " Gziped Postscript <a href=\""+url+"\">" ;
	      s += "<img src=\""+suppress_white_and_tab(cnf->url_icon_ps)+"\" align=top border=0 alt =\"\">" ;
	      s+="</a>\n" ;
	    }
	  else
	    s+= " Gziped Postscript (<a href=\""+url+"\">.ps.gz</a>)\n" ;
	  Compressed(url,s) ;
	  return OK ;
	}

      pos = url.find(".ps.Z",0) ;
      if (pos!=string::npos)
	{
	  if (suppress_white_and_tab(cnf->url_icon_ps)!= "")
	    {
	      s+= "Ziped Postscript <a href=\""+url+"\">" ;
	      s += "<img src=\""+suppress_white_and_tab(cnf->url_icon_ps)+"\" align=top border=0 alt =\"\">" ;
	      s+="</a>\n" ;
	    }
	  else
	    s+= " Ziped Postscript (<a href=\""+url+"\">.ps.Z</a>)\n" ;
	}

      pos = url.find(".doc",0) ;
      if (pos!=string::npos)
	{
	  s+= " <a href=\""+url+"\">" ;
	  if (suppress_white_and_tab(cnf->url_icon_word)!= "")
	    s += " Microsoft Word <img src=\""+suppress_white_and_tab(cnf->url_icon_word)+"\" align=top border=0 alt =\"\">" ;
	  else
	    s+= " Microsoft Word (<a href=\""+url+"\">.doc</a>)\n" ;
	  Compressed(url,s) ;
	  return OK ;
	}

      pos = url.find(".ppt",0) ;
      if (pos!=string::npos)
	{
	  s+= " <a href=\""+url+"\">" ;
	  if (suppress_white_and_tab(cnf->url_icon_ppt)!= "")
	    s += " Microsoft powerpoint <img src=\""+suppress_white_and_tab(cnf->url_icon_ppt)+"\" align=top border=0 alt =\"\">" ;
	  else
	    s+= " Microsoft powerpoint (<a href=\""+url+"\">.ppt</a>)\n" ;
	  Compressed(url,s) ;
	  return OK ;
	}

      pos = url.find(".ps",0) ;
      if (pos!=string::npos)
	{
	  if (suppress_white_and_tab(cnf->url_icon_ps)!= "")
	    {
	      s+= "Postscript (<a href=\""+url+"\">" ;
	      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_ps)+"\" align=top border=0 alt =\"\">" ;
	      s+="</a>)\n" ;
	    }
	  else
	    s+= " Postscript (<a href=\""+url+"\">.ps</a>)\n" ;

	  return OK ;
	}

      pos = url.find("doi.org",0) ;
      if (pos!=string::npos)
	{
	  if (suppress_white_and_tab(cnf->url_icon_ps)!= "")
	    {
	      s+= "Doi page <a href=\""+url+"\">" ;
	      s += "<img src=\""+suppress_white_and_tab(cnf->url_icon_doi)+"\" align=top border=0 alt =\"\">" ;
	      s+="</a>\n" ;
	    }
	  else
	    s+= " Doi page (<a href=\""+url+"\">doi</a>)\n" ;
	  return OK ;
	}

      unsigned int pos1 = url.find(".html",0) ;
      unsigned int pos2 = url.find(".htm",0) ;
      if ((pos1!=string::npos) || (pos2!=string::npos))
	{
	  if (suppress_white_and_tab(cnf->url_icon_html)!= "")
	    {
	      s+= " Follow the link <a href=\""+url+"\">" ;
	      s += "<img src=\""+suppress_white_and_tab(cnf->url_icon_html)+"\" align=top border=0 alt =\"\">" ;
	      s+="</a>\n" ;
	    }
	  else
	    s+= " Follow the  (<a href=\""+url+"\">link</a>)\n" ;
	  return OK ;
	}

      s+= " (<a href=\""+url+"\">link</a>)\n" ;
      return OK ;
}

int CEntry::Compressed(string &url, string &s)
{
  if (suppress_white_and_tab(cnf->url_icon_compressed)!= "")
  {
    unsigned int pos1, pos2 ;
    pos1 = url.find(".Z",0) ;
    pos2 = url.find(".gz",0) ;

   if ((pos1!=string::npos) || (pos2!=string::npos))
    {
      s+= " <a href=\""+url+"\">" ;
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_compressed)+"\" align=top border=0 alt =\"\">" ;
      s+= "</a>\n" ;
      return OK ;
    }
  }
  return OK ;
}
int
CEntry::DownloadIcon(string &url, string &s)
{
  unsigned int pos ;  string tmp =url ;
  suppress_white_and_tab(tmp) ;
   if (tmp.length()!=0)
    {
  pos = url.find(".pdf",0) ;

  if (pos!=string::npos)
  {
    s+= " <a href=\""+url+"\">" ;
    if (suppress_white_and_tab(cnf->url_icon_pdf)!= "")
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_pdf)+"\" align=top border=0 alt =\"pdf\">" ;
      else
	s += "pdf" ;
    s+= "</a>\n" ;
    Compressed(url,s) ;
    return OK ;
  }

  pos = url.find(".ps",0) ;
  if (pos!=string::npos)
  {
    s+= " <a href=\""+url+"\">" ;
    if (suppress_white_and_tab(cnf->url_icon_ps)!= "")
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_ps)+"\" align=top border=0 alt =\"ps\">" ;
    else
      s += "ps" ;
    s+= "</a>\n" ;
    Compressed(url,s) ;
    return OK ;
 }

  pos = url.find("doi.org",0) ;
  if (pos!=string::npos)
  {
    s+= " <a href=\""+url+"\">" ;
    if (suppress_white_and_tab(cnf->url_icon_doi)!= "")
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_doi)+"\" align=top border=0 alt =\"doi\">" ;
    else
      s += "doi" ;
    s+= "</a>\n" ;
    return OK ;
  }

  pos = url.find(".doc",0) ;
  if (pos!=string::npos)
  {
    s+= " <a href=\""+url+"\">" ;
    if (suppress_white_and_tab(cnf->url_icon_word)!= "")
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_word)+"\" align=top border=0 alt =\"doc\">" ;
    else
      s += "doc" ;
    s+= "</a>\n" ;
    Compressed(url,s) ;
    return OK ;
  }

  pos = url.find(".ppt",0) ;
  if (pos!=string::npos)
  {
    s+= " <a href=\""+url+"\">" ;
    if (suppress_white_and_tab(cnf->url_icon_ppt)!= "")
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_ppt)+"\" align=top border=0 alt =\"\">" ;
    else
      s += "ppt" ;
    s+= "</a>\n" ;
    Compressed(url,s) ;
    return OK ;
  }

  unsigned int pos1 = url.find(".html",0) ;
  unsigned int pos2 = url.find(".htm",0) ;
  if ((pos1!=string::npos) || (pos2!=string::npos))
  {
    s+= " <a href=\""+url+"\">" ;
    if (suppress_white_and_tab(cnf->url_icon_html)!= "")
      s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_html)+"\" align=top border=0 alt =\"ppt\">" ;
    else
      s += "download" ;
    s+= "</a>\n" ;
    return OK ;
  }

  s+= " <a href=\""+url+"\">" ;
  s += "download" ;
  s+= "</a>\n" ;}
  return OK ;

}

int
CEntry::DownloadArxiv(string &url, string &s)
{
  s+= " <a href=\""+url+"\">" ;
  if (suppress_white_and_tab(cnf->url_icon_arxiv)!= "")
    s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_arxiv)+"\" align=top border=0 alt =\"\">" ;
  else
    s += "arxiv" ;
  s+= "</a>\n" ;
  Compressed(url,s) ;
  
  return OK ;

}

int CEntry::CheckKeyword(CConfig *cnf)
{
  if (f_keyword !=NULL)
  {
    f_keyword->LKeyword.Front() ;
    while (!f_keyword->LKeyword.Outside())
    {
      string keyword = suppress_white_and_tab(f_keyword->LKeyword.Value()) ;
      cnf->LKeyword.Front() ;
      bool findkeyword ;
      findkeyword = false ;
      while (!cnf->LKeyword.Outside())
      {
      string cnfkey = suppress_white_and_tab(cnf->LKeyword.Value().key) ;
      if (upcase(cnfkey)==upcase(keyword))
	findkeyword = true ;
      cnf->LKeyword.Next() ;
      }
      if (findkeyword == false)
      {
	f_keyword->LKeyword.Suppress() ;
      }
      else
	f_keyword->LKeyword.Next() ;
    }

    if (f_keyword->LKeyword.NbElement() ==0)
    {
      delete f_keyword ;
      f_keyword = NULL ;
    }
  }
  return OK ;
}


void
CEntry::CreatePublicationPage(ofstream &f)
{

  CheckKeyword(cnf) ;

  string keyee = cnf->directory_base +"/" +cnf->directory_publi +"/" + suppress_white_and_tab(key)+ ".ref" ;

  //  cnf->language = LANGUAGE1 ;

  ofstream fee(keyee.c_str()) ;
  if (fee==NULL) cout << "cannot open file "<< keyee <<endl ;

  keyee = cnf->base_http +"/" +cnf->directory_publi +"/" +suppress_white_and_tab(key)+ ".ref" ;
  string s ;
  s = "" ;

  PageBegin(f, cnf) ;


  string s_tmp ;
  s = "" ;
  if (cnf->language == LANGUAGE2)
  {
    s+= "<p><center> Accès aux " ;
    if ((f_url != NULL) ||
	(f_arxiv != NULL) || 
	(f_urltransp != NULL) ||
	(f_urlinterne != NULL))
      s += "<a href=\"#download\"> Téléchargement</a> | " ;
    if (f_xmisc != NULL) s += "<a href=\"#note\"> Notes</a> | " ;
    if (f_abstract != NULL) s += "<a href=\"#abstract\"> Résumé</a> | " ;
    if (f_crossref != NULL)
      s+= "<a href=\"#crossref\"> Autres articles</a> | " ;
    if (f_keyword != NULL)
    {
      if (f_keyword->LKeyword.NbElement()>1)
	s+= "<a href=\"#keyword\"> Mots-clés</a> | " ;
      else
	s+= "<a href=\"#keyword\"> Mot-clé</a> | " ;
    }
    if (cnf->author_create_pages!=false)
      if (f_author != NULL) s += "<a href=\"#contact\"> Contact</a> | " ;

    s += "<a href=\"#bib\"> Référence BibTex</a> | " ;
    s += "<a href=\"#ee\"> Référence EndNote </a> | " ;
    s += "</center>" ;
  }
  else
  {
    s+= "<p><center> Jump to : " ;
    if ((f_arxiv != NULL) ||
	(f_url != NULL) ||
	(f_urltransp != NULL) ||
	(f_urlinterne != NULL))
      s += "<a href=\"#download\"> Download</a> | " ;
    if (f_xmisc != NULL) s += "<a href=\"#note\"> Note</a> | " ;
    if (f_abstract != NULL) s += "<a href=\"#abstract\"> Abstract</a> | " ;
    if (f_crossref != NULL)
      s+= "<a href=\"#crossref\"> See also</a> | " ;
    if (f_keyword != NULL)
    {
      if (f_keyword->LKeyword.NbElement()>1)
	s+= "<a href=\"#keyword\"> Keywords</a> | " ;
      else
	s+= "<a href=\"#keyword\"> Keyword</a> | " ;
    }
    if (cnf->author_create_pages!=false)
      if (f_author != NULL) s += "<a href=\"#contact\"> Contact</a> | " ;

    s += "<a href=\"#bib\"> BibTex reference</a> | " ;
    s += "<a href=\"#ee\"> EndNote reference</a> | " ;
    s += "</center>" ;
  }
  f << s << endl ;

  s = "" ;
  s+= "<p> <h1> " + key + "</h1>\n " ;

  PrintHTML(s_tmp) ;
  suppress_brace(s_tmp) ;

  s+= "<p>"+ s_tmp + "</P><p>\n<p>" ;

  f << s << endl ;

  // Download
  if ((f_arxiv != NULL) ||
      (f_url != NULL) ||
      (f_urltransp != NULL) ||
      (f_urlinterne != NULL))
  {
    s = "" ;

    if (cnf->language==LANGUAGE2)
    {
      s += "<a name=\"download\"></a><h2> Télécharger l'article " ;
      if (cnf->url_download_help.length() != 0) s+= " [<a href=\""+cnf->url_download_help+ "\">Aide</a>] " ;
    }
    else{
      s += "<a name=\"download\"></a><h2> Download " ;
      if (cnf->url_download_help.length() != 0) s+= " [<a href=\""+cnf->url_download_help+ "\">help</a>] " ;
    }
    s+= "</h2> <P> \n" ;
    f << s << endl ;
    if (f_doi != NULL)
    {
      s = "" ;
      if (cnf->language==LANGUAGE2)
	s+= "<b>Charger l'article : </b> \n" ;
      else
	s+= "<b>Download paper: </b> \n" ;

      Download(f_doi->s, s) ;
      s+= "<p>" ;
      f << s << endl ;
    } 
    if (f_arxiv != NULL)
    {
      s = "" ;
      if (cnf->language==LANGUAGE2)
	s+= "<b>Charger l'article sur Arxiv: </b> \n" ;
      else
	s+= "<b>Download Arxiv paper: </b> \n" ;

      Download(f_arxiv->s, s) ;
      s+= "<p>" ;
      f << s << endl ;
    }
    if (f_url != NULL)
    {
      s = "" ;
      if (cnf->language==LANGUAGE2)
	s+= "<b>Charger l'article : </b> \n" ;
      else
	s+= "<b>Download paper: </b> \n" ;

      Download(f_url->s, s) ;
      s+= "<p>" ;
      f << s << endl ;
    }
    if (f_urlinterne != NULL)
    {
      s = "" ;

      if (cnf->language==LANGUAGE2)
	s += "<b>Charger l'article (Accès limité) </b>  \n" ;
      else
	s += "<b>Download paper (restricted access) </b>  \n" ;
      Download(f_urlinterne->s, s) ;

      if (suppress_white_and_tab(cnf->url_icon_key) != "")
	s += " <img src=\""+suppress_white_and_tab(cnf->url_icon_key)+"\" align=bottom alt =\"\">" ;
      else
    if (cnf->language==LANGUAGE2)
      s += " Accès en interne seulement (demander l'article pas mél)" ;
    else
      s += " restricted (send us a email)" ;

      s+="<P> \n" ;

      f << s << endl ;
    }
    // Download
    if (f_urltransp != NULL)
    {
      s = "" ;

      if (cnf->language==LANGUAGE2)
	s += "<b>Download slides  </b>  \n" ;
      else
	s += "<b>Download slides  </b>  \n" ;
      Download(f_urltransp->s, s) ;
      s+= "<p>" ;

      f << s << endl ;

    }
    s = "" ;
    if (f_url != NULL)
    {
      if (cnf->language==LANGUAGE2)
	s += "<p><b>Copyright :</b>" + cnf->copyright_notice_language2 + "<p>" ;
      else
	s += "<p><b>Copyright notice:</b>" + cnf->copyright_notice_language1 + "<p>" ;
    }
    f << s << endl ;

  }

  // notes
  if (f_xmisc != NULL)
  {
    s = "" ;
     if (cnf->language==LANGUAGE2)
       s += "<a name=\"note\"></a><h2> Informations supplémentaires  </h2> <P> \n" ;
     else
       s += "<a name=\"note\"></a><h2> Note on this paper  </h2> <P> \n" ;
    s+= f_xmisc->s + "<p>" ;
    f << s << endl ;
  }
  // Abstract
  if (f_abstract != NULL)
  {
    s = "" ;
    if (cnf->language==LANGUAGE2)
      s += "<a name=\"abstract\"></a><h2> Résumé  </h2> <P> \n" ;
    else
      s += "<a name=\"abstract\"></a><h2> Abstract  </h2> <P> \n" ;

    s+= f_abstract->s + "<p>" ;
  f << s << endl ;
  }

  if (f_crossref != NULL)
  {
    s = " " ;
    if (cnf->language==LANGUAGE2)
      s+= "<a name=\"crossref\"></a> <h2>Autres références </h2> <p>" ;
    else
      s+= "<a name=\"crossref\"></a> <h2>See also </h2> <p>" ;

    f_crossref->LCrossref.Front() ;
    while (!f_crossref->LCrossref.Outside())
    {
      string crossref = f_crossref->LCrossref.Value() ;

      s+= "[ " ;
      s+= "<a href=\"" + cnf->base_http	+"/" + cnf->directory_publi
	+"/" ;
      s+= crossref ;
      if (cnf->language ==LANGUAGE1)
	s+= cnf->language1_postfix ;
      else
	s+= cnf->language2_postfix ;
      s+= cnf->html_postfix +  "\">" ;
      s+= crossref ;
      s+= "</a>" ;
      s+= " ] " ;
      f_crossref->LCrossref.Next() ;
    }
    f << s << endl ;
  }
  if (f_keyword != NULL)
  {
    s = " " ;
    if (cnf->language==LANGUAGE2)
    {
      if (f_keyword->LKeyword.NbElement()>1)
	s+= "<a name=\"keyword\"></a> <h2>Mots-clés </h2> <p> " ;
      else
	s+= "<a name=\"keyword\"></a> <h2>Mot-clé</h2>  <p> " ;
    }
    else
    {
      if (f_keyword->LKeyword.NbElement()>1)
	s+= "<a name=\"keyword\"></a> <h2>Keywords </h2> <p> " ;
      else
	s+= "<a name=\"keyword\"></a> <h2>Keyword</h2>  <p>" ;
    }
    f_keyword->LKeyword.Front() ;
    bool url ;
    if (cnf->keyword_create_pages) url = true ; else url = false ;
    while (!f_keyword->LKeyword.Outside())
    {
      string keyword  ;
      keyword = f_keyword->LKeyword.Value() ;

      if (url==false)
	s+= "[ " + maj( keyword) + " ] " ;
      else
      {
 	s+= "[ " ;
	s+= "<a href=\"" + cnf->base_http +"/" + cnf->directory_keyword +"/" ;
	if (cnf->language == LANGUAGE1)
	  s+= lowcase(suppress_white_and_tab(keyword))+cnf->language1_postfix + cnf->html_postfix +  "\">" ;
	else
	  s+= lowcase(suppress_white_and_tab(keyword))+cnf->language2_postfix + cnf->html_postfix +  "\">" ;

	s+= maj(keyword) ;
	s+= "</a>" ;
	s+= " ] " ;
      }
     f_keyword->LKeyword.Next() ;
    }
    f << s << endl ;
 }


  if (cnf->author_create_pages !=false)  if (f_author !=NULL)
  {
    s="" ;
    s_tmp = "" ;
    int k =Contact(s_tmp) ;
    if (k!=0)
    {
      // Contact
      s = "" ;
      s += "<a name=\"contact\"></a><h2> Contact  </h2> <P> \n" ;
      s+=s_tmp ;
      //flush
      f << s << endl ;
    }
  }

  s = "" ;
    if (cnf->language==LANGUAGE2)
      s += "<a name=\"bib\"></a><h2> Référence BibTex  </h2> <P> \n" ;
    else
      s += "<a name=\"bib\"></a><h2> BibTex Reference  </h2> <P> \n" ;
  PrintBIBTEX(s_tmp) ;
  gsub(s_tmp,"\n","<br>") ;
  gsub(s_tmp,"\t","&nbsp;&nbsp;&nbsp;") ;
  s += s_tmp + "<p>" ;

  //flush
  f << s << endl ;

  s = "" ;
    if (cnf->language==LANGUAGE2)
      s += "<a name=\"ee\"></a><h2> Référence EndNote [<a href=\"http://www.endnote.com\">help</a>] </h2> <P> \n" ;
    else
      s += "<a name=\"ee\"></a><h2> EndNote Reference [<a href=\"http://www.endnote.com\">help</a>] </h2> <P> \n" ;
    {
      s_tmp ="" ;
      PrintEE(s_tmp) ;
      fee << s_tmp <<endl ;
    }

    if (cnf->language==LANGUAGE2)
      s += "Charger la référence EndNote (<a href=\""+keyee+"\">.ref</a>) <p>" ;
    else
      s += "Get EndNote Reference (<a href=\""+keyee+"\">.ref</a>) <p>" ;

  f << s << endl ;
  PageEndNoCopyright(f,cnf) ;

  fee.close() ;
}
