
/*
#----------------------------------------------------------------------------
#  Copyright (C) 1998  IRISA-INRIA Rennes Vista Project
#  All Rights Reserved.
#
#    Contact:
#       Eric Marchand
#       IRISA-INRIA Rennes
#       Campus Universitaire de Beaulieu
#       35042 Rennes Cedex
#       France
#
#    email: marchand@irisa.fr
#    www  : http://www.irisa.fr/vista
#
#----------------------------------------------------------------------------
*/


#ifndef CList_h
#define CList_h



#include <stdio.h>
#include <iostream>

/*!
  \ingroup liblist
  \class CElement
  \brief Each element of a list
*/
template <class Type>
class CElement
{
 public:
  CElement<Type> *prev; //<! pointer to the previous element in the list
  CElement<Type> *next; //<! pointer to the next element in the list
  Type val;             //<! value of the element
} ;

/*!
  \file CList.h
  \brief Definition of the CList class
*/

/*!
  \ingroup liblist
  \class CList

  \brief Provide simple list managment

  \author Eric Marchand   (Eric.Marchand@irisa.fr) Irisa / Inria Rennes

  \verbatim
  Data structure:
    each object CElement contains its own value and
    two pointers to the next element of the list and to the previous one

    A list is mainly a pointer to three of these elements
      - one (cur) points the current element
      - one (first) points to a virtual element located at the
        beginning of the list
      - one (last) points  to a virtual element located at the
        end of the list

      first, last and cur are used internally and are not to be considered
      by "basic" user.

  Notation:
    In this documentation we note such a list as
          [*, a, b, c, *]
           f     ^     l
    where
     - the * are the two virtual elements (first (f) and last (l))
     - the ^ denotes the position of the current element

  \endverbatim
*/

template <class Type>
class CList
{
 private:
  void Init() ;
 public:

  int nb;                    //<! number of items in the List
  /*!
    \brief the first virtual item in the list
    \verbatim
          [*, a, b, c, *]
           f
    \endverbatim
  */
  CElement<Type> *first;
  /*!
    \brief the last virtualitem in the list
    \verbatim
          [*, a, b, c, *]
                       l
    \endverbatim
  */
  CElement<Type> *last;
  /*!
    \brief the current item in the list
    \verbatim
          [*, a, b, c, *]
                 ^
    \endverbatim
  */
  CElement<Type> *cur;       // the current element
 public:
  CList() ;                  // constr.
  CList(CList& Liste);       // cloning
  ~CList();                  // destr.
  void Next(void);           // current element's successor ( cur = cur->next )
  void Previous(void);       // current element's predecessor ( cur = cur->pred )
  void Front(void);          // go to the front of the List (cur = first)
  void End(void);            // go back to the end of the List ( cur = last )
  int Outside(void);         // test whether we are outside the List

  int EmptyList(void);       // tests whether the List is empty

  Type& Value(void);         // returns the current element value

  void Suppress(void);       // deletes the current item
  void Kill();              // empties the List

  void Display() ;          // displays the content of the list
  void Print() {Display() ;}           // displays the content of the list


  void AddRight( Type& el);   // inserts an element on the right
  void AddLeft( Type& el);    // inserts an element on the left
  void Modify( Type& el);     // modifies thevalue field of the curr. el.
  int NbElement(void);       // returns the number of items currently in the list
  void Sort() ;

  void operator=(CList<Type>& Liste);
  void operator+=(CList<Type>& Liste);
  void operator+=( Type& l);

  // Other non fundamental member (may be somehow usefull)
  int NextOutside(void);     // test whether we are outside the List
  int NNextOutside(void); // test whether we are outside the List
  int PreviousOutside(void) ;// test whether we are outside the List


  Type& PreviousValue(void); // returns the previous element value
  Type& PPreviousValue(void);
  Type& NextValue(void);     // returns the next element value
  Type& NNextValue(void);   // returns the next of the next element value
  Type& FirstValue(void) ;
  Type& SecondValue(void) ;
  Type& LastValue(void) ;
  Type& NextToLastValue(void) ;


};


#define DEBUG_LEVEL1 0

/*!
  \brief Initialization, Create an empty list
  \verbatim
  Init() --> [*, *]
  \endverbatim */
template<class Type>
void CList<Type>::Init()
{
  CElement<Type> *x=new  CElement<Type>;
  CElement<Type> *y=new  CElement<Type> ;

  first = x ;
  last = y ;

  x->prev = NULL ;
  x->next = y ;
  y->prev = x ;
  y->next =NULL ;

  cur = x ;
  nb = 0 ;
}

