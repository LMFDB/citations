#include <cctype>
#include <stdio.h>

#include <include/constant.h>

#include <entry/CEntry.h>
#include <entry/CVariousEntry.h>
#include <tools/String.h>

#define DEBUG_LEVEL2 1


//--------------------------------------------------------------------
int
CEntryTechReport::CheckValidity()
{
  if (f_title == NULL)
    cout <<"Field title  is missing " <<endl ;
  if (f_institution == NULL)
    cout <<"Field institution is missing " <<endl ;
  if (f_number == NULL)
    cout <<"Field number is missing " <<endl ;
  if (f_month == NULL)
    cout <<"Field month is missing " <<endl ;
  if (f_year == NULL)
    cout <<"Field year is missing " <<endl ;

  return OK ;
}

void
CEntryTechReport::Print(string &s)
{
    string name ;
    if (f_author !=NULL)
    f_author->Print(name) ;

    s += name + ", " ;
    if (f_title != NULL)
    {
      s += f_title->s + ". " ;
    }

    if (f_institution != NULL)  s += "Rapport de recherche " + f_institution->s + ", " ;
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +", " ;


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
CEntryTechReport::PrintLATEX(string &s)
{
    string name ;
    if (f_author !=NULL)
    f_author->Print(name) ;

    s += name + ". " ;
    if (f_title != NULL)
    {
      s += f_title->s + ". " ;
    }

    if (f_institution != NULL)  s += "Rapport de recherche " + f_institution->s + ", " ;
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +", " ;


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
CEntryTechReport::PrintHTML(string &s)
{
  string name ;
  if (f_author !=NULL)
    f_author->Print(name) ;


  s += "<span class=\"BibAuthor\">" ;
  s += name + "</span>. " ;

  if (f_title != NULL)
  {
      s += "<span class=\"BibTechReportTitle\">" ;
    s += f_title->s + "</span>. " ;
  }

  if (f_institution != NULL)
  {
      s += "<span class=\"BibTechReportInstitution\">" ;
    if (f_type == NULL)
    {
      if(cnf->language == FRENCH)
	s += "Rapport de recherche " + f_institution->s + "</span>, " ;
      else
	s += "Research Report " + f_institution->s + "</span>, " ;
    }
    else
      s += f_type->s +" " + f_institution->s + "</span>, " ;
  }
  if (f_number != NULL)   s += "No " + itoa(f_number->s) +", " ;



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
CEntryTechReport::PrintBIBTEX(string &s)
{

  s += "@TechReport{" + key +", \n" ;
  s += CreateBibtex() ;
  s+= "} \n"  ;
}


void
CEntryTechReport::PrintEE(string &s)
{
  s += "%O Report \n" ;
  s += CreateEE() ;
}
