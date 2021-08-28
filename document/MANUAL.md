# N-Prolog User's manual
under construction.

### □ [Filename]
Read from a file into a database using a consult predicate.
-When using Filename, the resoncult predicate is used.
You can specify multiple files. [Filename1, filename2, ...] 

### □ abolish(name/Arity)
Removes all clauses with the specified name arity from the data berth. 

### □ abort
Stop the current program. Return to the interpreter after the program ends.
If the program is compiled, abort restarts its goal. 

### □ ansi_cuu(N)
Move the cursor up N lines. 

### □ ansi_cud(N)
Move the cursor down N lines. 

### □ ansi_cuf(N)
Move the cursor forward N digits. 

### □ ansi_sub(N)
Move the cursor back N digits. 

### □ ansi_cpr(Row,Col)
The predicate ansi_cpr is used to know the current cursor position.
If the arguments Row and Col are not assigned, the coordinates of the current cursor position are in rows and columns.
Unify each argument.
If it has been assigned, compare that number with the coordinates of the current position. 

### □ ansi_scp
The predicate ansi_scp saves the current cursor position and the character attributes at that position. 

### □ ansi_rcp
The predicate ansi_rcp restores the cursor position and attributes saved by ansi_scp. 

### □ ansi_ed

### □ ansi_el

### □ ansi_sgr(G)
The predicate ansi_sgr sets graphic attributes. G can be an integer or a list of integers.
The following are standard values only and may differ depending on the model. 

- 0 Reset all attributes to default.
- 1 emphasis
- 4 Underline
- 5 Blink
- 7 Reverse
- 8 secret
- 30 black
- 31 Red
- 32 green
- 33 yellow
- 34 blue
- 35 Magenta
- 36 Light blue
- 37 white
- 40 Background color black
- 41 Background color red
- 42 Background color green
- 43 Background color yellow
- 44 Background color blue
- 45 Background color Magenta
- 46 Background color light blue
- 47 Background color white 


### □ arg(N,Term,X)
Unify X to the Nth value of the term.
(Arguments are numbered from 1 in the increasing direction.) 

### □ arg0(N,Term,X)
Unify X to the value of the N + 1th argument of the term.
(Arguments are numbered from 0 in the increasing direction.) 

### □ assert(Clause)
Add a clause to the end of the predicate. 

### □ asserta(Clause)
Add a clause to the top of the predicate. 

### □ assertz(Clause)
Add a clause to the end of the predicate.

### □ atom(X)
Check if X is an atom. 

### □ atom_string(Atom,String)
Convert an atom to a string or convert a string to an atom. 

### □ atomic(X)
Check if X is an atom data type.

### □ break
Suspend program execution and display an interpreter prompt.
The program can be restarted by the following types: 

end_of_file

### □ call(P)
Call the interpreted goal P. 

### □ chdir(Path)
Change or revert to the current directory.

### □ clause(Head,Body)
Unify Head and Body to the head and body of the node, respectively.
Head must be assigned.
example 


```
?- assert((foo(X) :- write(X))).
yes
?- clause(foo(X),B).
X = v_1
B = (write(v_1));
no
?- 
```

### □ close(Handle)
Closes the file specified by Handle. 

### □ ctr_dec(Ctr,X)
Decreases the value of a counter and returns the previous value of that counter. 

### □ ctr_inc(Ctr,X)
Increases the value of a counter and returns the previous value of that counter. 

### □ ctr_is(Ctr,X)
Returns the current counter value. 

### □ ctr_set(Ctr,X)
Set the counter to the specified value. 

### □ current_op(Proc,Assoc,Op)
Returns the operator constants currently defined in the database while backtracking. 

### □ current_predicate(Predicate)
Returns the predicate currently defined in the database while backtracking.

### □ date(date(Year,Month,Day))
Set the year, month, and day. 

### □ date_day(date(Year,Month,Day),WeekDay)
Returns the day of the week on a given date as a number between 0 (Sunday) and 6 (Saturday). 

### □ dec(N,X)
Subtract 1 from the number N and give it to the value X. 

### □ delete(Filename)
Delete the specified file. 

