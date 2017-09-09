#include <cctype>
#include <stdio.h>

#include <include/constant.h>

#include <entry/CEntry.h>
#include <entry/CVariousEntry.h>
#include <tools/String.h>

#define DEBUG_LEVEL2 1


//--------------------------------------------------------------------
int
CEntryMasterThesis::CheckValidity()
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
CEntryMasterThesis::Print(string &s)
{

    string name ;
    if (f_author !=NULL)
    f_author->Print(name) ;


    s += name + ", " ;
    if (f_title != NULL)
    {
      s += f_title->s + ". " ;
    }
    if (cnf->language==LANGUAGE2) s+= cnf->master_language2+" " ;
    else
      s+= cnf->master_language1+" " ;
    if (f_school != NULL)  s +=  f_school->s + ", " ;
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
    if (f_address!= NULL)  s +=  f_address->s + ", " ;


    if (f_month != NULL)
    {
      if (cnf->language==LANGUAGE2)
	s += f_month->s_french + " ";
      else
	s += f_month->s_english + " ";
    }
    if (f_year != NULL)     s += itoa(f_year->s) +".";

}

void
CEntryMasterThesis::PrintLATEX(string &s)
{

    string name ;
    if (f_author !=NULL)
    f_author->Print(name) ;


    s += name + ", " ;
    if (f_title != NULL)
    {
      s += "{\\em "+ f_title->s + "}. " ;
    }
    if (cnf->language==LANGUAGE2) s+= cnf->master_language2+" " ;
    else
      s+= cnf->master_language1+" " ;  if (f_school != NULL)  s +=  f_school->s + ", " ;
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
    if (f_address!= NULL)  s +=  f_address->s + ", " ;


    if (f_month != NULL)
    {
      if (cnf->language==LANGUAGE2)
	s += f_month->s_french + " ";
      else
	s += f_month->s_english + " ";
    }
    if (f_year != NULL)     s += itoa(f_year->s) +".";

}

void
CEntryMasterThesis::PrintHTML(string &s)
{

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
    if (f_school != NULL)
    {
      s += "<span class=\"BibPhDThesisSchool\">" ;  
      if (cnf->language==LANGUAGE2) s+= cnf->master_language2+" " ;
      else
	s+= cnf->master_language1+" " ;
      if(cnf->language == LANGUAGE2)
	s += f_school->s + "</span>, " ;
      else
	s += f_school->s + "</span>, " ;
    }

    if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;

    if ((f_addresse != NULL) && (f_address != NULL))
    {
      if (cnf->language==LANGUAGE2)
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
      if (cnf->language==LANGUAGE2)
	s += f_month->s_french + " ";
      else
	s += f_month->s_english + " ";
    }
    if (f_year != NULL)     s += itoa(f_year->s) +".";

}


void
CEntryMasterThesis::PrintBIBTEX(string &s)
{

  s += "@MasterThesis{" + key +", \n" ;
  s += CreateBibtex() ;
  s+= "} \n"  ;
}


void
CEntryMasterThesis::PrintEE(string &s)
{
  s += "%O Thesis \n" ;
  s += "%9 MasterThesis \n" ;
  s += CreateEE() ;
}
