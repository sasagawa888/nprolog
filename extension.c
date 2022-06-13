#include <string.h>
#ifdef __arm__
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif
#include "npl.h"

//-----------JUMP project(builtin for compiler)------------

int
b_reconsult_predicate (int arglist, int rest)
{
  int n, arg1, lis, save1;

  n = length (arglist);
  if (n == 1)
    {
      save1 = sp;
      arg1 = deref (car (arglist));
      if (!wide_variable_p (arg1))
	error (NOT_VAR, "n_reconsult_predicate ", arg1);

      lis = reverse (reconsult_list);
      while (!nullp (lis))
	{
	  unify (arg1, car (lis));
	  if (prove_all (rest, sp) == YES)
	    return (YES);

	  lis = cdr (lis);
	  unbind (save1);
	}
      unbind (save1);
      return (NO);
    }
  return (NO);
}

int
b_reconsult_abolish (int arglist, int rest)
{
  int n, lis, pred;

  n = length (arglist);
  if (n == 0)
    {
      lis = reconsult_list;
      while (!nullp (lis))
	{
	  pred = makepred (GET_NAME (car (lis)));
	  SET_CAR (pred, NIL);
	  listremove (car (lis), predicates);
	  lis = cdr (lis);
	}
      return (prove_all (rest, sp));
    }
  return (NO);
}

