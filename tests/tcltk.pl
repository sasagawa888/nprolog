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
             Tcl_Eval(interp,buff);$).
        

tk_exit :-
    cinline($Tcl_DeleteInterp(interp);$).

tk_init :-
    cinline($interp = Tcl_CreateInterp();
             Tcl_Init(interp);               
             Tk_Init(interp);$).


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
    tk_option(L,Opt),
    format(Str,$canvas .~A ~S\n;$,[Obj,Opt]),
    tk_interp(Str).

tk_mainloop :-
    cinline($Tk_MainLoop();$).

tk_pack(L) :-
    tk_packs(L,Obj),
    format(Str,$pack ~A \n;$,[Obj]),
    tk_sendinterp(Str).


tk_update :-
    cinline($strcpy(buff,"update\n");
             Tcl_Eval(interp,buff);$).

tk_command(Cmd) :-
    format(Str,$~A\n;$,[Cmd]),
    tk_interp(Str).

/*

(defun tk:winfo (class object)
   (let ((obj (tk:objects object)))
     (c-lang     
       "strcpy(buff,''winfo '');
        strcat(buff,Fgetname(CLASS));
        strcat(buff,'' '');
        strcat(buff,Fgetname(OBJ));
        strcat(buff,''\n'');")
     (c-lang    
       "Tcl_Eval(interp,buff);
        res = Fmakeint(atoi(Tcl_GetStringResult(interp)));
        return(res);")))

(defun tk:packs (ls)    
    (cond ((null ls) "")
          (t (string-append (string-append " ." (convert (car ls) <string>))
                            (tk:packs (cdr ls))))))

(defun tk:str-to-lower (x)
    (c-lang
      "res = Fmakestr(str_to_lower(Fgetname(X)));"))
                            

(defun tk:rgb (v)
    (string-append " #" (convert (elt v 0) <string>)
                        (convert (elt v 1) <string>)
                        (convert (elt v 2) <string>)))

(defun tk:list (ls)
    (cond ((null ls) "")
          ((atom (car ls)) (string-append (convert (car ls) <string>)
                                          (tk:list (cdr ls))))
          ((listp (car ls)) (string-append (tk:list (car ls))
                                           (tk:list (cdr ls))))))

;; e.g. menu '(m m1) -> ".m.m1"  menu 'm "."
(defun tk:objects (ls)
    (cond ((null ls) "")
          ((eq ls 'root) ".")
          ((symbolp ls) (string-append "." (tk:str-to-lower (convert ls <string>))))
          (t (string-append "." 
                            (tk:str-to-lower (convert (car ls) <string>))
                            (tk:objects (cdr ls))))))

(defun tk:option (ls)
    (cond ((null ls) "")
          ((and (consp (car ls)) (eq (car (car ls)) 'add))
           (string-append (tk:option-add (elt (car ls) 1) (cdr (cdr (car ls))))
                          (tk:option (cdr ls))))
          ((eq (car ls) '-text) (cond ((stringp (car (cdr ls)))
                                       (string-append (string-append " -text \"" (car (cdr ls)) "\"")
                                                      (tk:option (cdr (cdr ls)))))
                                      ((listp (car (cdr ls)))
                                       (string-append (string-append " -text {" (tk:list (car (cdr ls))) "}")
                                                      (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-width) (string-append (string-append " -width " (convert (car (cdr ls)) <string>))
                                                (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-height) (string-append (string-append " -height " (convert (car (cdr ls)) <string>))
                                                (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-relief) (string-append (string-append " -relief " (convert (car (cdr ls)) <string>))
                                                (tk:option (cdr (cdr ls)))))                       
          ((eq (car ls) '-command) (string-append (string-append " -command " (tk:command-option (car (cdr ls))) )
                                                 (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-label) (string-append (string-append " -label \"" (car (cdr ls)) "\"")
                                                 (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-type) (string-append (string-append " -type " (car (cdr ls)))
                                                 (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-menu) (string-append (string-append " -menu " (tk:objects (car (cdr ls))))
                                                 (tk:option (cdr (cdr ls)))))                                      
          ((eq (car ls) '-underline) (string-append (string-append " -underline " (convert (car (cdr ls)) <string>) )
                                                 (tk:option (cdr (cdr ls)))))                                                                              
          ((eq (car ls) '-xscrollcommand) (string-append (string-append " -xscrollcommand \"" (car (cdr ls)) "\"")
                                                 (tk:option (cdr (cdr ls)))))   	
          ((eq (car ls) '-yscrollcommand) (string-append (string-append " -yscrollcommand \"" (car (cdr ls)) "\"")
                                                 (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-selectmode)  (string-append (string-append " -selectmode " (car (cdr ls)))
                                                     (tk:option (cdr (cdr ls))))) 
          ((eq (car ls) '-orient)  (string-append (string-append " -orient " (car (cdr ls)))
                                                     (tk:option (cdr (cdr ls))))) 
          ((or (eq (car ls) '-fg) (eq (car ls) '-foreground)) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -fg " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -fg " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((or (eq (car ls) '-bg) (eq (car ls) '-background)) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -bg " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -bg " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-activeforeground) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -activeforeground " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -activeforeground " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-activebackground) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -activebackground " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -activebackground " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-disabledforeground) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -disabledforeground " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -disabledforeground " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))                                         
          ((eq (car ls) '-troughcolor) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -troughcolor " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -troughcolor " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-fill) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -fill " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -fill " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-outline) 
                                   (cond ((atom (car (cdr ls))) 
                                    (string-append (string-append " -outline " (convert (car (cdr ls)) <string>))
                                                   (tk:option (cdr (cdr ls)))))
                                   ((vectorp (car (cdr ls)))
                                    (string-append (string-append " -outline " (tk:rgb (car (cdr ls))))
                                                   (tk:option (cdr (cdr ls)))))))
          ((eq (car ls) '-stipple) (string-append (string-append " -stipple " (convert (car (cdr ls)) <string>))
                                                (tk:option (cdr (cdr ls)))))                                          
          ((eq (car ls) '-anchor) (string-append (string-append " -anchor "
                                                                 (tk:str-to-lower (convert (car (cdr ls)) <string>)))
                                                (tk:option (cdr (cdr ls)))))
          ((eq (car ls) '-tearoff) (string-append (string-append " -tearoff " 
                                                                 (tk:str-to-lower (convert (car (cdr ls)) <string>)))
                                                  (tk:option (cdr (cdr ls)))))                                    
          ((eq (car ls) '-font) (string-append (string-append " -font " (tk:list (car (cdr ls))))
                                                (tk:option (cdr (cdr ls)))))))
          

(defun line (:rest l)
    (string-append " line" (tk:class-option l)))

(defun oval (:rest l)
    (string-append " oval" (tk:class-option l)))

(defun rectangle (:rest l)
    (string-append " rectangle" (tk:class-option l)))

(defun arc (:rest l)
    (string-append " arc" (tk:class-option l)))

(defun polygon (:rest l)
    (string-append " polygon" (tk:class-option l)))

(defun text (:rest l)
    (string-append " text" (tk:class-option l)))



(defun tk:class-option (ls)
    (cond ((null ls) "")
          (t (string-append (string-append " " (convert (car ls) <string>))
                            (tk:class-option (cdr ls))))))
          

(defun tk:create (obj class :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''.'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,'' create '');
       strcat(buff,str_to_lower(Fgetname(CLASS)));")
    (c-lang   
      "strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);
       res = Fmakeint(atoi(Tcl_GetStringResult(interp)));")))       

*/