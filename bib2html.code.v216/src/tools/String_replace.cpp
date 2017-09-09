#include <tools/String.h>

#include <include/constant.h>
string supress_slash(string& S)
{
  string s = S ;
  gsub(s,"~","") ;
  gsub(s,"&nbsp;","") ;
  gsub(s,"\\ ","") ;
  return s ;
}
void filter_string(string& S)
{
  gsub(S,"--","-") ;
  gsub(S,"~"," ") ;
  gsub(S,"  "," ") ;


  // toutes les chaine de caractere ci-apres contiennent un slach
  if (instring(S, "\\"))
  {
    if (instring(S, "\\\""))
    {
      gsub(S,"\\\"a","ä") ;
      gsub(S,"\\\"u","ü") ;
      gsub(S,"\\\"A","Ä") ;
      gsub(S,"\\\"U","Ü") ;
      gsub(S,"\\\"o","ö") ;
    }

    if (instring(S, "\\'"))
    {
      gsub(S,"\\'e","é") ;
      gsub(S,"\\'E","É") ;
      gsub(S,"\\'{e}","é") ;
    }


    gsub(S,"\\aa","a") ;
    gsub(S,"\\oe ","oe") ;
    gsub(S,"\\AA","A") ;
    gsub(S,"\\OE ","OE") ;

    if (instring(S, "\\`"))
    {
      gsub(S,"\\`E","È") ;
      gsub(S,"\\`A","À") ;
      gsub(S,"\\`e","è") ;
      gsub(S,"\\`{e}","è") ;
      gsub(S,"\\`a","à") ;
      gsub(S,"\\`{a}","à") ;
      gsub(S,"\\`u","ù") ;
      gsub(S,"\\`{u}","ù") ;
      gsub(S,"\\`{A}","À") ;
      gsub(S,"\\`U","Ù") ;
      gsub(S,"\\`{U}","Ù") ;
    }

    if (instring(S, "\\^"))
    {
      gsub(S,"\\^a","â") ;
      gsub(S,"\\^e","ê") ;
      gsub(S,"\\^\\i","î") ;
      gsub(S,"\\^{\\i}","î") ;
      gsub(S,"\\^o","ô") ;
      gsub(S,"\\^{o}","ô") ;
      gsub(S,"\\^u","û") ;
      gsub(S,"\\^{u}","û") ;
    }

    gsub(S,"\\^A","Â") ;
    gsub(S,"\\^E","Ê") ;
    gsub(S,"\\^\\I","Î") ;
    gsub(S,"\\^{\\I}","Î") ;

    gsub(S,"\\,c","ç") ;
    gsub(S,"\\,{c}","ç") ;



    gsub(S,"\\,C","Ç") ;
    gsub(S,"\\,{C}","Ç") ;
    gsub(S,"\\^U","Ô") ;
    gsub(S,"\\^{O}","Ô") ;
    gsub(S,"\\^U","Û") ;
    gsub(S,"\\^{U}","Û") ;
    gsub(S,"\\v Z","Z") ;
    gsub(S,"\\v z","z") ;
    gsub(S,"\\v U","U") ;
    gsub(S,"\\v u","u") ;
    gsub(S,"\\' c","c") ;
    gsub(S,"\\' C","C") ;
    gsub(S,"\\v v","v") ;
    gsub(S,"\\v s","s") ;
    gsub(S,"\\v r","r") ;

    gsub(S,"\\.a","a") ;

    if (instring(S, "{\\"))
    {
      gsub(S,"{\\.a}","a") ;
      gsub(S,"{\\'e}","é") ;
      gsub(S,"{\\\"a}","ä") ;
      gsub(S,"{\\aa}","a") ;
      gsub(S,"{\\\"u}","ü") ;
      gsub(S,"{\\oe}","oe") ;

      gsub(S,"{\\\"A}","Ä") ;
      gsub(S,"{\\AA}","A") ;
      gsub(S,"{\\\"U}","Ü") ;
      gsub(S,"{\\OE}","OE") ;

      gsub(S,"{\\'E}","É") ;
      gsub(S,"{\\`E}","È") ;
      gsub(S,"{\\`A}","À") ;
      gsub(S,"{\\`e}","è") ;
      gsub(S,"{\\`a}","à") ;
      gsub(S,"{\\^a}","â") ;
      gsub(S,"{\\^e}","ê") ;
      gsub(S,"{\\^\\i}","î") ;
      gsub(S,"{\\,c}","ç") ;
      gsub(S,"{\\`u}","ù") ;
      gsub(S,"{\\^o}","ô") ;
      gsub(S,"{\\\"o}","ö") ;
      gsub(S,"{\\^u}","û") ;
      gsub(S,"{\\~g}","g") ;
      gsub(S,"{\\~n}","ñ") ;
      gsub(S,"\\~n","ñ") ;
      gsub(S,"{\\'o}","ó") ;
      gsub(S,"\\'o","ó") ;

      gsub(S,"{\\^A}","Â") ;
      gsub(S,"{\\^E}","Ê") ;
      gsub(S,"{\\^\\I}","Î") ;
      gsub(S,"{\\,C}","Ç") ;
      gsub(S,"{\\`U}","Ù") ;
      gsub(S,"{\\^U}","Ô") ;
      gsub(S,"{\\^U}","Û") ;
      gsub(S,"{\\v Z}","Z") ;
      gsub(S,"{\\v z}","z") ;
      gsub(S,"{\\v U}","U") ;
      gsub(S,"{\\v u}","u") ;
      gsub(S,"{\\' c}","c") ;
      gsub(S,"{\\' C}","C") ;
    }


    gsub(S,"\\sc ","") ;
    gsub(S,"\\em ","") ;
    gsub(S,"\\bf ","") ;
    gsub(S,"\\mbox","") ;
    gsub(S,"\\&","&") ;
  }
}

string suppressaccent(string& S)
{
  bool find = false ;
  unsigned int i ;
  for (i=0 ; i < S.length() ; i++)
    // Le code des caracteres accentuees est > a 208
    if (S[i] >= 'À')
    {
      find = true ;
      break ;
    }
  if (find==true)
  {
    gsub(S,"é","e") ;
    gsub(S,"è","e") ;
    gsub(S,"ê","e") ;
    gsub(S,"É","E") ;
    gsub(S,"È","E") ;
    gsub(S,"Ê","E") ;
    gsub(S,"â","a") ;
    gsub(S,"Â","a") ;
    gsub(S,"à","a") ;
    gsub(S,"À","A") ;
    gsub(S,"ä","a") ;
    gsub(S,"Ä","A") ;
    gsub(S,"ü","u") ;
    gsub(S,"Ü","U") ;
    gsub(S,"ù","u") ;
    gsub(S,"Ù","U") ;
    gsub(S,"û","u") ;
    gsub(S,"Û","U") ;
    gsub(S,"î","i") ;
    gsub(S,"Î","i") ;
    gsub(S,"ç","c") ;
    gsub(S,"Ç","C") ;
    gsub(S,"ô","o") ;
    gsub(S,"Ô","O") ;
  }
  return S ;
}