/*!
  \brief Basic constructor, Initialization, Create an empty list
  \verbatim
  Init() --> [*, *]
  \endverbatim
  \sa Init()
 */
template<class Type>
CList<Type>::CList()
{
  Init() ;
}



/*!
  \brief CList destructor
  \sa Kill()
 */
template<class Type>
CList<Type>::~CList()
{
  if (DEBUG_LEVEL1)
    printf("Appel Destructeur de liste \n") ;

  Kill() ;

  if (first != NULL) delete first ;
  if (last != NULL) delete last ;

  if (DEBUG_LEVEL1)
    printf("Appel Destructeur de liste \n") ;

}

/*!
  \brief return the number of element in the list
 */
template<class Type>
int CList<Type>::NbElement(void)
{
  return(nb) ;
}


/*!
  \brief position the current element on the next one
  \verbatim
  [*, a, b, c, d, *] --> Next() -->   [*, a, b, c, d, *]
         ^                                      ^
  \endverbatim
*/
template<class Type>
void CList<Type>::Next(void)
{
  cur = cur->next ;
}


/*!
  \brief position the current element on the previous one
  \verbatim
  [*, a, b, c, d, *] --> Next() -->   [*, a, b, c, d, *]
         ^                                ^
  \endverbatim
*/
template<class Type>
void CList<Type>::Previous(void)
{
  cur = cur->prev ;
}

/*!
  \brief return the value of the current element

  \verbatim
  [*, a, b, c, *]  --> Value() return b
      ^
  \endverbatim
 */
template<class Type>
Type& CList<Type>::Value(void)
{

  return(cur->val) ;
}

/*!
  \brief return the value of the previous element

  \verbatim
  [*, a, b, c, *]  --> PreviousValue() return a
         ^
  \endverbatim
*/
template<class Type>
Type& CList<Type>::PreviousValue(void)
{
  return(cur->prev->val) ;
}

/*!
 \brief return the value of the previous previous  element

  \verbatim
  [*, a, b, c, *]  --> PPreviousValue() return a
            ^
  \endverbatim
 */
template<class Type>
Type& CList<Type>::PPreviousValue(void)
{
  return(cur->prev->prev->val) ;
}

/*!
  \brief return the value of the next element
  \verbatim
  [*, a, b, c, d, *]  --> NextValue() return c
         ^
  \endverbatim
*/
template<class Type>
Type& CList<Type>::NextValue(void)
{
  return(cur->next->val) ;
}


/*!
  \brief return the value of the next next element
  \verbatim
  [*, a, b, c, d, *]  --> NNextValue() return d
         ^
  \endverbatim
*/
template<class Type>
Type& CList<Type>::NNextValue(void)
{
  return(cur->next->next->val) ;
}

/*!
  \brief return the first element of the list
   \verbatim
   [*, a, b, c, d, *]  --> FirstValue() return a
  \endverbatim
 */
template<class Type>
Type& CList<Type>::FirstValue(void)
{
  return(first->next->val) ;
}


/*!
  \brief return the second element of the list
   \verbatim
   [*, a, b, c, d, *]  --> SecondValue() return b
  \endverbatim
 */
template<class Type>
Type& CList<Type>::SecondValue(void)
{
  return(first->next->next->val) ;
}

/*! \brief return the third element of the list
   \verbatim
   [*, a, b, c, d, *]  --> ThirdValue() return c
  \endverbatim
 */
/*template<class Type>
Type& CList<Type>::ThirdValue(void)
{
  return(first->next->next->next->val) ;
}*/

/*!\brief return the last element of the list
   \verbatim
   [*, a, b, c, d, *]  --> LastValue() return d
  \endverbatim
 */
template<class Type>
Type& CList<Type>::LastValue(void)
{
  return(last->prev->val) ;
}

/*!
  \brief return the next to last element of the list
   \verbatim
   [*, a, b, c, d, *]  --> NextToLastValue() return c
  \endverbatim
 */
template<class Type>
Type& CList<Type>::NextToLastValue(void)
{
  return(last->prev->prev->val) ;
}

/*!
  \brief

template<class Type>
Type& CList<Type>::BBeforeLastValue(void)
{
  return(last->prev->prev->prev->val) ;
}
*/

/*!
  \brief Position the current element on the first element of the list

  \verbatim
  [*, a, b, c, d, *]  --> Front() --> [*, a, b, c, d, *]
         ^                                ^
  \endverbatim
 */
