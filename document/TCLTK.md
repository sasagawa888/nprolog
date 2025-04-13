# TCL/TK library
under construction

# Preparation
The Tcl/Tk library utilizes the C language embedding feature. Therefore, it needs to be compiled first. Please follow the steps below to compile it.

```
?- use_module(compiler).
yes
?- compile_file('./library/tcltk.pl').
***
yes
```

# Specification

- tk_init/0
Initializing Tcl/Tk.

- tk_exit/0
Terminating Tcl/Tk.

- tk_interp/0
Execute the command given as the string Str in Tcl/Tk.

- tk_update/0
Send the update command to Tcl/Tk.

- tk_mainloop/0
Execute Tk_MainLoop() in Tcl/Tk.

- tk_canvas(Object,Option)
Option width(N),height(N)

- tk_create(Object,Class,Option)
Class line([x1,y1,x2,y2,...]) oval([x1,y1,x2,y2,...]) arc([x1,y1,x2,y2])
rectangle([x1,y1,x2,y2]) polygon([x1,y1,x2,y2,...])

Option fill(Color) e.g. fill(red)

- tk_pack(Object,Option)
Object is atom or list of atom.
