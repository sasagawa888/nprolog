#include <string.h>
#include <ctype.h>
#include "npl.h"

//--------------list data type---------------------
  int
car (int addr)
{
  return (GET_CAR (addr));
}

 int
caar (int addr)
{
  return (car (car (addr)));
}

 int
cdar (int addr)
{
  return (cdr (car (addr)));
}

 int
cdr (int addr)
{
  return (GET_CDR (addr));
}

 int
cddr (int addr)
{
  return (cdr (cdr (addr)));
}

  int
cadr (int addr)
{
  return (car (cdr (addr)));
}

 int
caddr (int addr)
{
  return (car (cdr (cdr (addr))));
}

 int
cadddr (int addr)
{
  return (car (cdr (cdr (cdr (addr)))));
}

 int
caddddr (int addr)
{
  return (car (cdr (cdr (cdr (cdr (addr))))));
}

 int
cadddddr (int addr)
{
  return (car (cdr (cdr (cdr (cdr (cdr (addr)))))));
}

  int
cadar (int addr)
{
  return (car (cdr (car (addr))));
}

 int
cons (int car, int cdr)
{
  int addr;
   addr = freshcell ();
  SET_TAG (addr, STRUCT);
  SET_CAR (addr, car);
  SET_CDR (addr, cdr);
  return (addr);
}

 int
wcons (int car, int cdr)
{
  int addr;
   addr = wp;
  wp++;
  if (wp >= CELLSIZE)
    {
      error (RESOURCE_ERR, "wcons ", NIL);
    }
  SET_TAG (addr, STRUCT);
  SET_CAR (addr, car);
  SET_CDR (addr, cdr);
  SET_AUX (addr, 0);
  return (addr);
}

 int
assq (int sym, int lis)
{
  while (lis != NIL)
    {
      if (sym == caar (lis))
	return (car (lis));
      lis = cdr (lis);
    }
  return (-1);
}

 
// assq1(foo,[foo/1,boo/2]) -> foo/1
  int
assq1 (int sym, int lis)
{
  while (lis != NIL)
    {
      if (sym == cadr (car (lis)))
	return (car (lis));
      lis = cdr (lis);
    }
  return (-1);
}

 
// replace([b,4],[[a,1][b,2][c,3]]) -> [[1,a],[b,4],[c,3]]
  int
replace (int x, int lis)
{
  int temp;
   temp = NIL;
  while (lis != NIL)
    {
      if (car (x) == caar (lis))
	return (append (listreverse (temp), cons (x, cdr (lis))));
      temp = cons (car (lis), temp);
      lis = cdr (lis);
    }
  return (lis);
}

 
//if improper list return -1
  int
length (int addr)
{
  int len = 0;
   while (!(nullp (addr)))
    {
      if (!structurep (addr))
	return (-1);
      len++;
      addr = cdr (addr);
    }
  return (len);
}

 int
atom_length (int addr)
{
  char str[STRSIZE], c;
  int pos, n;
   strcpy (str, GET_NAME (addr));
  if (strlen (GET_NAME (addr)) == 2 && str[0] == '\\')
    return (1);
   pos = 0;
  n = 0;
  c = str[pos];
  while (c != NUL)
    {
      if (c == '\\')
	{
	  n++;
	  pos = pos + 2;
	}
      
      else if (isUni2 (c))
	{
	  n++;
	  pos = pos + 2;
	}
      
      else if (isUni3 (c))
	{
	  n++;
	  pos = pos + 3;
	}
      
      else if (isUni4 (c))
	{
	  n++;
	  pos = pos + 4;
	}
      
      else
	{
	  n++;
	  pos++;
	}
      c = str[pos];
    }
  return (n);
}

 int
string_length (int addr)
{
  char str[STRSIZE], c;
  int pos, n;
   strcpy (str, GET_NAME (addr));
  if (strlen (GET_NAME (addr)) == 2 && str[0] == '\\')
    return (1);
   pos = 0;
  n = 0;
  c = str[pos];
  while (c != NUL)
    {
      if (c == '\\')
	{
	  n++;
	  pos = pos + 2;
	}
      
      else if (isUni2 (c))
	{
	  n++;
	  pos = pos + 2;
	}
      
      else if (isUni3 (c))
	{
	  n++;
	  pos = pos + 3;
	}
      
      else if (isUni4 (c))
	{
	  n++;
	  pos = pos + 4;
	}
      
      else
	{
	  n++;
	  pos++;
	}
      c = str[pos];
    }
  return (n);
}

 int
list (int nest)
{
  if (nullp (nest))
    return (NIL);
  
  else
    return (cons (car (nest), list (cdr (nest))));
}

  
//append!
  int
append1 (int x, int y)
{
  int z;
   if (nullp (x))
    return (y);
  z = x;
  while (!nullp (cdr (x)))
    {
      x = cdr (x);
    }
  SET_CDR (x, y);
  return (z);
}

 int
append (int x, int y)
{
  if (nullp (x))
    return (y);
  
  else
    return (listcons (car (x), append (cdr (x), y)));
}

 int
reverse (int x)
{
  int res;
   res = NIL;
  while (!(nullp (x)))
    {
      res = cons (car (x), res);
      x = cdr (x);
    }
  return (res);
}

  int
listreverse (int x)
{
  int res;
   res = NIL;
  while (!(nullp (x)))
    {
      res = cons (car (x), res);
      SET_AUX (res, LIST);
      x = cdr (x);
    }
  return (res);
}

  int
last (int x)
{
  return (car (listreverse (x)));
}

 int
addtail (int x, int y)
{
  return (listreverse (cons (x, (listreverse (y)))));
}

 int
list1 (int x)
{
  return (cons (x, NIL));
}

 int
list2 (int x, int y)
{
  return (cons (x, cons (y, NIL)));
}

 int
list3 (int x1, int x2, int x3)
{
  return (cons (x1, cons (x2, cons (x3, NIL))));
}

 int
