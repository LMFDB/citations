#include <cctype>
#include <stdio.h>

#include <include/constant.h>

#include <entry/CEntry.h>
#include <entry/CVariousEntry.h>
#include <tools/String.h>

#define DEBUG_LEVEL2 1


//--------------------------------------------------------------------
int
CEntryPhdThesis::CheckValidity()
{
  if (f_title == NULL)
    cout <<"Field title  is missing " <<endl ;
  if (f_school == NULL)
    cout <<"Field school is missing " <<endl ;
  if (f_number == NULL)
    cout <<"Field number is missing " <<endl ;
  if (f_month == NULL)
    cout <<"Field month is missing " <<endl ;
  if (f_year == NULL)
    cout <<"Field year is missing " <<endl ;

  return OK ;
}
void
CEntryPhdThesis::Print(string &s)
{
  int hdr = FALSE ;;
  string name ;
  if (f_author !=NULL)
    f_author->Print(name) ;
  s += name + ". " ;
  if (f_title != NULL)
  {
    s += f_title->s + ". " ;
  }

  if (f_type!=NULL)
  {
    string st ;
    st = upcase(f_type->s) ;
    unsigned int pos ;
    pos = st.find("HDR",0) ;
    if (pos != string::npos) 	hdr = TRUE ;
   pos = st.find("HABILITATION",0) ;
    if (pos != string::npos) 	hdr = TRUE ; 
  }

  if (f_hdr!= NULL)  hdr = TRUE ;

  if (hdr==TRUE)
  {
    s += "Habilitation à diriger des recherches " ;
  }
  else
  {
    s += "Thèse " ;
  }
  if (f_school != NULL)  s+= "de l'" + f_school->s + ", " ;
  if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
  if (f_address!= NULL)  s +=  f_address->s + ", " ;


  if (f_month != NULL)
  {
    if (cnf->language==FRENCH)
      s += f_month->s_french + " ";
    else
      s += f_month->s_english + " ";
  }
  if (f_year != NULL)     s += itoa(f_year->s) +".";

}

void
CEntryPhdThesis::PrintLATEX(string &s)
{
  int hdr = FALSE ;;
  string name ;
  if (f_author !=NULL)
    f_author->Print(name) ;
  s += name + ". " ;
  if (f_title != NULL)
  {
    s += "{\\em "+f_title->s + "}. " ;
  }

  if (f_type!=NULL)
  {
    string st ;
    st = upcase(f_type->s) ;
    unsigned int pos ;
    pos = st.find("HDR",0) ;
    if (pos != string::npos) 	hdr = TRUE ;
  }

  if (f_hdr!= NULL)  hdr = TRUE ;

  if (hdr==TRUE)
  {
    s += "Habilitation à diriger les recherches " ;
  }
  else
  {
    s += "Thèse " ;
  }
  if (f_school != NULL)  s+= "de l'" + f_school->s + ", " ;
  if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
  if (f_address!= NULL)  s +=  f_address->s + ", " ;


  if (f_month != NULL)
  {
    if (cnf->language==FRENCH)
      s += f_month->s_french + " ";
    else
      s += f_month->s_english + " ";
  }
  if (f_year != NULL)     s += itoa(f_year->s) +".";

}

void
CEntryPhdThesis::PrintHTML(string &s)
{
  int hdr= FALSE ;
  string name ;
  if (f_author !=NULL)
    f_author->Print(name) ;


  s += "<span class=\"BibAuthor\">" ;
  s += name + "</span>. " ;
  if (f_title != NULL)
  {
      s += "<span class=\"BibPhDThesisTitle\">" ;
      s += f_title->s + "</span>. " ;
  }

    if (f_type!=NULL)
    {
      string st ;
      st = upcase(f_type->s) ;
      unsigned int pos ;
      pos = st.find("HDR",0) ;
      if (pos != string::npos)
	hdr = TRUE ;
    }

    s += "<span class=\"BibPhDThesisSchool\">" ;
   if (f_hdr!=NULL)
      hdr = TRUE  ;
    if (hdr==TRUE)
    {
      s += "Habilitation à diriger des recherches" ;
    }
    else
    {
      if(cnf->language == FRENCH)
	s += "Thèse"  ;
      else
	s += "PhD Thesis" ;
    }

    if (f_school != NULL)
    {
      s += " " ;
      if(cnf->language == FRENCH)
	s += "de l'"  ;
      s +=  f_school->s;
    }
    s +=   "</span>, " ;

    if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
   if ((f_addresse != NULL) && (f_address != NULL))
    {
      if (cnf->language==FRENCH)
	s +=  f_addresse->s+ ", " ;
      else
	s +=  f_address->s+ ", " ;
    }
    else   if ( (f_address != NULL))
    {
	s +=  f_address->s+ ", " ;
    }

    if (f_month != NULL)
    {
      if (cnf->language==FRENCH)
	s += f_month->s_french + " ";
      else
	s += f_month->s_english + " ";
    }
    if (f_year != NULL)     s += itoa(f_year->s) +".";

}


void
CEntryPhdThesis::PrintBIBTEX(string &s)
{
  int hdr = FALSE;

  if (f_type!=NULL)
  {
    string st ;
    st = upcase(f_type->s) ;
    unsigned int pos ;
    pos = st.find("HDR",0) ;
    if (pos != string::npos)
      hdr = TRUE ;
  }

  if (f_hdr!=NULL)
    hdr = TRUE  ;

  s += "@PhdThesis{" + key +", \n" ;
  s += CreateBibtex() ;
  if (hdr==TRUE)
    {
      s += "\ttype = {Habilitation à diriger les recherches}, \n " ;
    }
  s+= "} \n"  ;
}


void
CEntryPhdThesis::PrintEE(string &s)
{
  int hdr = FALSE;

  if (f_type!=NULL)
  {
    string st ;
    st = upcase(f_type->s) ;
    unsigned int pos ;
    pos = st.find("HDR",0) ;
    if (pos != string::npos)
      hdr = TRUE ;
  }

  s += "%O Thesis \n" ;
  if (hdr==TRUE)
    s+= "%9 HDR \n" ;
  else
    s += "%9 PhdThesis \n" ;
  s += CreateEE() ;
}
