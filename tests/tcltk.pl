% tcl/tk library
clibrary($-ltcl -ltk$).
cdeclare($#ifdef __linux__
          #include <tcl/tcl.h>
          #else
          #include <tcl.h>
          #endif$).

cdeclare($#define BUFFSIZE 1024
         Tcl_Interp *interp;
         char buff[BUFFSIZE];$).
cdeclare($static int proc_eval(ClientData clientData, Tcl_Interp *interp, int argc, Tcl_Obj *const argv[])
          { int func,args;
            int i,len,intarg;
            func = Fmakesym(Tcl_GetStringFromObj(argv[1], &len));
            args = NIL;
            for (i = argc-1; i > 1; i--) {
            intarg =Fmakeint(atoi(Tcl_GetStringFromObj(argv[i], &len)));
            args = Fcons(intarg,args);
            i = Fgetint(Fpeval(Fcons(func,args),0));
            Tcl_SetObjResult(interp, Tcl_NewIntObj(i));
            return TCL_OK;
           }
         }$).

tk_exit :-
    cinline($Tcl_DeleteInterp(interp);$).

tk_init :-
    cinline($interp = Tcl_CreateInterp();
             Tcl_Init(interp);               
             Tk_Init(interp); 
             Tcl_CreateObjCommand(interp, "eisl_eval", proc_eval, NULL, NULL);$).

tk_function(X,S) :-
  tk_function1(X,X1),
  concat(${eisl_eval$,X1,S).
tk_function1([],$}$).
tk_function1([X|Xs],S) :-
  concat($ $,X,X1),
  tk_function1(Xs,S1),
  concat(X1,S1,S).

list_string([],$$).
list_string([X|Xs],S) :-
  list_string(Xs,S1),
  concat(X,S1,S).

tk_bind(Obj,Ovent,Func) :-
  %tk_function(Func,Cmd),
  cinline($strcpy(buff,"bind ."$),
  cinline(Obj),cinline($ $),
  cinline(Event),cinline($ $),
  cinline(Cmd),cinline($\n);$),
  cinline($Tcl_Eval(interp,buff);$).

tk_command_option(X,Y) :-
  list(X),
  tk_function(X,Y).
tk_command_option(X,Y) :-
  list_string([$"$,X,$"$],Y).

/*

(defun tk:label (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''label .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk:button (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''button .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))


(defun tk:radiobutton (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''radiobutton .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk:checkbutton (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''radiobutton .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk:listbox (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''listbox .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk:scrollbar (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''scrollbar .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk:menu (obj :rest l)
  (let ((objects (tk:objects obj))
        (opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''menu '');
       strcat(buff,Fgetname(OBJECTS));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))



(defun tk:configure (obj :rest l)
  (let ((objects (tk:objects obj))
        (opt (tk:option l)))
    (c-lang 
      "strcpy(buff,Fgetname(OBJECTS));
       strcat(buff,'' configure '');
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))


(defun tk:add (obj class :rest l)
  (let ((objects (tk:objects obj))
        (opt (tk:option l)))
    (c-lang 
      "strcpy(buff,Fgetname(OBJECTS));
       strcat(buff,'' add '');
       strcat(buff,Fgetname(CLASS));
       strcat(buff,'' '');
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))

(defun tk:canvas (obj :rest l)
  (let ((opt (tk:option l)))
    (c-lang 
      "strcpy(buff,''canvas .'');
       strcat(buff,str_to_lower(Fgetname(OBJ)));
       strcat(buff,Fgetname(OPT));
       strcat(buff,''\n'');
       Tcl_Eval(interp,buff);")))       

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

(defun tk:pack (:rest l)
  (let ((obj (tk:packs l)))
  (c-lang 
  "strcpy(buff,''pack '');
   strcat(buff,str_to_lower(Fgetname(OBJ)));
   strcat(buff,''\n'');
   Tcl_Eval(
    interp,buff);")))

(defun tk:update ()
  (c-lang 
  "strcpy(buff,''update'');
   strcat(buff,''\n'');
   Tcl_Eval(
    interp,buff);"))

(defun tk:mainloop ()
    (c-lang "Tk_MainLoop();"))


(defun tk:command (cmd)
    (c-lang 
      "strcpy(buff,Fgetname(CMD));
       strcat(buff,''\n'');
       printf(''%s'',buff);
       Tcl_Eval(interp,buff);
       printf(''%s\n'', Tcl_GetStringResult(interp));")
    t)

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
          
*/