list4 (int x1, int x2, int x3, int x4)
{
  return (cons (x1, cons (x2, cons (x3, cons (x4, NIL)))));
}

 int
list5 (int x1, int x2, int x3, int x4, int x5)
{
  return (cons (x1, cons (x2, cons (x3, cons (x4, cons (x5, NIL))))));
}

 int
list6 (int x1, int x2, int x3, int x4, int x5, int x6)
{
  return (cons
	   (x1, cons (x2, cons (x3, cons (x4, cons (x5, cons (x6, NIL)))))));
}

 int
list7 (int x1, int x2, int x3, int x4, int x5, int x6, int x7)
{
  return (cons
	   (x1,
	    cons (x2,
		  cons (x3,
			cons (x4, cons (x5, cons (x6, cons (x7, NIL))))))));
}

 int
list8 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
{
  return (cons
	   (x1,
	    cons (x2,
		  cons (x3,
			cons (x4,
			      cons (x5,
				    cons (x6,
					  cons (x7, cons (x8, NIL)))))))));
}

 int
list9 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8, int x9)
{
  return (cons
	   (x1,
	    cons (x2,
		  cons (x3,
			cons (x4,
			      cons (x5,
				    cons (x6,
					  cons (x7,
						cons (x8,
						      cons (x9, NIL))))))))));
}

 int
list10 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8,
	int x9, int x10)
{
  return (cons
	   (x1,
	    cons (x2,
		  cons (x3,
			cons (x4,
			      cons (x5,
				    cons (x6,
					  cons (x7,
						cons (x8,
						      cons (x9,
							    cons (x10,
								  NIL)))))))))));
}

 int
wlist1 (int x)
{
  return (wcons (x, NIL));
}

 int
wlist2 (int x, int y)
{
  return (wcons (x, wcons (y, NIL)));
}

 int
wlist3 (int x1, int x2, int x3)
{
  return (wcons (x1, wcons (x2, wcons (x3, NIL))));
}

 int
wlist4 (int x1, int x2, int x3, int x4)
{
  return (wcons (x1, wcons (x2, wcons (x3, wcons (x4, NIL)))));
}

 int
wlist5 (int x1, int x2, int x3, int x4, int x5)
{
  return (cons (x1, cons (x2, cons (x3, cons (x4, cons (x5, NIL))))));
}

 int
wlist6 (int x1, int x2, int x3, int x4, int x5, int x6)
{
  return (wcons
	   (x1,
	    wcons (x2, wcons (x3, wcons (x4, wcons (x5, wcons (x6, NIL)))))));
}

 int
wlist7 (int x1, int x2, int x3, int x4, int x5, int x6, int x7)
{
  return (cons
	   (x1,
	    cons (x2,
		  cons (x3,
			cons (x4, cons (x5, cons (x6, cons (x7, NIL))))))));
}

 int
wlist8 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8)
{
  return (wcons
	   (x1,
	    wcons (x2,
		   wcons (x3,
			  wcons (x4,
				 wcons (x5,
					wcons (x6,
					       wcons (x7,
						      wcons (x8, NIL)))))))));
}

 int
wlist9 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8,
	int x9)
{
  return (wcons
	   (x1,
	    wcons (x2,
		   wcons (x3,
			  wcons (x4,
				 wcons (x5,
					wcons (x6,
					       wcons (x7,
						      wcons (x8,
							     wcons (x9,
								    NIL))))))))));
}

 int
wlist10 (int x1, int x2, int x3, int x4, int x5, int x6, int x7, int x8,
	 int x9, int x10)
{
  return (wcons
	   (x1,
	    wcons (x2,
		   wcons (x3,
			  wcons (x4,
				 wcons (x5,
					wcons (x6,
					       wcons (x7,
						      wcons (x8,
							     wcons (x9,
								    wcons
								    (x10,
								     NIL)))))))))));
}

  int
nth (int addr, int n)
{
  while (!nullp (addr))
    {
      if (n == 1)
	return (car (addr));
      addr = cdr (addr);
      n--;
    }
  return (NIL);
}

  
//check data type
  int
constantp (int addr)
{
  if (integerp (addr))
    return (1);
  
  else if (!structurep (addr) && !variablep (addr))
    return (1);
  
  else
    return (0);
}

 int
atom_constant_p (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (GET_AUX (addr) == SIMP)
    return (1);
  
  else
    return (0);
}

 
// 'foo.pl' '123.23'
  int
atom_quote_p (int addr)
{
  int pos;
  char str[ATOMSIZE];
   if (IS_OUTCELL (addr))
    return (0);
  
  else if (operatorp (addr))
    return (0);
  
  else if (GET_AUX (addr) == SYS)
    return (0);
  
  else if (anoymousp (addr))
    return (0);
  
  else if (variablep (addr))
    return (0);
  
  else if (user_operator_p (addr))
    return (0);
  
  else if (singlep (addr))
    {
      strcpy (str, GET_NAME (addr));
      if (str[0] == NUL)
	return (1);
      if (isupper (str[0]))
	return (1);
      if (isdigit (str[0]))
	return (1);
      if (str[0] == '_' && GET_AUX (addr) == SIMP)
	return (1);
      pos = 0;
      while (str[pos] != NUL)
	{
	  if (!
	       (str[pos] == '_' || isalnum (str[pos]) || isUni2 (str[pos])
		|| isUni3 (str[pos]) || isUni4 (str[pos])
		|| isUni5 (str[pos]) || isUni6 (str[pos]))
	       || str[pos] == ' ')
	    {
	      return (1);
	    }
	   if (isUni2 (str[pos]))
	    pos = pos + 2;
	  
	  else if (isUni3 (str[pos]))
	    pos = pos + 3;
	  
	  else if (isUni4 (str[pos]))
	    pos = pos + 4;
	  
	  else if (isUni5 (str[pos]))
	    pos = pos + 5;
	  
	  else if (isUni6 (str[pos]))
	    pos = pos + 6;
	  
	  else
	    pos++;
	}
      return (0);
    }
  
  else
    return (0);
}

  int
