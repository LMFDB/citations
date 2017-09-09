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

#ifndef __String_h_
#define __String_h_

using namespace std ;

#include <string>
#include <stdlib.h>
#include <iostream>
#include <stdio.h>

void suppress_first_and_last_space(string &s) ;
string upcase(const string &s) ;
string lowcase(const string &s) ;
string maj(const string &s) ;
void SuppressLastDot(string &s);

int instring(const string &s, const  char *sc);
int instring(const string &s, const string &s1) ;

int count(const string &s,const char c) ;

int before(const string &s1, const string &s2,  string &s) ;
int after(const string &s1, const string &s2,  string &s) ;
int between(const string &s1,
	    const string &start,
	    const string &send,
	    string &s) ;
int beforelast(const string &s1, const string &s2,  string &s) ;

int betweenfirstlast(const string &s1,
		     const string &start,
		     const string &send,
		     string &s) ;

int suppress(const string &s1,
	     char c,
	     string &s) ;

string
suppress_white_and_tab(const  string &s) ;
int
suppress_white_and_tab(const  string &s,  string &s_entry_with_no_space) ;
string itoa(int k) ;
int gsub(string &s, const  string& pat, const  string& r) ;
int gsubonetime(string &s, const string& pat, const   string& r) ;
void suppress_brace(string &S) ;

int isbetween( const string &s, const  string &subs,  const string &s1,  const string &s2) ;

int isbetween( const string &s, const unsigned int pos,  const string &s1,  const string &s2) ;

void filter_string(string& S) ;

string suppressaccent(string& S) ;

string supress_slash(string& S) ;
#endif
