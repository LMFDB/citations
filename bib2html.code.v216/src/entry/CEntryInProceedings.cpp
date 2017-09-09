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

#include <include/constant.h>

#include <entry/CEntry.h>
#include <entry/CVariousEntry.h>
#include <tools/String.h>

#define DEBUG_LEVEL2 1




//-------------------------------------------------------------



int
CEntryInProceedings::CheckValidity()
{
  if (f_title == NULL)
    cout <<"Field title  is missing " <<endl ;
  if (f_booktitle == NULL)
    cout <<"Field booktitle is missing " <<endl ;
  if (f_volume == NULL)
    cout <<"Field volume is missing " <<endl ;
  if (f_pages == NULL)
    cout <<"Field pages is missing " <<endl ;
  if (f_address == NULL)
    cout <<"Field address is missing " <<endl ;
  if (f_month == NULL)
    cout <<"Field month is missing " <<endl ;
  if (f_year == NULL)
    cout <<"Field year is missing " <<endl ;

  return OK ;
}

void
CEntryInProceedings::Print(string &s)
{

    string name ;
    if (f_author!=NULL)
    {
      f_author->Print(name) ;
      s += name + ". " ;
    }

    string name_eds ;
    if (f_editor!=NULL)
    {
      f_editor->Print(name_eds) ;
            if (f_author ==NULL) s += name_eds + ". " ;
    }


    if (f_title != NULL)
    {
      s += f_title->s + ". " ;
    }
    if (f_booktitle != NULL)
    {
      s += "in " + f_booktitle->s + ", " ;
    }
    if ((f_editor!= NULL) && (f_author !=NULL)) s +=  name_eds + " (Eds), " ;
    if (f_volume != NULL)   s += "Vol " + f_volume->s + ", " ;
    if (f_pages != NULL)    s += "pp. " + f_pages->s  +", " ;// + itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
    if (f_address != NULL)  s += f_address->s+ ", " ;

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
CEntryInProceedings::PrintLATEX(string &s)
{

    string name ;
    if (f_author!=NULL)
    {
      f_author->Print(name) ;
      s += name + ". " ;
    }

    string name_eds ;
    if (f_editor!=NULL)
    {
      f_editor->Print(name_eds) ;
            if (f_author ==NULL) s += name_eds + ". " ;
    }


    if (f_title != NULL)
    {
      s += f_title->s + ". " ;
    }
    if (f_booktitle != NULL)
    {
      s += "In {\\em " + f_booktitle->s + "}, " ;
    }
  if (f_note != NULL)
    {
      s += "{" ;
      s += f_note->s + "}, " ;
    }
    if ((f_editor!= NULL) && (f_author !=NULL)) s +=  name_eds + " (Eds), " ;
    if (f_series != NULL)   s +=  f_series->s + ", " ;
    if (f_volume != NULL)   s += "Vol " + f_volume->s + ", " ;
    if (f_pages != NULL)    s += "pp. " + f_pages->s  +", " ;// + itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
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
CEntryInProceedings::PrintHTML(string &s)
{

    string name ;

    if (f_author !=NULL)
      f_author->Print(name) ;


    string name_eds ;
    if (f_editor!= NULL)  f_editor->Print(name_eds) ;

    s += "<span class=\"BibAuthor\">" ;
    s += name + "</span>. " ;
    if (f_title != NULL)
    {
     s += "<span class=\"BibInProceedingsTitle\">" ;
      s += f_title->s + "</span>. " ;
    }
    if (f_booktitle != NULL)
    {
      s += "In <span class=\"BibInProceedingsBooktitle\">" + f_booktitle->s + "</span>, " ;
    }
    if (f_editor!= NULL)
    {
      if (f_editor->LName.NbElement()>1)
	s +=  name_eds + " (eds.), " ;
      else
	s +=  name_eds + " (ed.), " ;
    }
    if (f_series != NULL)   s +=  f_series->s + ", " ;
    if (f_note != NULL)
    {
      s += "<span class=\"BibJournalName\">" ;
      s += f_note->s + "</span>, " ;
    }
    if (f_volume != NULL)   s += "Volume " + f_volume->s + ", " ;
    if (f_pages != NULL)    s += "Pages "  + f_pages->s  +", " ;//+ itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
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
CEntryInProceedings::PrintBIBTEX(string &s)
{
  s += "@InProceedings{" + key +", \n" ;

 s += CreateBibtex() ;
  s+= "} \n"  ;
}


void
CEntryInProceedings::PrintEE(string &s)
{
  s += "%0 Conference Proceedings\n" ;
  s += CreateEE() ;
}
