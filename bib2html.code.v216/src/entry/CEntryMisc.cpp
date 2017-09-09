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

//--------------------------------------------------------------------
int
CEntryMisc::CheckValidity()
{
  if (f_title == NULL)
    cout <<"Field title  is missing " <<endl ;
  if (f_howpublish == NULL)
    cout <<"Field howpublish is missing " <<endl ;
  if (f_number == NULL)
    cout <<"Field number is missing " <<endl ;
  if (f_month == NULL)
    cout <<"Field month is missing " <<endl ;
  if (f_year == NULL)
    cout <<"Field year is missing " <<endl ;

  return OK ;
}
void
CEntryMisc::Print(string &s)
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
      if (f_author ==NULL) s += name_eds + ", " ;
    }

    if (f_title != NULL)  {
      s += f_title->s + ", " ;
    }
    if (f_booktitle != NULL)  {
      s += f_booktitle->s + ", " ;
    }
    if (f_howpublish != NULL)  {
      s += f_howpublish->s + ", " ;
    }
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +", " ;
    if (f_pages != NULL)    s += "pp. "  + f_pages->s  +", " ;//+ itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
    if (f_address)  s +=  f_address->s + ", " ;

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
CEntryMisc::PrintLATEX(string &s)
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
      if (f_author ==NULL) s += name_eds + ", " ;
    }

    if (f_title != NULL)  {
      s += f_title->s + ", " ;
    }
    if (f_booktitle != NULL)  {
      s += "{\\em "+f_booktitle->s + "}, " ;
    }
    if (f_howpublish != NULL)  {
      s += f_howpublish->s + ", " ;
    }
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +", " ;
    if (f_pages != NULL)    s += "pp. "  + f_pages->s  +", " ;//+ itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
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
CEntryMisc::PrintHTML(string &s)
{

    string name ;
    if (f_author !=NULL)
      f_author->Print(name) ;

    s += "<span class=\"BibAuthor\">" ;
    s += name + "</span>. " ;
    if (f_title != NULL)  {
     s += "<span class=\"BibMiscTitle\">" ;
     s += f_title->s + "</span>. " ;
    }
    if (f_booktitle != NULL)  {
      s += "<span class=\"BibMiscBookTitle\">" ;
      s += f_booktitle->s + "</span>, " ;
    }
    if (f_howpublish != NULL)  {
      s += "<span class=\"BibMiscHowpublished\">" ;
      s += f_howpublish->s + "</span>, " ;
    }
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +", " ;
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
CEntryMisc::PrintBIBTEX(string &s)
{
  s += "@Misc{" + key +", \n" ;
  s += CreateBibtex() ;
  s += "} \n"  ;
}

void
CEntryMisc::PrintEE(string &s)
{
  s += "%O Generic \n" ;
  s += CreateEE() ;
}
