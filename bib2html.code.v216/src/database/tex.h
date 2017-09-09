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
#ifndef __tex_h_
#define __tex_h_


#include <stdio.h>
#include <database/CDataBase.h>
#include <config/CConfig.h>


#include<fstream>
#include<stdlib.h>

void
CreateMainPageCategoryTex(ofstream& f, CDataBase &B, int ra) ;
int CreatePageAllTex(CDataBase& B) ;
int
CreatePageAuthorsTex(CDataBase& B) ;void
CreatePageAuthorTex(ofstream& f,
		 CDataBase& B,
		    CConfigAuthor &author) ;
#endif
