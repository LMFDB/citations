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


int
CEntryJournal::CheckValidity()
{
  if (f_title == NULL)
    cout <<"Field title  is missing " <<endl ;
  if (f_journal == NULL)
    cout <<"Field journal is missing " <<endl ;
  if (f_volume == NULL)
    cout <<"Field volume is missing " <<endl ;
  if (f_number == NULL)
    cout <<"Field number is missing " <<endl ;
  if (f_pages == NULL)
    cout <<"Field pages is missing " <<endl ;
  if (f_month == NULL)
    cout <<"Field month is missing " <<endl ;
  if (f_year == NULL)
    cout <<"Field year is missing " <<endl ;

  return OK ;
}


void
CEntryJournal::Print(string &s)
{
    string name ;
    if (f_author!=NULL)
    {
      f_author->Print(name) ;
      s += name + ", " ;
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
    if (f_journal != NULL)
    {
      s += f_journal->s + ", " ;
    }
    if (f_volume != NULL)   s += f_volume->s  ;
    if (f_number != NULL)   s += "(" + itoa(f_number->s) +")" ;
    if (f_pages != NULL)
    {
      if ((f_volume != NULL) || (f_number != NULL) )
	s += ":" + f_pages->s +", " ; //itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
      else
	s += "pages " + f_pages->s  +", " ;//itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
    }
    else
      if ((f_volume != NULL) || (f_number != NULL) )
	s += ", " ;

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
CEntryJournal::PrintLATEX(string &s)
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
    if (f_journal != NULL)
    {
      s += "{\\em " +  f_journal->s + "}, " ;
    }
    if (f_note != NULL)
    {
      s += "{" ;
      s += f_note->s + "}, " ;
    }
    if (f_volume != NULL)   s += f_volume->s  ;
    if (f_number != NULL)   s += "(" + itoa(f_number->s) +")" ;
    if (f_pages != NULL)
    {
      if ((f_volume != NULL) || (f_number != NULL) )
	s += ":" + f_pages->s +", " ; //itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
      else
	s += "pages " + f_pages->s  +", " ;//itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
    }
    else
      if ((f_volume != NULL) || (f_number != NULL) )
	s += ", " ;

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
CEntryJournal::PrintHTML(string &s)
{

    string name ;

    if (f_author!=NULL)
    {
      f_author->Print(name) ;
    }

    string name_eds ;
    if (f_editor!=NULL)
    {
      f_editor->Print(name) ;
      if (f_author ==NULL) s += name + ". " ;
    }

    s += "<span class=\"BibAuthor\">" ;
    s += name + "</span>. " ;
    if (f_title != NULL)
    {
      s += "<span class=\"BibJournalTitle\">" ;
      s += f_title->s + "</span>. " ;
    }
    if (f_journal != NULL)
    {
      s += "<span class=\"BibJournalName\">" ;
      s += f_journal->s + "</span>, " ;
    }

    if (f_note != NULL)
    {
      s += "<span class=\"BibJournalName\">" ;
      s += f_note->s + "</span>, " ;
    }
    if (f_volume != NULL)   s += f_volume->s  ;
    if (f_number != NULL)   s += "(" + itoa(f_number->s) +")" ;
    if (f_pages != NULL)
    {
      if ((f_volume != NULL) || (f_number != NULL) )
	s += ":"  + f_pages->s  +", " ;
      else
	s += "pages " + f_pages->s  +", " ;
    }
    else
      if ((f_volume != NULL) || (f_number != NULL) )
	s += ", " ;
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
CEntryJournal::PrintBIBTEX(string &s)
{
  s += "@article{" + key +", \n" ;
  s += CreateBibtex() ;
  s += "} \n"  ;
}


void
CEntryJournal::PrintEE(string &s)
{
  s += "%0 Journal Article \n" ;
  s += CreateEE() ;
}