numberp (int addr)
{
  if (IS_ALPHA (addr))
    return (0);
  
  else if (integerp (addr))
    return (1);
  
  else if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_FLOAT (addr) || IS_LONGNUM (addr) || IS_BIGXNUM (addr))
    return (1);
  
  else
    return (0);
}

  int
integerp (int addr)
{
  if (IS_ALPHA (addr))
    return (0);
  
  else if (addr >= INT_FLAG)
    return (1);
  
  else if (addr < 0)
    return (1);
  
  else
    return (0);
}

 int
bignump (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_BIGXNUM (addr))
    return (1);
  
  else
    return (0);
}

 int
longnump (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_LONGNUM (addr))
    return (1);
  
  else
    return (0);
}

 int
wide_integer_p (int addr)
{
  if (integerp (addr) || longnump (addr) || bignump (addr))
    return (1);
  
  else
    return (0);
}

 int
floatp (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_FLOAT (addr))
    return (1);
  
  else
    return (0);
}

 int
stringp (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_STRING (addr))
    return (1);
  
  else
    return (0);
}

  int
atomp (int addr)
{
  if (nullp (addr))
    return (1);
  
  else if (singlep (addr) && !wide_variable_p (addr))
    return (1);
  
  else
    return (0);
}

 int
atomicp (int addr)
{
  if (atomp (addr))
    return (1);
  
  else if (numberp (addr))
    return (1);
  
  else
    return (0);
}

 int
characterp (int addr)
{
  if (atomp (addr) && atom_length (addr) == 1)
    return (1);
  
  else
    return (0);
}

 int
singlep (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_SINGLE (addr))
    return (1);
  
  else
    return (0);
}

 int
streamp (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_STREAM (addr))
    return (1);
  
  else
    return (0);
}

 int
structurep (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (IS_STRUCT (addr) || IS_NIL (addr))
    return (1);
  
  else
    return (0);
}

 
// [1,2,3]
  int
listp (int addr)
{
  if (structurep (addr) && GET_AUX (addr) == LIST)
    return (1);
  
  else
    return (0);
}

 
// (1,2,3).
  int
argumentsp (int addr)
{
  if (structurep (addr) && car (addr) == AND && 
       (!structurep (cadr (addr)) || 
	(operationp (cadr (addr)) && heavy999p (car (cadr (addr))))) && 
       (!structurep (caddr (addr)) || 
	(operationp (caddr (addr)) && heavy999p (car (caddr (addr))))))
    return (1);
  
  else if (structurep (addr) && car (addr) == AND && 
	   (!structurep (cadr (addr)) || 
	    (structurep (cadr (addr)) && heavy999p (car (cadr (addr)))))
	   && argumentsp (caddr (addr)))
    return (1);
  
  else
    return (0);
}

 int
disjunctionp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr)) && eqlp (car (addr), OR))
    return (1);
  
  else
    return (0);
}

 int
conjunctionp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr)) && car (addr) == AND)
    return (1);
  
  else
    return (0);
}

 int
atmarkp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr)) && car (addr) == ATMARK)
    return (1);
  
  else
    return (0);
}

 int
colonp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr)) && car (addr) == COLON)
    return (1);
  
  else
    return (0);
}

  int
infix_operator_p (int addr)
{
  if (IS_OUTCELL (addr))
    return (0);
  
  else if (operatorp (addr) || notated_builtinp (addr)
	   || user_operator_p (addr))
    return (1);
  
  else
    return (0);
}

 int
infixp (int addr)
{
   if (structurep (addr) && infix_operator_p (car (addr)))
    return (1);
  
  else
    return (0);
}

 int
prefixp (int addr)
{
  int opt;
   if (structurep (addr) && infix_operator_p (car (addr)) && 
	 ((opt = GET_OPT (car (addr))) == FX || opt == FY))
    return (1);
  
  else
    return (0);
}

 int
postfixp (int addr)
{
  int opt;
   if (structurep (addr) && infix_operator_p (car (addr)) && 
	 ((opt = GET_OPT (car (addr))) == XF || opt == YF))
    return (1);
  
  else
    return (0);
}

 int
alphabeticalp (int addr)
{
  char *str;
   if (!singlep (addr))
    return (0);
  
  else
    {
      str = GET_NAME (addr);
      if (isalpha (*str))
	return (1);
      
      else
	return (0);
    }
}

 int
operatorp (int addr)
{
   if (singlep (addr) && GET_AUX (addr) == OPE)
    return (1);
  
  else
    return (0);
}

 int
user_operator_p (int addr)
{
   if (singlep (addr) && GET_AUX (addr) == USER)
    return (1);
  
  else
    return (0);
}

 int
user_operation_p (int addr)
{
  if (structurep (addr) && GET_AUX (addr) != LIST && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == USER)
    return (1);
  
  else
    return (0);
}

 int
notated_builtinp (int addr)
{
  int opt;
   if (singlep (addr) && 
	 (GET_AUX (addr) == SYS || GET_AUX (addr) == OPE
	  || GET_AUX (addr) == COMP) && ((opt = GET_OPT (addr)) == XFX
					  || opt == YFX || opt == XFY
					  || opt == FX || opt == FY
					  || opt == XF || opt == YF
					  || opt == FX_XFX || opt == FY_XFX
					  || opt == FX_XFY || opt == FY_XFY
					  || opt == FX_YFX || opt == FY_YFX
					  || opt == FX_XF || opt == FX_YF
					  || opt == FY_XF
					  || opt == FY_YF ))
    return (1);
  
  else
    return (0);
}

 int
