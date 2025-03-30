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

tk_init/0
Initializing Tcl/Tk.

tk_exit/0
Terminating Tcl/Tk.

tk_interp(Str)
Execute the command given as the string Str in Tcl/Tk.

tk_update/0
Send the update command to Tcl/Tk.

tk_mainloop/0
Execute Tk_MainLoop() in Tcl/Tk.