int
b_filename (int arglist, int rest)
{
  int n, arg1, arg2, pos, len;
  char str1[STRSIZE];

  n = length (arglist);
  if (n == 2)
    {
      arg1 = deref (car (arglist));
      arg2 = cadr (arglist);
      strcpy (str1, GET_NAME (arg1));
      len = strlen (GET_NAME (arg1));
      for (pos = 0; pos < len; pos++)
	if (str1[pos] == '.')
	  {
	    str1[pos] = NUL;
	    if (unify (arg2, makeconst (str1)) == YES)
	      return (prove_all (rest, sp));
	    else
	      return (NO);
	  }
      if (unify (arg1, arg2) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

//convert atom for C language function name
int
b_atom_convert (int arglist, int rest)
{
  int n, arg1, arg2, pos1;
  char str1[ATOMSIZE], str2[ATOMSIZE], str3[ATOMSIZE], str4[ATOMSIZE];
  //   str1=input   str2=unicode-buffer str3=usc4-buffer str4 = output-string 
  n = length (arglist);
  if (n == 2)
    {
      arg1 = deref (car (arglist));
      arg2 = deref (cadr (arglist));

      strcpy (str1, GET_NAME (arg1));
      pos1 = 0;
      memset (str4, NUL, ATOMSIZE);

      while (str1[pos1] != NUL)
	{
	  if (str1[pos1] == ':')
	    {
	      str2[0] = '_';
	      str2[1] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '&')
	    {
	      str2[0] = 'a';
	      str2[1] = 'n';
	      str2[2] = 'd';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '?')
	    {
	      str2[0] = 'm';
	      str2[1] = 'a';
	      str2[2] = 'g';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '+')
	    {
	      str2[0] = 'p';
	      str2[1] = 'l';
	      str2[2] = 's';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '-')
	    {
	      str2[0] = 'm';
	      str2[1] = 'n';
	      str2[2] = 's';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '*')
	    {
	      str2[0] = 'a';
	      str2[1] = 's';
	      str2[2] = 't';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '/')
	    {
	      str2[0] = 'd';
	      str2[1] = 'i';
	      str2[2] = 'v';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '>')
	    {
	      str2[0] = 'r';
	      str2[1] = 'i';
	      str2[2] = 'g';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (str1[pos1] == '<')
	    {
	      str2[0] = 'l';
	      str2[1] = 'e';
	      str2[2] = 'f';
	      str2[3] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (isUni1 (str1[pos1]))
	    {
	      str2[0] = str1[pos1];
	      str2[1] = NUL;
	      strcat (str4, str2);
	      pos1++;
	    }
	  else if (isUni2 (str1[pos1]))
	    {
	      str2[0] = str1[pos1++];
	      str2[1] = str1[pos1++];
	      str2[2] = NUL;
	      sprintf (str3, "u%d", utf8_to_ucs4 (str2));
	      strcat (str4, str3);
	    }
	  else if (isUni3 (str1[pos1]))
	    {
	      str2[0] = str1[pos1++];
	      str2[1] = str1[pos1++];
	      str2[2] = str1[pos1++];
	      str2[3] = NUL;
	      sprintf (str3, "u%d", utf8_to_ucs4 (str2));
	      strcat (str4, str3);
	    }
	  else if (isUni4 (str1[pos1]))
	    {
	      str2[0] = str1[pos1++];
	      str2[1] = str1[pos1++];
	      str2[2] = str1[pos1++];
	      str2[3] = str1[pos1++];
	      str2[4] = NUL;
	      sprintf (str3, "u%d", utf8_to_ucs4 (str2));
	      strcat (str4, str3);
	    }
	  else if (isUni5 (str1[pos1]))
	    {
	      str2[0] = str1[pos1++];
	      str2[1] = str1[pos1++];
	      str2[2] = str1[pos1++];
	      str2[3] = str1[pos1++];
	      str2[4] = str1[pos1++];
	      str2[5] = NUL;
	      sprintf (str3, "u%d", utf8_to_ucs4 (str2));
	      strcat (str4, str3);
	    }
	  else if (isUni6 (str1[pos1]))
	    {
	      str2[0] = str1[pos1++];
	      str2[1] = str1[pos1++];
	      str2[2] = str1[pos1++];
	      str2[3] = str1[pos1++];
	      str2[4] = str1[pos1++];
	      str2[5] = str1[pos1++];
	      str2[6] = NUL;
	      sprintf (str3, "u%d", utf8_to_ucs4 (str2));
	      strcat (str4, str3);
	    }
	}
      unify (arg2, makeconst (str4));
      return (prove_all (rest, sp));
    }
  return (NO);
}

int
b_arity_count (int arglist, int rest)
{
  int n, arg1, arg2;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = deref (car (arglist));
      arg2 = cadr (arglist);

      if (unify (arg2, listreverse (GET_ARITY (arg1))) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}


int
b_generate_all_variable (int arglist, int rest)
{
  int n, arg1, arg2;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = deref (car (arglist));
      arg2 = cadr (arglist);
      if (unify (arg2, generate_all_variable (GET_CAR (arg1))) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
b_generate_variable (int arglist, int rest)
{
  int n, arg1, arg2;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = deref (car (arglist));
      arg2 = cadr (arglist);
      if (unify (arg2, generate_variable (arg1)) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
generate_all_variable (int x)
{
  int y, res;

  res = NIL;
  while (!nullp (x))
    {
      y = variable_convert1 (car (x));
      if (clausep (y))
	res = generate_variable1 (caddr (y),
				  generate_variable1 (cadr (y), res));
      else
	res = generate_variable1 (y, res);

      x = cdr (x);
    }
  return (res);
}

int
generate_variable (int x)
{
  if (clausep (x))
    return (generate_variable1 (caddr (x),
				generate_variable1 (cadr (x), NIL)));
  else
    return (generate_variable1 (x, NIL));
}

int
generate_variable1 (int x, int y)
{
  int temp;

  if (nullp (x))
    return (y);
  else if (numberp (x))
    return (y);
  else if (compiler_variable_p (x) && !memq (x, y))
    {
      temp = cons (x, y);
      SET_AUX (temp, LIST);
      return (temp);
    }
  else if (singlep (x))
    return (y);
  else if (car (x) == AND)
    return (generate_variable1 (cadr (x), generate_variable1 (caddr (x), y)));
  else if (car (x) == OR)
    return (generate_variable1 (cadr (x), generate_variable1 (caddr (x), y)));
  else
    return (generate_variable1 (car (x), generate_variable1 (cdr (x), y)));
}

int
b_compiler_anoymous (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = deref (car (arglist));
      if (compiler_anoymous_p (arg1))
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
compiler_anoymous_p (int x)
{
  char str[256];

  if (numberp (x))
    return (0);
  if (!!structurep (x))
    return (0);
  strcpy (str, GET_NAME (x));
  str[4] = NUL;
  if (strcmp (str, "var_") == 0)
    return (1);
  else
    return (0);
}



int
b_compiler_variable (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = deref (car (arglist));
      if (compiler_variable_p (arg1))
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
compiler_variable_p (int x)
{
  char str[256];

  if (numberp (x))
    return (0);
  if (!!structurep (x))
    return (0);
  strcpy (str, GET_NAME (x));
  str[3] = NUL;
  if (strcmp (str, "var") == 0)
    return (1);
  else
    return (0);
}

int
b_variable_convert (int arglist, int rest)
{
  int n, arg1, arg2;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = deref (car (arglist));
      arg2 = cadr (arglist);

      if (unify (arg2, variable_convert1 (arg1)) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
variable_convert1 (int x)
{
  int y;
  variable_convert4 (NIL);	//initialize anoymous N
  y = variable_convert2 (x);
  if (clausep (x))
    {
      SET_AUX (y, CLAUSE);
      SET_OPT (y, GET_OPT (x));
    }
  return (y);
}

int
variable_convert2 (int x)
{
  int y, z;

  if (nullp (x))
    return (NIL);
  else if (anoymousp (x))
    return (variable_convert4 (x));
  else if (variablep (x))
    return (variable_convert3 (x));
  else if (!structurep (x))
    return (x);
  else
    {
      y = GET_AUX (x);
      z = cons (variable_convert2 (car (x)), variable_convert2 (cdr (x)));
      SET_AUX (z, y);
      return (z);
    }

}

//normal variable X -> varX
int
variable_convert3 (int x)
{
  int res;
  char str[STRSIZE];

  strcpy (str, "var");
  strcat (str, GET_NAME (x));
  res = makeconst (str);
  return (res);
}

//anoymous variable _ -> varN (N=1...)
int
variable_convert4 (int x)
{
  int res;
  static int n;
  char str1[STRSIZE], str2[STRSIZE];

  //initialize
  if (x == NIL)
    {
      n = 1;
      return (0);
    }

  strcpy (str1, "var_");
  sprintf (str2, "%d", n);
  strcat (str1, str2);
  res = makeconst (str1);
  n++;
  return (res);
}

int
b_clause_with_arity (int arglist, int rest)
{
  int n, arg1, arg2, arg3, l, clause, clauses, res;

  n = length (arglist);
  if (n == 3)
    {
      arg1 = deref (car (arglist));
      arg2 = deref (cadr (arglist));
      arg3 = deref (caddr (arglist));
      if (!singlep (arg1))
	error (NOT_ATOM, "n_clause_with_arity", arg1);
      if (!integerp (arg2))
	error (NOT_INT, "n_clause_with_arity", arg2);

      clauses = GET_CAR (arg1);
      l = GET_INT (arg2);
      res = NIL;

      while (!nullp (clauses))
	{
	  clause = car (clauses);
	  if (atomp (clause) && l == 0)
	    res = cons (clause, res);
	  else if (predicatep (clause) && length (clause) == l + 1)
	    res = cons (clause, res);
	  else if (user_operation_p (clause) && length (clause) == l + 1)
	    res = cons (clause, res);
	  else if (clausep (clause) && atomp (cadr (clause)) && l == 0)
	    res = cons (clause, res);
	  else if (clausep (clause) && length (cadr (clause)) == l + 1)
	    res = cons (clause, res);

	  clauses = cdr (clauses);
	}
      res = listreverse (res);
      unify (res, arg3);
      return (prove_all (rest, sp));
    }
  return (NO);
}

int
b_property (int arglist, int rest)
{
  int n, arg1, arg2;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);

      if (builtinp (arg1))
	{
	  if (unify (arg2, makeconst ("builtin")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (predicatep (arg1))
	{
	  if (unify (arg2, makeconst ("predicate")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (functionp (arg1))
	{
	  if (unify (arg2, makeconst ("function")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (compiledp (arg1))
	{
	  if (unify (arg2, makeconst ("compiled")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (operationp (arg1))
	{
	  if (unify (arg2, makeconst ("operation")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (operatorp (arg1))
	{
	  if (unify (arg2, makeconst ("operator")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (user_operator_p (arg1))
	{
	  if (unify (arg2, makeconst ("userop")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (user_operation_p (arg1))
	{
	  if (unify (arg2, makeconst ("userop")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (singlep (arg1) && findatom (arg1, USER) == 1)
	{
	  if (unify (arg2, makeconst ("userop")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else if (structurep (arg1) && GET_AUX (arg1) != LIST &&
	       IS_INCELL (car (arg1)) && findatom (car (arg1), USER) == 1)
	{
	  if (unify (arg2, makeconst ("userop")) == YES)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else
	return (NO);

    }
  return (NO);
}

int
b_bignum (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);

      if (bignump (arg1))
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
b_longnum (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);

      if (longnump (arg1))
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
b_findatom (int arglist, int rest)
{
  int n, arg1, arg2, arg3, res;

  n = length (arglist);
  if (n == 3)
    {
      arg1 = deref (car (arglist));	//atom
      arg2 = deref (cadr (arglist));	//property
      arg3 = deref (caddr (arglist));	//address

      res = NIL;
      if (eqlp (arg2, makeconst ("constant")))
	res = findatom (arg1, SIMP);
      else if (eqlp (arg2, makeconst ("predicate")))
	res = findatom (arg1, PRED);
      else if (eqlp (arg2, makeconst ("builtin")))
	res = findatom (arg1, SYS);
      else if (eqlp (arg2, makeconst ("compiled")))
	res = findatom (arg1, COMP);
      else if (eqlp (arg2, makeconst ("operator")))
	res = findatom (arg1, OPE);
      else if (eqlp (arg2, makeconst ("userop")))
	res = findatom (arg1, USER);
      else
	error (ILLEGAL_ARGS, "findatom ", arg2);

      if (unify (arg3, makeint (res)) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
b_defined_predicate (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = deref (car (arglist));

      if (predicatep (arg1))
	{
	  if (atomp (arg1) && GET_CAR (arg1) != NIL)
	    return (prove_all (rest, sp));
	  else if (structurep (arg1) && GET_CAR (car (arg1)) != NIL)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else
	return (NO);
    }
  return (NO);
}

int
b_defined_userop (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = deref (car (arglist));

      if (user_operation_p (arg1) || user_operator_p (arg1))
	{
	  if (atomp (arg1) && GET_CAR (arg1) != NIL)
	    return (prove_all (rest, sp));
	  else if (structurep (arg1) && GET_CAR (car (arg1)) != NIL)
	    return (prove_all (rest, sp));
	  else
	    return (NO);
	}
      else
	return (NO);
    }
  return (NO);
}

int
b_get_execute (int arglist, int rest)
{
  int n, arg1, pos, res;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);

      res = NIL;
      pos = execute_list;
      while (!nullp (pos))
	{
	  res = listcons (car (pos), res);
	  pos = cdr (pos);
	}
      if (unify (arg1, res) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  return (NO);
}

int
b_heapdump (int arglist, int rest)
{
  int n, arg1, arg2;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);

      if (!integerp (arg1))
	error (NOT_INT, "heapd ", arg1);
      if (!integerp (arg2))
	error (NOT_INT, "heapd ", arg2);
      if (greaterp (arg1, arg2))
	error (WRONG_ARGS, "heapd ", wlist2 (arg1, arg2));

      heapdump (get_int (arg1), get_int (arg2));
      return (prove_all (rest, sp));
    }
  return (NO);
}

//----------for Raspberry PI
#ifdef __arm__
int
b_wiringpi_setup_gpio (int arglist, int rest)
{
  int n;

  n = length (arglist);
  if (n == 0)
    {
      wiringPiSetupGpio ();
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "wiringpi_setup_gpio ", arglist);
  return (NO);
}

int
b_wiringpi_spi_setup_ch_speed (int arglist, int rest)
{
  int n, arg1, arg2, x, y;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);

      if (!integerp (arg1))
	error (NOT_INT, "wiringpi_spi_setup_ch_speed ", arg1);
      if (!integerp (arg2))
	error (NOT_INT, "wiringpi_spi_setup_ch_speed ", arg2);


      x = GET_INT (arg1);
      y = GET_INT (arg2);
      wiringPiSPISetup (x, y);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "wiringpi_spi_setup_ch_speed ", arglist);
  return (NO);
}

int
b_pwm_set_mode (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);

      if (arg1 == makeconst ("pwm_mode_ms"))
	pwmSetMode (PWM_MODE_MS);
      else if (arg1 == makeconst ("pwm_mode_bal"))
	pwmSetMode (PWM_MODE_BAL);
      else
	error (WRONG_ARGS, "pwm_set_mode", arg1);

      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "pwm_set_mode ", arglist);
  return (NO);
}

int
b_pwm_set_range (int arglist, int rest)
{
  int n, arg1, x;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "pwm_set_range", arg1);

      x = GET_INT (arg1);
      pwmSetRange (x);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "pwm_set_range ", arglist);
  return (NO);
}

int
b_pwm_set_clock (int arglist, int rest)
{
  int n, arg1, x;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "pwm_set_clock", arg1);

      x = GET_INT (arg1);
      pwmSetClock (x);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "pwm_set_clock ", arglist);
  return (NO);
}

int
b_pin_mode (int arglist, int rest)
{
  int n, arg1, arg2, x;


  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "pin_mode ", arg1);

      x = GET_INT (arg1);
      if (arg2 == makeconst ("intput"))
	pinMode (x, INPUT);
      else if (arg2 == makeconst ("output"))
	pinMode (x, OUTPUT);
      else if (arg2 == makeconst ("pwm_output"))
	pinMode (x, PWM_OUTPUT);
      else
	error (WRONG_ARGS, "pin_mode", arg2);

      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "pin_mode ", arglist);
  return (NO);
}

int
b_digital_write (int arglist, int rest)
{
  int n, arg1, arg2, x, y;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "digital_write ", arg1);
      if (!integerp (arg2))
	error (NOT_INT, "digital_write ", arg2);

      x = GET_INT (arg1);
      y = GET_INT (arg2);
      digitalWrite (x, y);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "digital_write ", arglist);
  return (NO);
}

int
b_digital_write_byte (int arglist, int rest)
{
  int n, arg1, x;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "digital_write_byte ", arg1);

      x = GET_INT (arg1);
      digitalWriteByte (x);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "digital_write_byte ", arglist);
  return (NO);
}

int
b_pull_up_dn_control (int arglist, int rest)
{
  int n, arg1, arg2, x, y;


  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "pull_up_dn_control ", arg1);
      if (!integerp (arg2))
	error (NOT_INT, "pull_up_dn_control ", arg2);

      x = GET_INT (arg1);
      y = GET_INT (arg2);
      pullUpDnControl (x, y);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "pull_up_dn_control ", arglist);
  return (NO);
}

int
b_digital_read (int arglist, int rest)
{
  int n, arg1, arg2, x, res;

  n = length (arglist);
  if (n == 2)
    {
      arg1 = car (arglist);
      arg2 = cadr (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "digital_read", arg1);

      x = GET_INT (arg1);
      res = digitalRead (x);
      if (unify (arg2, makeint (res)) == YES)
	return (prove_all (rest, sp));
      else
	return (NO);
    }
  error (ARITY_ERR, "digital_read ", arglist);
  return (NO);
}

int
b_delay (int arglist, int rest)
{
  int n, arg1, x;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "delay", arg1);

      x = GET_INT (arg1);
      delay (x);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "delay ", arglist);
  return (NO);
}

int
b_delay_microseconds (int arglist, int rest)
{
  int n, arg1, x;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);
      if (!integerp (arg1))
	error (NOT_INT, "delay_microseconds ", arg1);

      x = GET_INT (arg1);
      delayMicroseconds (x);
      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "delay_microseconds ", arglist);
  return (NO);
}

int
b_timer_microseconds (int arglist, int rest)
{
  int n, arg1;

  n = length (arglist);
  if (n == 1)
    {
      arg1 = car (arglist);

      if (arg1 == TIMERON)
	timer = getETime ();
      else if (arg1 == TIMEROFF)
	timer = getETime () - timer;
      else if (variablep (arg1))
	unify (arg1, makeflt (timer));
      else
	error (ILLEGAL_ARGS, "timer_microseconds ", arg1);

      return (prove_all (rest, sp));
    }
  error (ARITY_ERR, "timer_microseconds ", arglist);
  return (NO);
}


#endif
