# TCL/TK library


# Preparation
The Tcl/Tk library utilizes the C language embedding feature. Therefore, it needs to be compiled first. Please follow the steps below to compile it.

```
?- use_module(compiler).
yes
?- compile_file('./library/tcltk.pl').
***
yes
```

# Usage

```
?- use_module(tcltk).

```

# Specification

- `tk_init`  
  Initializes the Tcl and Tk interpreters.

- `tk_exit`  
  Deletes the Tcl interpreter and exits.

- `tk_clear`  
  Clears the command buffer (used for GUI commands).

- `tk_command(Cmd)`  
  Executes the arbitrary Tcl command string `Cmd`.

- `tk_mainloop`  
  Starts the main event loop of Tk.

- `tk_update`  
  Immediately updates the Tk GUI.


- `tk_canvas(Obj)`  
  Creates a canvas widget with the name `Obj`.

- `tk_canvas(Obj, Opt)`  
  Creates a canvas widget with options.

- `tk_label(Obj)`  
  Creates a label widget.

- `tk_label(Obj, Opt)`  
  Creates a label widget with options.

- `tk_button(Obj)`  
  Creates a button widget.

- `tk_button(Obj, Opt)`  
  Creates a button widget with options.

- `tk_radiobutton(Obj)`  
  Creates a radio button widget.

- `tk_radiobutton(Obj, Opt)`  
  Creates a radio button widget with options.

- `tk_checkbutton(Obj)`  
  Creates a check button widget.

- `tk_checkbutton(Obj, Opt)`  
  Creates a check button widget with options.

- `tk_listbox(Obj)`  
  Creates a listbox widget.

- `tk_listbox(Obj, Opt)`  
  Creates a listbox widget with options.

- `tk_scrollbar(Obj)`  
  Creates a scrollbar widget.

- `tk_scrollbar(Obj, Opt)`  
  Creates a scrollbar widget with options.


- `tk_pack(Obj)`  
  Packs a single widget.

- `tk_pack(Obj, Opt)`  
  Packs a widget with options.

- `tk_pack(ObjList)`  
  Packs multiple widgets provided as a list of atoms.

- `tk_create(Obj, Class, Option)`  
  Creates a canvas item of type `Class` with ID `Obj` and options.

 class line([x1,y1,x2,y2,...]) oval([x1,y1,x2,y2]) arc([x1,y1,x2,y2])
rectangle([x1,y1,x2,y2]) polygon([x1,y1,x2,y2,...])


 
