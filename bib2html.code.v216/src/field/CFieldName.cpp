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
#include <cctype>
#include <stdio.h>
#include <math.h>

#include <include/constant.h>

#include <field/CFieldName.h>
#include <tools/String.h>
#include <tools/divers.h>

#define DEBUG_LEVEL1 0
#define DEBUG_LEVEL2 0

/*!
  Basic Constructor
*/
CFieldName::CFieldName() : CField() 
{
  LName.Kill() ;
}

/*!
  Destructor
*/
CFieldName::~CFieldName()
{
  LName.Kill() ;
}


/*!
  copy operator
*/
CFieldName&
CFieldName::operator=( CFieldName &f)
{
  LName = f.LName ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldName::CFieldName( CFieldName &ib)
{
  *this = ib ; 
}

CFieldName::CFieldName(string &s)
{
  LName.Kill() ;
  unsigned int pos1 ;
  pos1  =  s.find(" and ",0);

  // cout << "CFieldName::CFieldName(string &s) " << endl ;
  string s_name ;
  CName name ;
  
  while (pos1 != string::npos)
  {
    if (!isbetween(s," and ", "{","}"))
    {
      before(s," and ", s_name) ;
      after(s," and ", s) ;
      name.ExtractName(s_name) ;
      
      LName += name ;
      pos1 =  s.find(" and ",0);
    }
    else
    { 
      // cout <<"pos1 = " << pos1 << endl ;
      pos1 =  s.find(" and ",pos1+1);
      //  cout <<"pos1 = " << pos1 << endl ;
    }
  }
  
  name.ExtractName(s) ;
  LName += name ;
}

int CFieldName::Print(ostream& f) 
{
  
  if (!LName.EmptyList())
  {
    LName.Front() ;
    while (!LName.Outside())
    {
      CName name = LName.Value() ;
      f << name.first << " " << name.last ;
    }
  }
  return 0 ;
}

int CFieldName::Print(string& s) 
{
  if (!LName.EmptyList())
  {
    LName.Front() ;
    while (!LName.NextOutside())
    {
      CName name = LName.Value() ;
      s +=  name.first + " " + name.last+ ", " ;
      LName.Next() ;
    }
    CName name = LName.Value() ;
    s +=  name.first + " " + name.last ;
  }
  return 0 ;
}

//-----------------------------------------------------------------

/*!
  Basic Constructor
*/
CName::CName()  
{
  last = "" ;
  first = "" ;
  jr = "" ;
  von = "" ;
}

/*!
  Basic Constructor
*/
CName::CName(string &_last, string &_first, string &_von, string &_jr)  
{
  last = _last ;
  first = _first ;
  jr = _jr ;
  von = _von ;
}

/*!
  Destructor
*/
CName::~CName()
{
}

CName&
CName::operator=( CName &a)
{
  last = a.last ;
  first = a.first ;
  von = a.von ;
  jr = a.jr ;
  
  return *this ;
}

CName&
CName::operator=( CConfigAuthor &a)
{
  last = a.name ;
  first = a.I ;

  return *this ;
}

int
CName::operator==( CName &a)
{
  string a1, a2 ;
  a1 = first[0] ;
  a2 = a.first[0] ;
 
  
  string n1, n2 ;
  n1 = supress_slash(last) ;
  n2 = supress_slash(a.last) ;
  return ((upcase(suppress_white_and_tab(suppressaccent(n1)))== upcase(suppress_white_and_tab(suppressaccent(n2))))  &&
  	  (upcase(suppressaccent(a1)) == upcase(suppressaccent(a2))) &&
	  (upcase(von)==upcase(a.von)) &&
	  (upcase(jr)==upcase(a.jr))
	  ) ;
}

int
CName::operator!=( CName &a)
{
  string a1, a2 ;
  a1 = first[0] ;
  a2 = a.first[0] ;
  return ((upcase(suppress_white_and_tab(suppressaccent(last)))!= upcase(suppress_white_and_tab(suppressaccent(a.last)))) ||
  	  (upcase(suppressaccent(a1)) != upcase(suppressaccent(a2)))||
	  (upcase(von)!=upcase(a.von)) ||
	  (upcase(jr)!=upcase(a.jr))
	   ) ;
}

/*! 
  copy ructor
*/
CName::CName( CName &a)
{
  *this = a ; 
}

int 
CName::ExtractName(string &s)
{
  unsigned int pos ;

  if (DEBUG_LEVEL2)  cout << "chaine initiale :[" << s << "]"<< endl ;
  // in case of comma, first name is after the last
  // comma

  // On supprime tous les 1er et dernier  blancs
  suppress_first_and_last_space(s) ;
  
  pos = s.rfind(",") ; // rfind (on recherche la DERNIERE occurence)

  while (isbetween(s,pos,"{","}"))
    pos = s.rfind(",",pos-1) ; 

  
  
  if (pos != string::npos) 
  {
    if (DEBUG_LEVEL2) cout << "Cas ou les nom sont séparés par une virgule" <<endl  ;
    string tmp1, tmp2 ;
    before(s,",", tmp1) ;
    suppress(tmp1,'{',tmp2) ;
    suppress(tmp2,'}',last) ;
    suppress_first_and_last_space(last) ;
    after(s,",", s) ;
    suppress_first_and_last_space(s) ;
    suppress(s,'{',tmp2) ;
    suppress(tmp2,'}',first);
  }
  else
  {
    if (DEBUG_LEVEL2) cout << "Cas ou les noms en SONT PAS  séparés par une virgule" <<endl  ;
    pos =0  ;

    string tmp1, tmp2 ;
    unsigned     int pos1, pos2 ;
    suppress_first_and_last_space(s) ;
    pos1 = s.find("{") ;
    pos2 = s.find(" ") ;
    
    if (pos2 ==string::npos)
    {
      last = s ;
      first = "" ;
    }
    else
    {
      if ((pos1>pos2) || (pos1 ==string::npos))
      {
	before(s," ", tmp2) ;
	suppress_first_and_last_space(tmp2) ;
	//      suppress_white_and_tab( tmp1, tmp2) ;
	suppress(tmp2,'{',tmp1) ;
	suppress(tmp1,'}',first) ;
	suppress_first_and_last_space(first) ;
	
	after(s," ", s) ;
	suppress_first_and_last_space(s) ;
	//    suppress_white_and_tab(s, tmp1) ;
	suppress(s,'{',tmp2) ;
	suppress(tmp2,'}',last);
	suppress_first_and_last_space(last) ;
      }
      else
      {
	between(s,"{","}",first) ;
	before(s,"}", tmp2) ;
	suppress_first_and_last_space(tmp2) ;
	//      suppress_white_and_tab( tmp1, tmp2) ;
	suppress(tmp2,'{',tmp1) ;
	suppress(tmp1,'}',first) ;
	suppress_first_and_last_space(first) ;
	
	after(s," ", s) ;
	suppress_first_and_last_space(s) ;
	//    suppress_white_and_tab(s, tmp1) ;
	suppress(s,'{',tmp2) ;
	suppress(tmp2,'}',last);
	suppress_first_and_last_space(last) ;
      }
    }
  }
  pos = first.find("Jr.,") ;
  if (pos !=string::npos)
  {
    if (DEBUG_LEVEL2)    cout << "find  Jr.,"<<endl ;
    first.erase(pos,4) ;
    last.append(" Jr.") ;
  }
  pos = first.find("Jr.") ;
  if (pos !=string::npos)
  {
    if (DEBUG_LEVEL2)   cout << "find  Jr."<<endl  ;
    first.erase(pos,3) ;
    last.append(" Jr.") ;
  }
  pos = first.find("Jr,") ;
  if (pos !=string::npos)
  {
    if (DEBUG_LEVEL2)    cout << "find  Jr."<<endl  ;
    first.erase(pos,3) ;
    last.append(" Jr.") ;
  }
  suppress_first_and_last_space(last) ;
  suppress_first_and_last_space(first) ;
  if (DEBUG_LEVEL2)  cout << "prenom : [" <<first<<"]"<<endl ;
  if (DEBUG_LEVEL2)   cout << "nom :    [" <<last<<"]"<<endl <<endl ;
  return 0 ;
}

int CName::Print(ostream& f)
{
  f << first << " " << last ;
  return 0 ;
}


//-----------------------------------------------------------------
/*!
  Basic Constructor
*/
CFieldAuthor::CFieldAuthor() : CFieldName() {}

/*!
  Destructor
*/
CFieldAuthor::~CFieldAuthor(){}


/*!
  copy operator
*/
CFieldAuthor&
CFieldAuthor::operator=(CFieldAuthor  &f)
{
  LName =f.LName ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldAuthor::CFieldAuthor(CFieldAuthor &ib)
{
  *this = ib ; 
}

CFieldAuthor::CFieldAuthor(string &s): CFieldName(s) {}

//-----------------------------------------------------------------
/*!
  Basic Constructor
*/
CFieldEditor::CFieldEditor() : CFieldName() {}

/*!
  Destructor
*/
CFieldEditor::~CFieldEditor(){}


/*!
  copy operator
*/
CFieldEditor&
CFieldEditor::operator=(CFieldEditor  &f)
{
  LName =f.LName ;
  return *this ;
}

/*! 
  copy ructor
*/
CFieldEditor::CFieldEditor(CFieldEditor &ib)
{
  *this = ib ; 
}

CFieldEditor::CFieldEditor(string &s): CFieldName(s) {}

string
CFieldAuthor::PrintBIBTEX()
{
  string st ;
  if (!LName.EmptyList())
  {
    CName n ;
    st += "Author = {" ;
    LName.Front() ;
    while (!LName.NextOutside())
    {
      n = LName.Value() ;
      st += n.last + ", " + n.first +" and " ;
      LName.Next() ;
    }
    n = LName.Value() ;
    st += n.last + ", " + n.first ;
    st +="}" ;
  }
  return st ;
}

string
CFieldAuthor::PrintEE()
{

  string st ;
  if (!LName.EmptyList())
  {
    CName n ;
    LName.Front() ;
    while (!LName.Outside())
    {
      n = LName.Value() ;
      st += "%A "+ n.last + ", " + n.first +"\n" ;
      LName.Next() ;
    }
  }
  return st ;
}

string
CFieldEditor::PrintBIBTEX()
{
  string st ;

  CName n ;
  if (!LName.EmptyList())
  {
    st += "editor = {" ;
    LName.Front() ;
    while (!LName.NextOutside())
    {
      n = LName.Value() ;
      st += n.last + ", " + n.first +" and " ;
      LName.Next() ;
    }
    n = LName.Value() ;
    st += n.last + ", " + n.first ;
    st +="}" ;
  }
  return st ;
}

string
CFieldEditor::PrintEE()
{
  string st ;
  if (!LName.EmptyList())
  {
    CName n ;
    LName.Front() ;
    while (!LName.Outside())
    {
      n = LName.Value() ;
      st += "%E "+ n.last + ", " + n.first +"\n" ;
      LName.Next() ;
    }
  }
  return st ;
}
