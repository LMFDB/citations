#include <tools/String.h>
#include <include/constant.h>

#define DEBUG_LEVEL1 0

string upcase(const string &s)
{
  string s1 ;
  s1 = s  ;
  for (unsigned int i = 0 ; i < s.length(); i++)
    s1[i] = toupper(s[i]) ;
  return s1 ;
}

string lowcase(const string &s)
{
  string s1 ;
  s1 = s  ;
  for (unsigned int i = 0 ; i < s.length(); i++)
    s1[i] = tolower(s[i]) ;
  return s1 ;
}

string maj(const string &s)
{
  string s1 ;
  s1 = lowcase(s)  ;

 int  i=0 ;
 while (s[i]==' ') i++ ;
 s1[i] = toupper(s[i]) ;
 return s1 ;
}

int
instring(const string &s, const char *sc)
{
  return (s.find(sc,0) != string::npos) ;
}

int
instring(const string &s, const string &s1)
{
  return (s.find(s1,0) != string::npos) ;
}

//! compte le nombre d'occurence de c dans s
int count(const string &s,const char c)
{
  int nb = 0 ;
  for (unsigned int i = 0 ; i < s.length(); i++)
    if (s[i] == c ) nb++ ;
  return nb;
}

//! compte le nombre d'occurence de s1 dans s
int count(const string &s,const string &s1)
{
  int nb = 0 ;
  for (unsigned int i = 0 ; i < s.length() - s1.length(); i++)
  {
    unsigned int pos = s.find(s1,i) ;
    if (pos != string::npos ) nb++ ;
  }
  return nb;
}

int before(const string &s1, const string &s2,  string &s)
{
  if (DEBUG_LEVEL1)
    cout<< "begin  before(const string &, const string &,  string &) " <<endl ;


  unsigned int pos = s1.find(s2,0) ;

  if (pos != string::npos )
    s = s1.substr(0,pos) ;

  if (DEBUG_LEVEL1)
    cout << "end  before(const string &, const string &,  string &) " <<endl ;

  return 0 ;
}

int beforelast(const string &s1, const string &s2,  string &s)
{
  if (DEBUG_LEVEL1)
    cout<< "begin  before(const string &, const string &,  string &) " <<endl ;

  unsigned int pos = s1.rfind(s2,s1.length()) ;

  if (pos != string::npos )
    s = s1.substr(0,pos) ;

  if (DEBUG_LEVEL1)
    cout << "end  before(const string &, const string &,  string &) " <<endl ;

  return 0 ;
}

int
after(const string &s1, const string &s2,  string &s)
{
  if (DEBUG_LEVEL1)
    cout<< "begin  after(const string &, const string &,  string &) " <<endl ;

  unsigned int   pos = s1.find(s2,0) ;

  if (pos != string::npos )
    s = s1.substr(pos+s2.length(),s1.length() - pos-s2.length()) ;

  if (DEBUG_LEVEL1)
    cout<< "end  after(const string &, const string &,  string &) " <<endl ;
  return 0 ;
}

int between(const string &s1,
	    const string &start,
	    const string &send,
	    string &s)
{
  //  int count_start = 0;
  //  int count_end=0 ;

  //  unsigned int posstart=0 ;
  //  unsigned int posend =0;


  before(s1,send,s) ;
  after(s,start,s) ;
  return 0 ;
}

int betweenfirstlast(const string &s1,
	    const string &start,
	    const string &send,
	    string &s)
{
  beforelast(s1,send,s) ;
  after(s,start,s) ;
  return 0 ;
}


int suppress(const string &s1,
	     char c,
	     string &s)
{
  s = "" ;
  for(unsigned int i =0 ; i < s1.length() ; i++)
  {
    if (s1[i] != c) s += s1[i] ;
  }
  return 0 ;
}

int
suppress_white_and_tab(const  string &s,  string &s_entry_with_no_space)
{
  string s_tmp, s_tmp1 ;
  s_tmp1 =s ;
  gsub(s_tmp1,"\\ ","###") ;
  suppress(s_tmp1,' ', s_tmp) ;
  suppress(s_tmp,'\n', s_tmp1) ;
  suppress(s_tmp1,'	', s_entry_with_no_space) ; // tab
  gsub(s_entry_with_no_space,"###","\\ ") ;


  return 0 ;
}


string
suppress_white_and_tab(const  string &s)
{
  string s_tmp ;
  suppress_white_and_tab(s,s_tmp) ;

  return s_tmp ;
}

string itoa(int k)
{
 char s[20] ;
 sprintf(s,"%d",k) ;
 string S(s) ;
 return S ;
}


