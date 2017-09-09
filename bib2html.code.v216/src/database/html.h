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

#ifndef __HTML_H_
#define __HTML_H_

#include <stdio.h>
#include <database/CDataBase.h>
#include <config/CConfig.h>


#include<fstream>
#include<stdlib.h>

int CreatePageYears(CDataBase& B) ;
int CreatePageYears_ab(CDataBase& B) ;
void CreatePageYear(ofstream& f, CDataBase& B, int year, int ab=0) ;
int CreatePageKeywords(CDataBase& B) ;
void CreatePageKeyword(ofstream& f, CDataBase& B, CConfigKeyword &keyword) ;
void CreateMainPageCategory(ofstream& f, CDataBase &A, int a) ;

int CreatePageAuthors(CDataBase& B) ;
void CreatePageAuthor(ofstream& f,
		 CDataBase& B,
		 CConfigAuthor &author) ;

void CreatePageCategory(ofstream& f, CDataBase& B, int type) ;
int CreatePageCategories(CDataBase& B) ;
void CreateIndexPage(CConfig &cnf) ;

int check_directory(CConfig &c, const char *dir ) ;
int make_directory( CConfig &c, const char *dir ) ;

int CreatePageAll(CDataBase& B) ;

void
CountEntries(CDataBase &B) ;

void PageBegin(ofstream &f, CConfig *cnf) ;
void PageEnd(ofstream &f, CConfig *cnf);
void PageEndNoCopyright(ofstream &f, CConfig *cnf) ;
#endif