### □ directory(Path,Name,Mode,Time,Date,Size)
List the directory files specified by Path.

example 

```
?- directory('./',A,B,C,D,E).
A = 'link.c'
B = file
C = time(13,20,47)
D = date(2020,10,4)
E = 4281 ;
A = 'compute.o'
B = file
C = time(7,54,38)
D = date(2020,10,18)
E = 37544 .
```

### □ display(Term)
Write the term to standard output with prefix notation. 

### □ dpu(Handlein,Handleout)
Allocate a second fundle to the open file.

### □ edit(Filename)
Switch from the interpreter to the editor for editing the file specified by Filename.
Call nano as an editor. When you exit nano, the contents of the file will be read into the interpreter.
If the environment variable EDITOR has a value, call that editor.

example 

```
EDITOR=emacs
```

### □ eq(X,Y)
Check if X and Y are the same data object and are stored at the same address. 

### □ expand_term(Term,Newterm)
DCG: Converts a term in a limited clause grammar to an equivalent Prolog term. 

### □ float(X)
Check if X is a floating point number.

### □ float_text(Float,Text,Format)
Converts a floating point number to a string according to the Format specification, or converts a string to a floating point number.

format is one of the following:

- general 0s following are suppressed.
- fixed (N) N gives the position of the decimal point (0-15).
- scientific (N) N gives the number of decimal places in exponential notation. 

### □ flush
Remove all characters in the type-ahead buffer.

### □ functor(Struct,Name,Arity)
Returns the structure name and arity. 

### □ gc(Amount)
Launch garbage collection.
When the argument is full, the cells that are no longer needed in the heap area are collected. 

### □ get(Char)
Read the next character from a standard input device, skipping unprinted characters,
Unify the ASCII value with Char. 

### □ get0(Char)
Read the next character from a standard input device, skipping unprinted characters,
Unify the ASCII value with Char. get0 does not skip non-printing characters. 

### □ get0_noecho(Char)
Read the following characters from the standard input device and unify the ASCII value to Char.
get0_noecho does not display the character on the standard output device. 

### □ halt
Exits the interpreter. 

### □ instance(Ref,Term)
Returns the term for that reference number. 

### □ integer(X)
Check if X is an integer. 

### □int_text(Integer,String)
Convert an integer to a string, or convert a string to an integer. 

### □ X is E 
Evaluate E and unify its value to X.

### □ keysort(L1,L2)
Sort the list L1 in standard order. List elements must be in the form Key_Value.
The sorted list is returned to L2. Even if it is duplicated, it won't be united. 

### □ leash(Mode)
Constrain the port to the specified Mode. 

### □ length(L,N)
Change the length of the list back to N. 

### □ listing
Write all current database predicates to standard output. 

### □ listing(Name/Arith)
### □ listing([Name/Arity,Name/Arity])
Write all clauses to the specified predicate or list of predicates in the current database to standard output. 

### □ list_text(List,AtomString)
Convert a character list to an atom (if the atom already exists) or a string, or convert an atom or string
Convert to a character list. 

### □ mkdir(Path)
Create a new directory. 

### □ name(Atom,List)
Convert a list to an atom, or convert an atom or an integer to a list. 

### □ open(Handle,Filename,Access)
Open an existing file. 

Access is one of the following 

```
r read
w write
rw read and write
a append
ra read and append
```

### □ read(Term)
Read terms from standard input devices. 

### □ read(Handle,Term)
Read terms from a file. 

### □ read_line(Handle,X)
Read one line from the file specified by Handle.

### □ recorda(Key,Term,Ref)
Predicates a term and returns a new reference number for that term. 

### □ recordz(Key,Term,Ref)
Adds a term at the end of the predicate and returns the reference number assigned to that term. 

### □ recordh(Table_name,Sort_key,Term)
Record the term in the hash table. 

### □ ref(X)
Check if X is a reference number. 

### □ removeallh(Table_name)
Delete the hash table. 

### □ removeh(Table_name,Sort_key,Term)
Remove a term from the hash table.

### □ reset_op
Returns the operator definition to its default value.

### □ retract (Clause)
Remove a clause from the database. 