variablep (int addr)
{
  if (IS_ALPHA (addr))
    return (1);
  
  else if (singlep (addr) && GET_AUX (addr) == VAR)
    return (1);
  
  else
    return (0);
}

 
// variable + anoymous_variable
  int
wide_variable_p (int addr)
{
  if (variablep (addr))
    return (1);
  
  else if (anoymousp (addr))
    return (1);
  
  else
    return (0);
}

 int
alpha_variable_p (int addr)
{
  if (IS_ALPHA (addr))
    return (1);
  
  else
    return (0);
}

 int
atom_variable_p (int addr)
{
  if (IS_INCELL (addr) && singlep (addr) && GET_AUX (addr) == VAR)
    return (1);
  
  else
    return (0);
}

 int
anoymousp (int addr)
{
  if (IS_INCELL (addr) && singlep (addr) && GET_AUX (addr) == ANOY)
    return (1);
  
  else
    return (0);
}

 int
predicatep (int addr)
{
  if (structurep (addr) && GET_AUX (addr) != LIST && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == PRED)
    return (1);
  
  else if (IS_INCELL (addr) && GET_AUX (addr) == PRED)
    return (1);
  
  else
    return (0);
}

 int
functionp (int addr)
{
  if (structurep (addr) && GET_AUX (addr) != LIST && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == FUNC)
    return (1);
  
  else if (IS_INCELL (addr) && GET_AUX (addr) == FUNC)
    return (1);
  
  else
    return (0);
}

 int
termp (int addr)
{
  if (structurep (addr) && GET_AUX (addr) != LIST && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == PRED)
    return (1);
  
  else
    return (0);
}

 int
atom_predicate_p (int addr)
{
  if (IS_INCELL (addr) && GET_AUX (addr) == PRED)
    return (1);
  
  else
    return (0);
}

 int
clausep (int addr)
{
  if (IS_INCELL (addr) && structurep (addr) && GET_AUX (addr) != LIST
       && IS_INCELL (car (addr)) && car (addr) == DEFINE)
    return (1);
  
  else
    return (0);
}

 int
operationp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == OPE && GET_AUX (addr) != LIST)
    return (1);
  
  else
    return (0);
}

 
// e.g. -1 -p
  int
single_operation_p (int addr)
{
  if (operationp (addr) && length (addr) == 2)
    return (1);
  
  else if (integerp (addr) && GET_INT (addr) < 0)
    return (1);
  
  else
    return (0);
}

 int
builtinp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == SYS && GET_AUX (addr) != LIST)
    return (1);
  
  else if (IS_INCELL (addr) && GET_AUX (addr) == SYS)
    return (1);
  
  else
    return (0);
}

  int
compiledp (int addr)
{
  if (structurep (addr) && IS_INCELL (car (addr))
       && GET_AUX (car (addr)) == COMP && GET_AUX (addr) != LIST)
    return (1);
  
  else if (IS_INCELL (addr) && GET_AUX (addr) == COMP)
    return (1);
  
  else
    return (0);
}

 int
compoundp (int addr)
{
  if (structurep (addr) && !IS_NIL (addr))
    return (1);
  
  else
    return (0);
}

 int
groundp (int addr)
{
   if (nullp (addr))
    return (1);
  
  else if (wide_variable_p (addr))
    return (0);
  
  else if (atomp (addr))
    return (1);
  
  else if (groundp (cadr (addr)) && groundp (caddr (addr)))
    return (1);
  
  else
    return (0);
   return (1);
}

  int
aliasp (int addr)
{
  if (IS_INCELL (addr) && singlep (addr) && IS_INCELL (car (addr))
       && streamp (car (addr)))
    return (1);
  
  else
    return (0);
}

  int
has_variable_p (int addr)
{
  if (nullp (addr))
    return (0);
  
  else if (!structurep (addr))
    if (variablep (addr))
      return (1);
  
    else
      return (0);
  
  else if (has_variable_p (car (addr)) || has_variable_p (cdr (addr)))
    return (1);
  
  else
    return (0);
}

 int
has_value_p (int addr)
{
  if (findvar (addr) == UNBIND)
    return (0);
  
  else
    return (1);
}

 int
has_no_value_p (int x)
{
   while (!nullp (x))
    {
      if (has_value_p (car (x)))
	return (0);
      x = cdr (x);
    }
  return (1);
}

 int
has_cut_p (int addr)
{
  if (addr == CUT)
    return (1);
  
  else if (!conjunctionp (addr))
    return (0);
  
  else if (conjunctionp (addr) && cadr (addr) == CUT)
    return (1);
  
  else
    return (has_cut_p (caddr (addr)));
}

 int
dcgp (int addr)
{
  if (structurep (addr) && car (addr) == DCG)
    return (1);
  
  else
    return (0);
}

  
// for parser. if weight of operator is heavy than 999
  int
heavy999p (int addr)
{
  if (GET_CDR (addr) % 10000 > 999 || GET_CDR (addr) / 10000 > 999)
    return (1);
  
  else
    return (0);
}

  int
callablep (int addr)
{
  if (variablep (addr))
    return (0);
  
  else if (numberp (addr))
    return (0);
  
  else if (atomp (addr))
    return (1);
  
  else if (predicatep (addr))
    return (1);
  
  else if (builtinp (addr))
    return (1);
  
  else if (compiledp (addr))
    return (1);
  
  else if (conjunctionp (addr))
    {
      if (callablep (cadr (addr)) && callablep (caddr (addr)))
	return (1);
      
      else
	return (0);
    }
  
  else if (disjunctionp (addr))
    {
      if (callablep (cadr (addr)) && callablep (caddr (addr)))
	return (1);
      
      else
	return (0);
    }
  
  else if (user_operation_p (addr))
    return (1);
  
  else
    return (0);
}

 int