template<class Type>
void CList<Type>::Front(void)
{
    cur = first->next ;
}

/*!
  \brief Position the current element on the last element of the list

  \verbatim
  [*, a, b, c, d, *]  --> Front() --> [*, a, b, c, d, *]
         ^                                         ^
  \endverbatim
 */
template<class Type>
void CList<Type>::End(void)
{
    cur = last->prev ;
}

/*!
  \brief Test if the list is empty

  \verbatim
  [*, a, b, c, d, *]  --> EmptyList return false
  [*, *]              --> EmptyList return true
  \endverbatim
 */
template<class Type>
int CList<Type>::EmptyList(void)
{
  return((first->next == last) &&( first == last->prev)) ;
}

/*!
  \brief Test if the current element is outside the list
  (on the virtual element)

  \verbatim
  [*, a, b, c, d, *]  --> Outside return false
         ^
  [*, a, b, c, d, *]  --> Outside return true
   ^      or      ^
  \endverbatim
 */
template<class Type>
int CList<Type>::Outside(void)
{

  return((cur==first)||(cur==last)) ;
}

/*!
  \brief Test if the next element is outside the list
  (ie if the current element is the last one)

  \verbatim
  [*, a, b, c, d, *]  --> NextOutside return true
               ^
  \endverbatim
 */
template<class Type>
int CList<Type>::NextOutside(void)
{
  return((cur->next==first)||(cur->next==last)) ;
}


/*!
  \brief Test if the previous element is outside the list
  (ie if the current element is the firts one)

  \verbatim
  [*, a, b, c, d, *]  --> NextOutside return true
      ^
  \endverbatim
 */
template<class Type>
int CList<Type>::PreviousOutside(void)
{
  return((cur->prev==first)||(cur->prev==last)) ;
}
/*!
  \brief Test if the nextnext element is outside the list
  (ie if the current element is the firts one)

  \verbatim
  [*, a, b, c, d, *]  --> NextOutside return true
            ^
  \endverbatim
 */
template<class Type>
int CList<Type>::NNextOutside(void)
{
  return((cur->next->next==first)||(cur->next->next==last)) ;
}

/*!
  \brief Add a new element in the list, at the right of the current one

  \warning the new element becomes the current one

  \verbatim
  [*, a, b, c, *]  --> AddRight(i) -->   [*, a, b, i, c, *]
         ^                                         ^
  \endverbatim
 */
template<class Type>
void CList<Type>::AddRight( Type& v)
{
  CElement<Type> *x=new  CElement<Type>;

  x->val = v ;
  if (EmptyList())
  {
    cur = first ;
  }
  else
  {
    if (Outside()) cout << "CList: Outside with AddRight " << endl ;
  }
  cur->next->prev = x ;
  x->next = cur->next ;
  x->prev = cur ;
  cur->next = x ;
  cur = x ;
  nb++ ;

}


/*!
  \brief Add a new element in the list, at the left of the current one

  \warning the new element becomes the current one

  \verbatim
  [*, a, b, c, *]  --> AddLeft(i) -->   [*, a, i, b, c, *]
         ^                                     ^
  \endverbatim
 */
template<class Type>
void CList<Type>::AddLeft( Type& v)
{
  CElement<Type> *x=new  CElement<Type>;

  x->val = v ;

  if (EmptyList())
  {
    cur = last ;
  }
  else
  {
    if (Outside()) cout << "CList: Outside with AddLeft " << endl ;
  }
  x->next = cur ;
  x->prev = cur->prev ;
  cur->prev->next = x ;
  cur->prev = x ;
  cur = x ;
  nb++ ;

}

/*!
  \brief Modify the value of the current element

  \verbatim
  [*, a, b, c, *]  --> Modify(i) -->   [*, a, i, c, *]
         ^                                    ^
  \endverbatim
 */
template<class Type>
void CList<Type>::Modify( Type& v)
{
  cur->val = v ;
}

/*!
  \brief Destroy the list

  \verbatim
  [*, a, b, c, *]  --> Kill -->   [*, *]
         ^                            ^
  \endverbatim
 */
template<class Type>
void CList<Type>::Kill()
{
  if (DEBUG_LEVEL1)
    cout << "begin CList<Type>::Kill(void) " << endl ;

  Front() ;
  while (!EmptyList())
  {
    Suppress() ;
  }

  if (DEBUG_LEVEL1)
    cout << "end CList<Type>::Kill(void) " << endl ;
}