### □ retrieveh(Table_name,Sort_key,Term)
Returns a term from the hash table.

### □ rename(Filename,Newname)
Rename the file. 

### □ rmdir(Path)
Delete the directory. 

### □ shell(Command)
Execute the BASH command and succeed. 

### □sort(L1.L2)
Sort list L1 into standard order, eliminate duplication and return sorted list to L2. 

### □ spy(Name/Arity)
Set a predicate as a debug spy point. 

### □ stdin(FileHandle,Goal)
Change standard input during that goal.

### □ stdout(FileHandle.Goal)
Change standard input during that goal.

### □ stdinout(InFile,OutFile,goal)
During that goal, change standard input and standard output. 

### □ string(X)
Check if X is a string. 

### □ string_length(String,Length)
Returns the length of the string. 

### □ string_term(String,Term)
Change the string to a term.

### □ substring(InString,N,Length,OutString)
Extract substrings from strings.
N is a natural number starting from the starting position 1.
Length is the length of the character string to be extracted 

### □ syntaxerrors(Old,New)
Specify whether to output the syntax error message or check the current setting.
An error message is output with yes, and no error message is output with no. 

### □ system(P)
Check if P is an embedded predicate. 

### □ tab(N)
Write the specified number of space characters to the standard output device. 

### □ tab(Handle,N)
Write the specified number of space characters in the file. 

### □ tell(Filename)
Open a file for output and make it the current output file. 

### □ telling(X) 
Returns the name of the output file opened by tell.

### □ time(time(Hours,Minutes,Seconds))
Returns hour, minute, and second. 

```
hour   [0-23]
minute [0-59]
second [0-61]
```

### □ trace
Turn on the debugger. 

### □ true
Goals are always successful. 

### □ var(X)
Check if X is the assigned variable. 

### □ write(Term)
Write to standard output device. 

### □ write(Handle,Term)
Write the term in the specified file. 

### □ writeeq(Term)
Write to standard output device so that the term can be read as a Prolog term
Enclose the atom and function in quotation marks. 

### □ writeeq(Time,Term)
Write the term to the specified file so that the term can be read as a Prolog term
Enclose the atom and function in quotation marks. 

## Debugger command
Start debugging by starting the program. Program reaches spy points
Will be executed. When that happens, the debugger stops the program and calls it.
Show the port and the goal where the current program is located.
For example, turn on the debugger, set the spy point to, my_appendn and predicate
Start debugging my_append. 

```
?- ['tests/test.pl'].
yes
?- trace.
yes
?- spy(my_append/3).
yes
?- my_append([1,2,3],[4,5],X).
** (0) CALL: my_append([1,2,3],[4,5],X)?> 
** (0) REDO: my_append([1,2,3],[4,5],X)?> 
** (1) CALL: my_append([2,3],[4,5],v_4)?> 
** (1) REDO: my_append([2,3],[4,5],v_4)?> 
** (2) CALL: my_append([3],[4,5],v_8)?> 
** (2) REDO: my_append([3],[4,5],v_8)?> 
** (3) CALL: my_append([],[4,5],v_12)?> 
X = [1,2,3,4,5] .
** (3) EXIT: my_append([],[4,5],v_12)?> 
** (2) EXIT: my_append([3],[4,5],v_8)?> 
** (1) EXIT: my_append([2,3],[4,5],v_4)?> 
** (0) EXIT: my_append([1,2,3],[4,5],X)?> 
yes
?- 
```

Run notrace when debugging is complete. Failure to do this will slow down execution. 

```
?- notrace.
```

The following display items are symbols that indicate how the debugger has reached its current goal. 

- ** Indicates that the goal is a spy point.
- *> Indicates that the goal is a spy point and that the goal has been reached as a result of the skip command.
- > The goal is not a spy point, but indicates that you have reached this goal as a result of the skip command.
- -> x command result Indicates that the debugger is reversing the path to the previous selection point. 

There are the following four ports.

- CALL is the port where the goal is called. The interpreter gives a number for each goal call.
The numbers start at 0 when the debugger is called and end at 0 when debugging is finished.

- EXIT is a port through which the program exits when the goal is successful.