mixturep (int addr)
{
  if (!singlep (addr))
    return (0);
  
  else if (GET_OPT (addr) == FX_XFX || GET_OPT (addr) == FX_XFY
	   || GET_OPT (addr) == FX_YFX || GET_OPT (addr) == FY_XFX
	   || GET_OPT (addr) == FY_XFY || GET_OPT (addr) == FY_YFX
	   || GET_OPT (addr) == FX_XF || GET_OPT (addr) == FX_YF
	   || GET_OPT (addr) == FY_XF || GET_OPT (addr) == FY_YF)
    return (1);
  
  else
    return (0);
}

 int
get_1st_weight (int addr)
{
  return (GET_CDR (addr) / 10000);
}

 int
get_2nd_weight (int addr)
{
  return (GET_CDR (addr) % 10000);
}

 int
ifthenp (int addr)
{
  if (IS_INCELL (addr) && structurep (addr) && car (addr) == IFTHEN)
    return (1);
  
  else
    return (0);
}

  int
atom_codes_list_p (int addr)
{
   while (!nullp (addr))
    {
      if (!integerp (car (addr)))
	return (0);
       addr = cdr (addr);
    }
  return (1);
}

  int
nullp (int addr)
{
  if (IS_NIL (addr))
    return (1);
  
  else
    return (0);
}

  int
eqp (int addr1, int addr2)
{
  if (addr1 == addr2)
    return (1);
  
  else if (numberp (addr1) && numberp (addr2))
    if (numeqp (addr1, addr2))
      return (1);
  
    else
      return (0);
  
  else
    return (0);
}

 
// e.g. addr1 = makeatom("abc",SIMP); addr2 = makeatom("abc",SYS);
// then eqlp(addr1,addr2) = 1
  int
eqlp (int addr1, int addr2)
{
  if (addr1 == addr2)
    return (1);
  
  else if (atomp (addr1) && atomp (addr2))
    {
      if (strcmp (GET_NAME (addr1), GET_NAME (addr2)) == 0)
	return (1);
      
      else
	return (0);
    }
  
  else if (numberp (addr1) && numberp (addr2))
    {
      if (numeqp (addr1, addr2))
	return (1);
      
      else
	return (0);
    }
  
  else if (stringp (addr1) && stringp (addr2))
    {
      if (strcmp (GET_NAME (addr1), GET_NAME (addr2)) == 0)
	return (1);
      
      else
	return (0);
    }
  
  else
    return (0);
}

  int
equalp (int addr1, int addr2)
{
   if (nullp (addr1) && nullp (addr2))
    return (1);
  
  else if (nullp (addr1) && !nullp (addr2))
    return (0);
  
  else if (!nullp (addr1) && nullp (addr2))
    return (0);
  
  else if (!structurep (addr1) && !structurep (addr2))
    return (eqlp (addr1, addr2));
  
  else if (!structurep (addr1) && structurep (addr2))
    return (0);
  
  else if (structurep (addr1) && !structurep (addr2))
    return (0);
  
  else if (equalp (car (addr1), car (addr2))
	   && equalp (cdr (addr1), cdr (addr2)))
    return (1);
  
  else
    return (0);
 }

 int
streqp (int x, int y)
{
  if (strcmp (GET_NAME (x), GET_NAME (y)) == 0)
    return (1);
  
  else
    return (0);
}

 int
memq (int x, int y)
{
  while (!nullp (y))
    {
      if (eqp (x, car (y)))
	return (1);
       y = cdr (y);
    }
  return (0);
}

 int
memberp (int x, int y)
{
  while (!nullp (y))
    {
      if (equalp (x, car (y)))
	return (1);
       y = cdr (y);
    }
  return (0);
}

  int
listremove (int x, int y)
{
  if (nullp (y))
    return (NIL);
  
  else if (eqlp (x, car (y)))
    return (cdr (y));
  
  else
    return (cons (car (y), listremove (x, cdr (y))));
}

 int
remove_duplicate (int x)
{
  if (nullp (x))
    return (NIL);
  
  else if (memq (car (x), cdr (x)))
    return (remove_duplicate (cdr (x)));
  
  else
    return (listcons (car (x), remove_duplicate (cdr (x))));
}

 
/*
x1 is ignore
*/ 
  int
listremove3 (int x1, int x2, int x3, int ls)
{
   if (nullp (ls))
    return (NIL);
  
  else if (equalp (x2, cadr (car (ls))) && equalp (x3, caddr (car (ls))))
    return (cdr (ls));
  
  else
    return (cons (car (ls), listremove3 (x1, x2, x3, cdr (ls))));
}

 int
spypointp (int x)
{
  int atom, n, y;
   if (atomp (x))
    {
      atom = x;
      n = 0;
    }
  
  else
    {
      atom = car (x);
      n = length (x) - 1;
    }
  y = list3 (SLASH, atom, makeint (n));
  if (memberp (y, spy_list))
    return (1);
  
  else
    return (0);
}

 int
leappointp (int x)
{
  int atom, n, y;
   if (atomp (x))
    {
      atom = x;
      n = 0;
    }
  
  else
    {
      atom = car (x);
      n = length (x) - 1;
    }
  y = list3 (SLASH, atom, makeint (n));
  if (equalp (y, leap_point))
    return (1);
  
  else
    return (0);
}

 int
unique (int x)
{
  int res;
   res = NIL;
  while (!nullp (x))
    {
      if (!memq (car (x), res))
	res = cons (car (x), res);
      x = cdr (x);
    }
  return (res);
}

 int
unicodep (char c)
{
  if (isUni2 (c) || isUni3 (c) || isUni4 (c) || isUni5 (c) || isUni6 (c))
    return (1);
  
  else
    return (0);
}

 
//-------for debug------------------
  void
