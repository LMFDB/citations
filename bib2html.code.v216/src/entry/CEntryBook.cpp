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

#define DEBUG_LEVEL1 0
#define DEBUG_LEVEL2 0



//--------------------------------------------------------------------
int
CEntryBook::CheckValidity()
{
  if (f_title == NULL)
    cout <<"Field title  is missing " <<endl ;
  if (f_publisher == NULL)
    cout <<"Field publisher is missing " <<endl ;
  if (f_number == NULL)
    cout <<"Field number is missing " <<endl ;
  if (f_month == NULL)
    cout <<"Field month is missing " <<endl ;
  if (f_year == NULL)
    cout <<"Field year is missing " <<endl ;

  return OK ;
}

void
CEntryBook::Print(string &s)
{

  if (DEBUG_LEVEL1)
    cout << "begin CEntryBook::Print(string &s) "<<endl ;

  string name ;
  if (f_author != NULL)
  {
    f_author->Print(name) ;

    s += name + ", " ;
  }
  if (f_title != NULL)
  {
    s +=  f_title->s + ", " ;
  }
  if (f_editor != NULL)
  {
    f_editor->Print(name) ;

    s += name + " (Eds), " ;
  }
  if (f_series != NULL)  s +=  f_series->s + ", " ;
  if (f_number != NULL)  s +=  "No " + itoa(f_number->s) + ", " ;
  if (f_publisher!= NULL)  s +=  f_publisher->s + ", " ;
  if (f_address!= NULL)  s +=  f_address->s + ", " ;

  if (f_month != NULL)
  {
    if (cnf->language==LANGUAGE2)
      s += f_month->s_french + " ";
    else
      s += f_month->s_english + " ";
  }
  if (f_year != NULL)     s += itoa(f_year->s) +".";

  if (DEBUG_LEVEL1)
    cout << "end CEntryBook::Print(string &s) "<<endl ;
}

void
CEntryBook::PrintLATEX(string &s)
{

  if (DEBUG_LEVEL1)
    cout << "begin CEntryBook::Print(string &s) "<<endl ;

  string name ;
  if (f_author != NULL)
  {
    f_author->Print(name) ;

    s += name + ". " ;
  }
  if (f_title != NULL)
  {
    s += "{\\em " + f_title->s + "}, " ;
  }
  if (f_editor != NULL)
  {
    f_editor->Print(name) ;

    s += name + " (Eds), " ;
  }
  if (f_note != NULL)
    {
      s += "{" ;
      s += f_note->s + "}, " ;
    }
  if (f_series != NULL)  s +=  f_series->s + ", " ;
  if (f_number != NULL)  s +=  "No " + itoa(f_number->s) + ", " ;
  if (f_publisher!= NULL)  s +=  f_publisher->s + ", " ;
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

  if (DEBUG_LEVEL1)
    cout << "end CEntryBook::Print(string &s) "<<endl ;
}


void
CEntryBook::PrintHTML(string &s)
{


    string name ;
    if (f_author != NULL)
    {
      f_author->Print(name) ;

      s += "<span class=\"BibAuthor\">" ;
      s += name + "</span>. " ;
    }
    if (f_title != NULL)
    {
      s += "<span class=\"BibBookTitle\">" ;
      s += f_title->s + "</span>. " ;
    }
    if (f_editor!= NULL)
    {
      f_editor->Print(name) ;
      if (f_editor->LName.NbElement()>1)
	s +=  name + " (eds.), " ;
      else
	s +=  name + " (ed.), " ;
    }
    if (f_note != NULL)
    {
      s += "<span class=\"BibJournalName\">" ;
      s += f_note->s + "</span>, " ;
    }
    if (f_series != NULL)  s +=  f_series->s + ", " ;
    if (f_number != NULL)  s +=  "No " + itoa(f_number->s) + ", " ;
    if (f_publisher!= NULL)
    {
	s += "<span class=\"BibPublisher\">" ;
	s += f_publisher->s + "</span>, " ;
    }
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
CEntryBook::PrintBIBTEX(string &s)
{

  s += "@Book{" + key +", \n" ;
  s += CreateBibtex() ;
  s+= "} \n"  ;
}


void
CEntryBook::PrintEE(string &s)
{
  s += "%O Book \n"  ;
  s += CreateEE() ;
}