int gsub(string &s, const string& pat, const   string& r)
{
  //  cout << "begin gsub(...) "<<endl ;
  bool find = false ;


  if ( s.length() - pat.length() > 1000000)
  {
    return OK ;
  }

  while(find==false)
  {
    find = false ;
    unsigned int i ;
    if ( s.length() - pat.length() > 1000000 ) {;find = true ; break ; }
    for ( i = 0 ; i < s.length() - pat.length(); i++)
    {
      //      cout << i << endl ;
      unsigned int pos = s.find(pat,i) ;
      if (pos != string::npos )
      {
	s.replace(pos,pat.length(), r) ;
	//find = true ;
	break ;
      }
    }
    if (i == s.length() - pat.length())  find = true ;
  }
  //   cout << "end gsub(...) "<<endl ;
  return OK ;
}

int gsubonetime(string &s, const string& pat, const   string& r)
{
  //  cout << "begin gsub(...) "<<endl ;
  bool find = false ;


  if ( s.length() - pat.length() > 1000000)
  {
    return OK ;
  }

  while(find==false)
  {
    find = false ;
    unsigned int i ;
    if ( s.length() - pat.length() > 1000000 ) {;find = true ; break ; }
    for ( i = 0 ; i < s.length() - pat.length(); i++)
    {
      //      cout << i << endl ;
      unsigned int pos = s.find(pat,i) ;
      if (pos != string::npos )
      {
	s.replace(pos,pat.length(), r) ;
	find = true ;
	break ;
      }
    }
    if (i == s.length() - pat.length())  find = true ;
  }
  //   cout << "end gsub(...) "<<endl ;
  return OK ;
}


void suppress_brace(string &S)
{
  gsub(S,"{"," ") ;
  gsub(S,"}"," ") ;
}

void suppress_first_and_last_space(string &s)
{

  if (s.length()!=0)
  {
    // On supprime tous les 1er blancs
    unsigned int pos ;
    int ok = 1;
    while (ok==1)
    {
      pos = s.find(" ",0) ;
      if (pos==0) { s.erase(pos,1) ; ok = 1 ; }
      else ok = 0 ;
    }

    // On supprime tous les derniers blancs
    ok = 1;
    while (ok==1)
    {
      pos = s.rfind(" ") ;
      if (pos==s.length()-1) { s.erase(pos,1) ; ok = 1 ; }
      else ok = 0 ;
    }
  }
}

void SuppressLastDot(string &s)
{
  suppress_first_and_last_space(s) ;
  unsigned int pos ;
  pos = s.rfind(".") ;
  if (pos==s.length()-1) { s.erase(pos,1) ; }
  pos = s.rfind(",") ;
  if (pos==s.length()-1) { s.erase(pos,1) ; }
}
// test if subs is between ss and se in s
int
isbetween( const string &s, const string &subs, const  string &ss,  const string &se)
{
  // cout << s << endl ;
  unsigned int pos1  =  s.find(subs) ;
  if (pos1 == string::npos) return 0 ;

  unsigned int posssb  =  s.rfind(ss,pos1) ;
  if (posssb == string::npos) return 0 ;

  unsigned int posseb  =  s.rfind(se,pos1) ;

  unsigned int possea  =  s.find(se,pos1) ;
  if (possea == string::npos) return 0 ;

  // cout << "isbetween " <<  pos1 <<"  "<< posssb<<" "<< possea << "  "<<posseb << endl ;

  //  cout << "return " << ( (pos1<possea) && (pos1>posssb) ) <<" " << 			 (posssb > posseb)  <<endl ;;

  if (posseb != string::npos)
    return ( (pos1<possea) && (pos1>posssb) &&   (posssb > posseb) );
  else
    return  ( (pos1<possea) && (pos1>posssb) );
}
int isbetween( const string &s, const unsigned int pos1,  const string &ss,  const string &se)
{

  unsigned int posssb  =  s.rfind(ss,pos1) ;
  if (posssb == string::npos) return 0 ;

  unsigned int posseb  =  s.rfind(se,pos1) ;

  unsigned int possea  =  s.find(se,pos1) ;
  if (possea == string::npos) return 0 ;

  // cout << "isbetween " <<  pos1 <<"  "<< posssb<<" "<< possea << "  "<<posseb << endl ;

  //  cout << "return " << ( (pos1<possea) && (pos1>posssb) ) <<" " << 			 (posssb > posseb)  <<endl ;;

  if (posseb != string::npos)
    return ( (pos1<possea) && (pos1>posssb) &&   (posssb > posseb) );
  else
    return  ( (pos1<possea) && (pos1>posssb) );
}

#undef DEBUG_LEVEL1