/*!
  \brief Suppress the current element

  \warning new current element is on the next one

  \verbatim
  [*, a, b, c, d, *] --> Suppress -->  [*, a, c, d, *]
         ^                                    ^
  \endverbatim
 */
template<class Type>
void CList<Type>::Suppress(void)
{
  if (DEBUG_LEVEL1)
    cout << "begin CList<Type>::Suppress(void) " << endl ;
  CElement<Type> *x ;

  cur->prev->next = cur->next ;
  cur->next->prev = cur->prev ;
  x = cur ;
  cur = cur->next ;

  if (x!=NULL) delete x ;

  nb-- ;

  if (DEBUG_LEVEL1)
    cout << "end CList<Type>::Suppress(void) " << endl ;
}



/*!
  \brief Copy constructor

  \remarks Cannot define this function as usual, ie, :
   <tt>template<class Type>
   CList<Type>::CList(const CList<Type>& liste)</tt>
  since the liste is indeed modified (not the element but the position
  of the current element.
 */

template<class Type>
void CList<Type>::operator=(CList<Type>& l)
{
  Type x ;
  CElement<Type> *ecm ;

  Kill() ;
  ecm = l.cur ;
  l.Front() ;
  Front() ;
  while (!l.Outside())
  {
    x = l.Value() ;
    AddRight(x) ;
    l.Next() ;
  }

  nb = l.nb ;
  cur = first->next ;
  l.cur = ecm ;
}

/*!
  \brief Append two lists

  \verbatim
  [*, a, b, *] += [*, c, d, *] --> [*, a, b, c, d, *]
                                                ^
  \endverbatim
 */
template<class Type>
void CList<Type>::operator+=(CList<Type>& l)
{
  Type x ;

  l.Front() ;
  Front() ;
  while (!l.Outside())
  {
    x = l.Value() ;
    AddRight(x) ;
    l.Next() ;
  }
}

/*!
  \brief  Append an element to a list

  \verbatim
  [*, a, b, *] += c --> [*, a, b, c, *]
                                  ^
  \endverbatim
 */
template<class Type>
void CList<Type>::operator += ( Type& l)
{
  End() ;
  AddRight(l) ;
}


/*!
  \brief Copy constructor

  \remarks Cannot define this function as usual, ie, :
   <tt>template<class Type>
   CList<Type>::CList(n CList<Type>& liste)</tt>
  since the liste is indeed modified (not the element but the position
  of the current element.

  \sa operator=(CList<Type>& liste)
 */
template<class Type>
CList<Type>::CList(CList<Type>& liste)
{
  Init() ;
  *this = liste ;
}

/*!
  \brief Print (cout) all the element of the list
 */
template<class Type>
void CList<Type>::Display()
{
  int k = 1 ;
  Front() ;
  while(!Outside()) {
    Next() ;
    k++ ;
  }
  cout<< endl << endl ;
}

/*!
  \brief Print (cout) all the element of the list
 */
template<class Type>
void CList<Type>::Sort()
{
  for (int i =0 ; i < nb ; i++)
  {
    Front() ;
    while(!NextOutside()) {
      if (Value() > NextValue())
      {
	Type a = Value() ;
	Suppress() ;
	AddRight(a) ;
      }
      else
	Next() ;
    }
  }
}

/*
  \brief Merge 2 sorted lists into a third sorted list

template<class Type>
void
Merge(CList<Type>& a, CList<Type>& b, CList<Type> &c)
{
  a.Front() ; b.Front() ;
  Type va = a.Value() ;
  Type vb = b.Value() ;

  while ((!a.Outside()) || (!b.outside()))
  {
    va = a.Value() ;
    vb = b.Value() ;

    if (va>vb)
    {
      c+= vb ; b.Suppress() ;
    }
    else
    {
      c+= va ; a.Suppress() ;
    }
  }
  if (a.outside())
    c+= a ;
  else
    c+= b ;
}

template<class Type>
void
MergeSort(CList<Type>& c)
{
  CList<CList<Type> > l ;
  c.Front() ;
  N = c.NbElements() ;
  for (i=0 ; i < N ; i++)
  {
    Type v1, v2 ;
    CList<Type> l1 ;
    v1 = c.Value() ; c.Next() ;
    v2 = c.Value() ; c.Next() ;
    if (v1<v2)
    { l1 += v1 ; l1 += v2 ; }
    else
    { l1 += v2 ; l1 += v1 ; }
    l += l1 ;
  }

  while (!l.Outside()) {
    a += va ;
    b += vb ;

    Merge(l3, l1, l2) ;
  }
}*/


#undef DEBUG_LEVEL1

#endif

