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
    cinline($strcat(buff,"\n");
             Tcl_Eval(interp,buff);
             //printf("%s",buff);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_clear :-
    cinline($buff[0] = '\0';
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_addatom(Atom) :-
    cinline($strcat(buff,Jgetname(Jderef(varAtom,th)));
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_addhex(Hex) :-
    cinline($sprintf(subbuff,"%x",Jget_int(Jderef(varHex,th)));
             strcat(buff,subbuff);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_addint(Int) :-
    cinline($sprintf(subbuff," %d",Jget_int(Jderef(varInt,th)));
             strcat(buff,subbuff);
             return(Jexec_all(rest,Jget_sp(th),th));$).


tk_init :-
    cinline($interp = Tcl_CreateInterp();
             Tcl_Init(interp);               
             Tk_Init(interp);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_exit :-
    cinline($Tcl_DeleteInterp(interp);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_error(Msg,Obj) :-
    format(user_output,$error ~A ~O$, [Msg,Obj]).

tk_canvas(Obj,Opt) :-
    tk_clear,
    tk_addatom(' canvas .'),
    tk_addatom(Obj),
    tk_option(Opt),
    tk_interp.

tk_mainloop :-
    cinline($Tk_MainLoop();
            return(Jexec_all(rest,Jget_sp(th),th));$).

tk_pack(Obj,Opt) :-
    tk_clear,
    tk_addatom(' pack .'),
    tk_addatom(Obj),
    tk_option(Opt),
    tk_interp.

tk_pack(Obj) :-
    atom(Obj),
    tk_clear,
    tk_addatom(' pack .'),
    tk_addatom(Obj),
    tk_interp.
tk_pack(Obj) :-
    list(Obj),
    tk_clear,
    tk_addatom(' pack '),
    tk_atomlist(Obj),
    tk_interp.

tk_update :-
    tk_clear,
    tk_addatom(update),
    tk_interp.
            


tk_rgb([R,G,B]) :-
    tk_addatom(' #'),
    tk_addint(R),
    tk_addint(G),
    tk_addint(B).
    

tk_create(Obj,Class,Option) :-
    tk_clear,
    tk_addatom(' .'),
    tk_addatom(Obj),
    tk_addatom(' create '),
    tk_class(Class),
    tk_option(Option),
    tk_interp.

tk_class(line(X)) :-
    tk_addatom(' line'),
    tk_intlist(X).
tk_class(oval(X)) :-
    tk_addatom(' oval'),
    tk_intlist(X).
tk_class(arc(X)) :-
    tk_addatom(' arc'),
    tk_intlist(X).
tk_class(rectangle(X)) :-
    tk_addatom(' rectangle'),
    tk_intlist(X).
tk_class(polygon(X)) :-
    tk_addatom(' polygon'),
    tk_intlist(X).

tk_intlist([]).
tk_intlist([X|Xs]) :-
    integer(X),
    tk_addint(X),
    tk_intlist(Xs).
tk_intlist([X|Xs]) :-
    tk_error('not integer',X).

tk_atomlist([]).
tk_atomlist([X|Xs]) :-
    atom(X),
    tk_addatom(' .'),
    tk_addatom(X),
    tk_atomlist(Xs).
tk_atomlist([X|Xs]) :-
    tk_error('not atom',X).


tk_option([]).
tk_option([rgb(R,G,B)|Xs]) :-
    tk_rgb([R,G,B]),
    tk_option(Xs).
tk_option([width(X)|Xs]) :-
    tk_addatom(' -width'),
    tk_addint(X),
    tk_option(Xs).
tk_option([height(X)|Xs]) :-
    tk_addatom(' -height'),
    tk_addint(X),
    tk_option(Xs).
tk_option([fill(X)|Xs]) :-
    tk_addatom(' -fill '),
    tk_addatom(X),
    tk_option(Xs).