cellprint (int addr)
{
  switch (GET_FLAG (addr))
    {
    case FRE:
      printf ("FRE ");
      break;
    case USE:
      printf ("USE ");
      break;
    }
  switch (GET_TAG (addr))
    {
    case EMP:
      printf ("EMP    ");
      break;
    case INTN:
      printf ("INTN   ");
      break;
    case FLTN:
      printf ("FLTN   ");
      break;
    case SINGLE:
      printf ("ATOM   ");
      break;
    case STRUCT:
      printf ("STRUCT ");
      break;
    }
  printf ("%07d ", GET_CAR (addr));
  printf ("%07d ", GET_CDR (addr));
  printf ("%07d ", GET_AUX (addr));
  printf ("%s \n", GET_NAME (addr));
}

 
//dump heap
  void
heapdump (int start, int end)
{
  int i;
   printf ("addr    F     TAG  CAR     CDR    BIND   NAME\n");
  for (i = start; i <= end; i++)
    {
      printf ("%07d ", i);
      cellprint (i);
    }
}


//Prolog unification
  int
deref (int x)
{
  int temp;
   if (nullp (x))
    return (NIL);
  
  else if (!structurep (x))
    return (deref1 (x));
  
  else
    {
      temp = wcons (deref (car (x)), deref (cdr (x)));
      SET_AUX (temp, GET_AUX (x));
      return (temp);
    }
}

 int
deref1 (int x)
{
  int res;
  if (variablep (x))
    {
    loop:res = findvar (x);
      if (res == UNBIND)
	return (x);
      
      else if (variablep (res))
	{
	  x = res;
	  goto loop;
	}
      
      else if (structurep (res))
	return (deref (res));
      
      else
	return (res);
    }
  
  else
    return (x);
   return (NIL);
}

 int
unify (int x, int y)
{
  int x1, y1;
  if (nullp (x) && nullp (y))
    return (YES);
  
  else if (variablep (x) && !variablep (y))
    {
      x1 = deref1 (x);
      if (x1 == x)
	{
	  bindsym (x, y);
	  return (YES);
	}
      
      else
	return (unify (x1, y));
    }
  
  else if (!variablep (x) && variablep (y))
    {
      y1 = deref1 (y);
      if (y1 == y)
	{
	  bindsym (y, x);
	  return (YES);
	}
      
      else
	return (unify (x, y1));
    }
  
  else if (variablep (x) && variablep (y))
    {
      x1 = deref1 (x);
      y1 = deref1 (y);
      if (variablep (x1) && variablep (y1))
	{
	  if (x1 == y1 || x == y1 || x1 == y || x == y)
	    {
	      return (YES);
	    }
	  
	  else if (x != y)
	    {			//ordinaly case
	      bindsym (x1, y1);
	      return (YES);
	    }
	  
	  else
	    {
	      bindsym (x1, makevariant ());	// ex ?- X = X
	      return (YES);
	    }
	}
      
      else if (variablep (x1) && !variablep (y1))
	{
	  bindsym (x1, y1);
	  return (YES);
	}
      
      else if (!variablep (x1) && variablep (y1))
	{
	  bindsym (y1, x1);
	  return (YES);
	}
      
      else
	{
	  return (unify (x1, y1));
	}
    }
  
  else if (anoymousp (x) || anoymousp (y))
    {
      return (YES);
    }
  
  else if (constantp (x) && constantp (y))
    {
      if (eqlp (x, y))
	return (YES);
      
      else
	return (NO);
    }
  
  else if (stringp (x) && stringp (y))
    {
      if (streqp (x, y))
	return (YES);
      
      else
	return (NO);
    }
  
  else if (nullp (x) && !nullp (y))
    return (NO);
  
  else if (!nullp (x) && nullp (y))
    return (NO);
  
  else if (structurep (x) && !structurep (y))
    return (NO);
  
  else if (!structurep (x) && structurep (y))
    return (NO);
  
  else if (listp (x) && !listp (y))
    return (NO);
  
  else if (!listp (x) && listp (y))
    return (NO);
  
  else if (unify (car (x), car (y)) == YES
	   && unify (cdr (x), cdr (y)) == YES)
    return (YES);
  
  else
    return (NO);
   return (NO);
}

   
//typed unify. x is a variable;
  int
unify_var (int x, int y)
{
  int x1, y1;
   if (anoymousp (x))
    {
      return (YES);
    }
  
  else if (!variablep (y))
    {
      x1 = deref1 (x);
      if (x1 == x)
	{
	  bindsym (x, y);
	  return (YES);
	}
      
      else
	return (unify (x1, y));
    }
  
  else if (variablep (y))
    {
      x1 = deref1 (x);
      y1 = deref1 (y);
      if (variablep (x1) && variablep (y1))
	{
	  if (x != y)
	    {			//ordinaly case
	      bindsym (x1, y1);
	    }
	  
	  else
	    {
	      bindsym (x1, makevariant ());	// ex ?- X = X
	    }
	  return (YES);
	}
      
      else if (variablep (x1) && !variablep (y1))
	{
	  bindsym (x1, y1);
	  return (YES);
	}
      
      else if (!variablep (x1) && variablep (y1))
	{
	  bindsym (y1, x1);
	  return (YES);
	}
      
      else
	{
	  return (unify (x1, y1));
	}
    }
   return (NO);
}

 
// typed unify. x is constant
  int
unify_const (int x, int y)
{
  int y1;
   if (constantp (x) && constantp (y))
    {
      if (eqlp (x, y))
	return (YES);
      
      else
	return (NO);
    }
  
  else if (variablep (y))
    {
      y1 = deref1 (y);
      if (variablep (y1))
	{
	  bindsym (y1, x);
	  return (YES);
	}
      
      else
	{
	  return (eqlp (x, y1));
	}
    }
  
  else if (anoymousp (y))
    {
      return (YES);
    }
   return (NO);
}

  
// typed unify. x is [] (empty list)
  int
