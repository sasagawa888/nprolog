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
         char buff[BUFFSIZE];$).

tk_interp(Str) :-
    cinline($strcpy(buff,Jgetname(Jderef(varStr,th)));
             Tcl_Eval(interp,buff);
             return(Jexec_all(rest,Jget_sp(th),th));$).


tk_init :-
    cinline($interp = Tcl_CreateInterp();
             Tcl_Init(interp);               
             Tk_Init(interp);
             return(Jexec_all(rest,Jget_sp(th),th));$).

tk_exit :-
    cinline($Tcl_DeleteInterp(interp);
             return(Jexec_all(rest,Jget_sp(th),th));$).
            

list_string([],$$).
list_string([X|Xs],S) :-
    list_string(Xs,S1),
    concat(X,S1,S).


tk_command_option(X,Y) :-
    list(X),
    tk_function(X,Y).
tk_command_option(X,[Y]) :-
    format(Y,$ ~A $,X).

tk_label(Obj) :-
    format(Str,$label .~A ~A\n;$,[Obj]),
    tk_interp(Str).
tk_label(Obj,L) :-
    tk_option(L,Opt),
    format(Str,$label .~A ~A\n;$,[Obj,Opt]),
    tk_interp(Str).


tk_button(Obj,L) :-
    tk_option(L,Opt),
    format(Str,$button .~A ~S \n;$,[Obj,Opt]),
    tk_interp(Str).
 
tk_radiobutton(Obj,L) :-
    tk_option(L,Opt),
    format(Str,$radiobutton .~A ~S\;$,[Obj,Opt]),
    tk_interp(Str).
 
tk_checkbutton(Obj,L) :-
    tk_option(L,Opt),
    format(Str,$checkbutton .~A ~S\;$,[Obj,Opt]),
    tk_interp(Str).
 
tk_listbox(Obj,L) :-
    tk_option(L,Opt),
    format(Str,$listbox .~A ~S\;$,[Obj,Opt]),
    tk_interp(Str).
 
tk_scrollbar(Obj,L) :-
    tk_option(L,Opt),
    format(Str,$scrollbar .~A ~S\;$,[Obj,Opt]),
    tk_interp(Str).

tk_menu(Obj,L) :-
    tk_object(Obj,Objects),
    tk_option(L,Opt),
    format(Str,$menu ~A ~S\n;$,[Objects,Opt]),
    tk_interp(Str).

tk_configure(Obj,L) :-
    tk_object(Obj,Objects),
    tk_option(L,Opt),
    format(Str,$ configure ~A ~S\n;$,[Objects,Opt]),
    tk_interp(Str).
 
tk_add(Obj,Class,L) :-
    tk_object(Obj,Objects),
    tk_option(L,Opt),
    format(Str,$ add ~A ~S\n;$,[Object,Class,Opt]),
    tk_interp(Str).

tk_canvas(Obj,L) :-
    tk_list(L,Opt),
    format(Str,$canvas .~A ~S\n;$,[Obj,Opt]),
    tk_interp(Str).

tk_mainloop :-
    cinline($Tk_MainLoop();$).

tk_pack(L) :-
    tk_packs(L,Obj),
    format(Str,$pack ~A \n;$,[Obj]),
    tk_interp(Str).


tk_update :-
    cinline($strcpy(buff,"update\n");
             Tcl_Eval(interp,buff);$).

tk_command(Cmd) :-
    format(Str,$~A\n;$,[Cmd]),
    tk_interp(Str).

tk_rgb([R,G,B],Str) :-
    format(Str,$ #~D ~D ~D$,[R,G,B]).

tk_create(Obj,Class,L) :-
    tk_list(L,Opt),
    format(Str,$.~O create ~O Class ~O\n$,[Obj,Class,Opt]),
    tk_interp(Str).

tk_list([],$$).
tk_list([X|Xs],Str) :-
    string_term(S,X),
    concat($ $,S,S1),
    tk_list(Xs,S2),
    concat(S1,S2,Str).
     
