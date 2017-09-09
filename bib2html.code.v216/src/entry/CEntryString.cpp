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
CEntryString::CheckValidity()
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
CEntryString::Print(string &s)
{

    string name ;
    if (f_author !=NULL)  f_author->Print(name) ;
    
    s += name + ", " ;
    if (f_title != NULL)  {
      s += f_title->s + ", " ;
    }
    if (f_booktitle != NULL)  {
      s += f_booktitle->s + ", " ;
    } 
    if (f_howpublish != NULL)  {
      s += f_howpublish->s + ", " ;
    } 
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
    if (f_pages != NULL)    s += "pp. " + itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
    if (f_address)  s +=  f_address->s + ", " ;

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
CEntryString::PrintHTML(string &s)
{

    string name ;
    if (f_author !=NULL)  f_author->Print(name) ;
    
    s += cnf->name_start ;
    s += name + ", " ;
    s += cnf->name_end ;
    if (f_title != NULL)  {
      s += cnf->title_journal_start ;
      s += f_title->s + ", " ;
      s += cnf->title_journal_end ;
    }
    if (f_booktitle != NULL)  {
      s += cnf->journal_start ;
      s += f_booktitle->s + ", " ;
      s += cnf->journal_end ;
    } 
    if (f_howpublish != NULL)  {
      s += cnf->journal_start ;
      s += f_howpublish->s + ", " ;
      s += cnf->journal_end ;
    } 
    if (f_number != NULL)   s += "No " + itoa(f_number->s) +"," ;
    if (f_pages != NULL)    s += "pp. " + itoa(f_pages->pf) + "-" + itoa(f_pages->pe) +", " ;
    if (f_address)  s +=  f_address->s + ", " ;


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
CEntryString::PrintBIBTEX(string &s)
{
}

void
CEntryString::PrintEE(string &s)
{
}