unify_nil (int x, int y)
{
  int y1;
   if (y == NIL)
    return (YES);
  
  else if (variablep (y))
    {
      y1 = deref1 (y);
      if (variablep (y1))
	{
	  bindsym (y1, x);
	  return (YES);
	}
      
      else if (y1 == NIL)
	return (YES);
      
      else
	return (NO);
    }
   return (NO);
}

 
//unbind to local-stack x
  void
unbind (int x)
{
  int i;
   for (i = x; i < sp; i++)
    {
      if (alpha_variable_p (stack[i]))
	{
	  variant[stack[i] - CELLSIZE] = UNBIND;
	}
      
      else if (atom_variable_p (stack[i]))
	{
	  if (alpha_variable_p (GET_CAR (stack[i])))
	    {
	      variant[GET_CAR (stack[i]) - CELLSIZE] = UNBIND;
	    }
	  SET_CAR (stack[i], UNBIND);
	  SET_CDR (stack[i], UNBIND);
	}
      
      else
	error (ILLEGAL_ARGS, "unbind", x);
    }
  sp = x;
}

 
// link variable and variant
  void
assign_variant (int x)
{
  while (!nullp (x))
    {
      SET_CDR (car (x), makevariant ());
      x = cdr (x);
    }
}

 
// release link variable and ariant
  void
release_variant (int x)
{
  while (!nullp (x))
    {
      SET_CDR (car (x), NIL);
      x = cdr (x);
    }
}

  int
sort (int x)
{
  int res;
   res = NIL;
  while (!nullp (x))
    {
      res = insert (res, (car (x)));
      x = cdr (x);
    }
  return (res);
}

 int
insert (int x, int y)
{
  if (nullp (x))
    return (listcons (y, NIL));
  
  else if (sortsmaller (y, car (x)))
    return (listcons (y, x));
  
  else if (sorteqlp (y, car (x)))
    return (x);
  
  else
    return (listcons (car (x), insert (cdr (x), y)));
}

 int
keysort (int x)
{
  int res;
   res = NIL;
  while (!nullp (x))
    {
      res = keyinsert (res, (car (x)));
      x = cdr (x);
    }
  return (res);
}

 int
keyinsert (int x, int y)
{
   if (nullp (x))
    return (list1 (y));
  
  else if (!(length (car (x)) == 3 && eqlp (caar (x), makeope ("-"))))
    error (ILLEGAL_ARGS, "keysort ", car (x));
  
  else if (sortsmaller (cadr (y), cadr (car (x))))
    return (listcons (y, x));
  
  else
    return (listcons (car (x), keyinsert (cdr (x), y)));
   return (NIL);
}

  int
sortsmaller (int x, int y)
{
  if (variablep (x) && !variablep (y))
    return (1);
  
  else if (!variablep (x) && variablep (y))
    return (0);
  
  else if (variablep (x) && variablep (y))
    {
      if (strcmp (GET_NAME (x), GET_NAME (y)) < 0)
	return (1);
      
      else
	return (0);
    }
  
  else
    return (atsmaller (x, y));
}

 int
sorteqlp (int x, int y)
{
  if (variablep (x) && !variablep (y))
    return (0);
  
  else if (!variablep (x) && variablep (y))
    return (0);
  
  else if (variablep (x) && variablep (y))
    {
      if (strcmp (GET_NAME (x), GET_NAME (y)) == 0)
	return (1);
      
      else
	return (0);
    }
  
  else
    return (eqlp (x, y));
}

  void
printenv (void)
{
  int i;
  for (i = 0; i < sp; i++)
    {
      if (alpha_variable_p (stack[i]))
	{
	  print (stack[i]);
	  printf ("=");
	  print (variant[stack[i] - CELLSIZE]);
	}
      
      else if (atom_variable_p (stack[i]))
	{
	  print (stack[i]);
	  printf ("=");
	  print (GET_CAR (stack[i]));
	}
    }
  printf ("sp = %d", sp);
}

  void
add_data (int pred, int data)
{
  int clauses;
   
    //set arity. e.g. GET_CDR(pred) == #[2,3]
    memoize_arity (data, pred);
   clauses = GET_CAR (pred);
  if (nullp (clauses))
    {
      SET_CAR (pred, cons (data, NIL));
    }
  
  else
    {
      while (!nullp (cdr (clauses)))
	{
	  clauses = cdr (clauses);
	}
      SET_CDR (clauses, cons (data, NIL));
    }
  if (!memq (pred, predicates))
    predicates = cons (pred, predicates);
}

 void
insert_data (int pred, int data)
{
   
    //set arity. e.g. GET_CDR(pred) == #[2,3]
    memoize_arity (data, pred);
   SET_CAR (pred, cons (data, GET_CAR (pred)));
  if (!memq (pred, predicates))
    predicates = cons (pred, predicates);
}

 
/*
X -> call(X) e.g foo(X) :- X. -> foo(X) :- call(X).
atom without argument is converted to predicate
*/ 
  int
variable_to_call (int x)
{
  if (nullp (x))
    return (NIL);
  
  else if (variablep (x))
    return (list2 (CALL, x));
  
  else if (atomp (x) && GET_AUX (x) == SIMP && !variablep (x) && x != FEND)
    return (makepred (GET_NAME (x)));
  
  else if (structurep (x) && (car (x) == AND || car (x) == OR))
    return (list3
	     (car (x), variable_to_call (cadr (x)),
	      variable_to_call (caddr (x))));
  
  else if (structurep (x) && car (x) == DEFINE)
    {
      if (nullp (caddr (x)))	// e.g :- foo(x).
	return (list2 (car (x), cadr (x)));
      
      else			// normal case foo(X) :- bar(X).
	return (list3 (car (x), cadr (x), variable_to_call (caddr (x))));
    }
  
  else if (structurep (x) && car (x) == makeatom ("-->", OPE))
    return (list3 (car (x), cadr (x), variable_to_call (caddr (x))));
  
  else
    return (x);
}

  int
