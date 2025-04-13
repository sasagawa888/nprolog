% tcl/tk library
clibrary($-ltcl -ltk$).
cdeclare($#ifdef __linux__
          #include <tcl/tcl.h>
          #else
          #include <tcl.h>
          #endif$).
cdeclare($#include <stdio.h>$).

cdeclare($#define BUFFSIZE 1024
         Tcl_Interp *interp;
         char buff[BUFFSIZE];
         char subbuff[BUFFSIZE];$).

tk_interp :-
    cinline($Tcl_Eval(interp,buff);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_clear :-
    cinline($buff[0] = '\0';$).

tk_addatom(Atom) :-
    cinline($strcat(buff,Jgetname(Jderef(varAtom,th)));$).

tk_addint(Int) :-
    cinline($sprintf(subbuff," %d",Jget_int(Jderef(varInt,th)));
             strcat(buff,subbuff);$).

tk_init :-
    cinline($interp = Tcl_CreateInterp();
             Tcl_Init(interp);               
             Tk_Init(interp);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_exit :-
    cinline($Tcl_DeleteInterp(interp);
             return(Jexec_all(rest,Jget_sp(th),th));$).
 
tk_canvas(Obj,Opt) :-
    tk_clear,
    tk_addatom(' .'),
    tk_addatom(Obj),
    tk_addatom(' canvas'),
    tk_option(Opt),
    tk_interp.

tk_mainloop :-
    cinline($Tk_MainLoop();$).

tk_pack(Obj,Opt) :-
    tk_clear,
    tk_addatom(' pack .'),
    tk_addatom(Obj),
    tk_addatom(' '),
    tk_option(Opt),
    tk_interp.

tk_pack(Obj) :-
    tk_clear,
    tk_addatom(' pack .'),
    tk_addatom(Obj),
    tk_interp.

tk_update :-
    cinline($strcpy(buff,"update\n");
             Tcl_Eval(interp,buff);$).


tk_rgb([R,G,B]) :-
    tk_addatom(' #'),
    tk_addint(R),
    tk_addatom(' '),
    tk_addint(G),
    tk_addatom(' '),
    tk_addint(B).
    

tk_create(Obj,Class,Option) :-
    tk_clear,
    tk_addatom('.'),
    tk_addatom(Obj),
    tk_addatom(' create '),
    tk_class(Class),
    tk_option(Option),
    tk_interp(Str).

tk_class(line(X),Str) :-
    tk_addatom(' -line '),
    tk_intlist(X).

tk_intlist([]).
tk_intlist([X|Xs]) :-
    tk_addint(X),
    tk_intlist(Xs).

tk_option([]).
tk_option([rgb(R,G,B)|Xs]) :-
    tk_rgb([R,G,B]),
    tk_option(Xs).
tk_option([width(X)|Xs]) :-
    tk_addatom(' -width '),
    tk_addint(X),
    tk_option(Xs).
tk_option([height(X)|Xs]) :-
    tk_addatom(' -height '),
    tk_addint(X),
    tk_option(Xs).
tk_option([fill(X)|Xs],Str) :-
    tk_addatom(' -fill '),
    tk_addatom(X),
    tk_option(Xs).