- REDO is a port where the program re-enters the goal with backtracking.

- FAIL is a port through which the program exits when the goal fails. 


### a
Suspend and terminate the program. Turn off the debugger and prompt for the interpreter
Display. 

### b
The program being debugged does not exit and prompts for an interpreter.
By typing end_of_file, the suspended state will be released and you can continue debugging.
can. As many interpreter prompts as there are valid interruptions? Is added.
For example, when interruption is enabled three times, the interpreter prompts:
Is displayed.

```
???-
```

### c
Instructs the debugger to creep to the next port. using this method
You can follow the execution step by step. Enter key is the same as entering c. 

### d
Shows the current goal. 

### e
Exit the interpreter. This command returns you to the Linux prompt. 

### f
Advance the debugger directly to the FAIL port. That the goal is already a failure
This command is valid if you know it. 

### h
Display the help screen. 

### l
Leap from spy point to spy point.
Don't go step-by-step at the current spypoint program execution
You can skip to the next spy point. 

### n
Turn off the debugger. 

### q
Skip to the goal's EXIT or FAIL port.
However, if there is a set of spy points in that goal, execution will stop at that spy point. 

### s
Even if there are other spy points in the goal, skip to the exit port or FAIL port of that goal
To do. This command is only available from the CALL or redo ports. 

### <esc>
It is the same as entering the escape key s. 

### w
Write down the current goal. 

### X
It can be used on the FAIL port or the redo port.
Causes the debugger to continue failing until it reaches the CALL or EXIT port. 

### @
Calls a secondary goal and returns to the debugger as soon as the goal is finished. 

### ;
Used on the EXIT port, which causes the debugger to go to the redo port of the current goal. 




## DCG
The following is an example from Professor Hideyuki Nakashima's "Prolog".

A dog bites a postman.

This English sentence has a structure. Its structure follows certain grammatical rules. 


```
Sentence-> noun phrase, verb phrase
Noun phrases-> articles, nouns
Article-> a
Noun-> dog
Noun-> postman
Verb phrase-> verb, noun phrase
Verb-> bits 
```
It's possible to write this directly in Prolog, but there's an easier way.
That is DCG. It is possible to write the above rules almost as they are.

Write the following code to a file and load it with consult in the same way as the Prolog code. 


```
s --> np,vp.
np --> det,n.
det -->[a].
n -->[dog].
n -->[postman].
vp --> v,np.
v -->[bites].
```

The grammar category is abbreviated. 

```
sentence　s
noun　n
noun　phrase　np
verb　v
determiner　det
verb　phrase
```

Let's run this on the N-Prolog processing system.
You can check if the sentence is correct with the predicate phrase. 


```
| ?- phrase(s,[a,dog,bites,a,postman]).
yes
| 
```

In this way, it was confirmed that the sentence given in the list has the given sentence structure. What if you give the wrong sentence? 


```
| ?- phrase(s,[bites,a,dog,a,postman]).
no
|
```

False is returned. It violates the grammar rules.

Interestingly, you can also generate sentences that meet grammatical rules. 

```
| ?- phrase(s,X).
X = [a,dog,bites,a,dog];
X = [a,dog,bites,a,postman];
X = [a,postman,bites,a,dog];
X = [a,postman,bites,a,postman];
no
| 
```

When I typed a semicolon and backtracked, some sentences came out.
The meaning is strange, but it follows the grammatical rules. 


## compiler
It's still incomplete, but it also comes with a compiler. Loading the compiler at startup.

compile_file(filename)

Make a file with the Prolog code to compile in this way.
Convert to C language and compile to object file with GCC.

For example, when compiling 9queens

compile_file('tests/queens.pl').

will do. This will generate a file called queens.o.

Enter ['tests/queens.o']. Or consult('queens.o'). To load it.
After that, you can use it like a normal predicate.

Partially processed tail recursive optimization. With queens, the execution speed is close to that of SWI-Prolog. 


## Hello

My name is Kenichi Sasagawa.
I learned prolog at Arity/Prolog in the 1980s.
Now, I'm making a Prolog interpreter and compiler.
I want to make it compatible with the familiar Arity/Prolog.
Thank you.