concat_atom (int x, int y)
{
  char str[ATOMSIZE];
  int res;
   strcpy (str, GET_NAME (x));
  strcat (str, "_");
  strcat (str, GET_NAME (y));
  res = makeatom (str, PRED);
  return (res);
}

 int
structure_to_list (int x)
{
  int res;
   x = listreverse (x);
  res = NIL;
  while (!nullp (x))
    {
      res = listcons (car (x), res);
      x = cdr (x);
    }
  if (operatorp (car (res)))
    res = listcons (makeconst (GET_NAME (car (res))), cdr (res));
   return (res);
}

 int
list_to_structure (int x)
{
  int res;
   x = listreverse (x);
  res = NIL;
  while (!nullp (x))
    {
      res = cons (car (x), res);
      x = cdr (x);
    }
  return (res);
}

 int
copy_term (int x)
{
  int temp;
   if (nullp (x))
    return (NIL);
  
  else if (variablep (x))
    return (x);
  
  else if (!structurep (x))
    return (x);
  
  else
    {
      temp = copy_term (car (x));
      return (cons (temp, copy_term (cdr (x))));
    }
  return (x);
}

  int
copy_heap (int x)
{
   if (nullp (x))
    return (NIL);
  
  else if (IS_ALPHA (x))
    return (alpha_to_variable (x));
  
  else if (singlep (x))
    return (x);
  
  else if (numberp (x))
    return (x);
  
  else if (stringp (x))
    return (x);
  
  else if (listp (x))
    return (listcons (copy_heap (car (x)), copy_heap (cdr (x))));
  
  else
    return (cons (copy_heap (car (x)), copy_heap (cdr (x))));
   return (x);
}

 
// v_001(vairant) -> _v001(atom-variable)
  int
alpha_to_variable (int x)
{
  int res;
  char str[ATOMSIZE];
   sprintf (str, "_v%d", x - CELLSIZE);
  res = makeatom (str, VAR);
  return (res);
}

  
//transform from UTF-8 to unicode
  int
utf8_to_ucs4 (char *p)
{
  int x, x1, x2, x3, res;
  unsigned char uc;
   uc = (unsigned char) *p;
  if (uc <= 0x7f)
    {
      x = (int) uc;
      return (x);
    }
  
  else if (uc >= 0xc0 && uc <= 0xdf)
    {
      x = (int) (UTF2MSK1 & uc);
      x = x << 6;
      p++;
      uc = (unsigned char) *p;
      x1 = (int) (UTFOMSKO & uc);
      res = x | x1;
      return (res);
    }
  
  else if (uc >= 0xe0 && uc <= 0xef)
    {
      x = (int) (UTF3MSK1 & uc);
      x = x << 12;
      p++;
      uc = (unsigned char) *p;
      x1 = (int) (UTFOMSKO & uc);
      x1 = x1 << 6;
      p++;
      uc = (unsigned char) *p;
      x2 = (int) (UTFOMSKO & uc);
      res = x | x1 | x2;
      return (res);
    }
  
  else if (uc >= 0xf0 && uc <= 0xf7)
    {
      x = (int) (UTF4MSK1 & uc);
      x = x << 18;
      p++;
      uc = (unsigned char) *p;
      x1 = (int) (UTFOMSKO & uc);
      x1 = x1 << 12;
      p++;
      uc = (unsigned char) *p;
      x2 = (int) (UTFOMSKO & uc);
      x2 = x2 << 6;
      p++;
      uc = (unsigned char) *p;
      x3 = (int) (UTFOMSKO & uc);
      res = x | x1 | x2 | x3;
      return (res);
    }
  
  else
    return (-1);
}

   
//transform from Unicode to UTF-8
  void
ucs4_to_utf8 (int n, char *p)
{
  int w, x, y, z;
   if (n <= 0x7f)
    {
      *p = (char) n;
    }
  
  else if (n <= 0x07ff)
    {
      x = UNI2MSK1 & n;
      x = x >> 6;
      x = UNI2ADD1 | x;
      y = UNI2MSK2 & n;
      y = UNIOADDO | y;
      *p = (char) x;
      p++;
      *p = (char) y;
    }
  
  else if (n <= 0xffff)
    {
      x = UNI3MSK1 & n;
      x = x >> 12;
      x = UNI3ADD1 | x;
      y = UNI3MSK2 & n;
      y = y >> 6;
      y = UNIOADDO | y;
      z = UNI3MSK3 & n;
      z = UNIOADDO | z;
      *p = (char) x;
      p++;
      *p = (char) y;
      p++;
      *p = (char) z;
    }
  
  else if (n < 0x1fffff)
    {
      w = UNI4MSK1 & n;
      w = w >> 18;
      w = UNI4ADD1 | w;
      x = UNI4MSK2 & n;
      x = x >> 12;
      x = UNIOADDO | x;
      y = UNI4MSK3 & n;
      y = y >> 6;
      y = UNIOADDO | y;
      z = UNI4MSK4 & n;
      z = UNIOADDO | z;
      *p = (char) w;
      p++;
      *p = (char) x;
      p++;
      *p = (char) y;
      p++;
      *p = (char) z;
    }
  
  else
    {
      error (OUT_OF_RANGE, "Unicode->UTF-8", NIL);
    }
  p++;
  *p = NUL;
}

  int
ctrl_to_number (char c)
{
  if (c == 'n')
    return (makeint (EOL));
  
  else if (c == 't')
    return (makeint (TAB));
  
  else if (c == 'f')
    return ((makeint (FF)));
  
  else if (c == 'r')
    return (makeint (CR));
  
  else if (c == 'v')
    return (makeint (VT));
  
  else if (c == 'a')
    return (makeint (BEL));
  
  else if (c == 'b')
    return (makeint (BS));
  
  else
    return (makeint (c));
   return (NIL);
}

  int
last_predicate (int x)
{
   if (!operationp (x))
    return (x);
  
  else
    return (last_predicate (caddr (x)));
}

  
