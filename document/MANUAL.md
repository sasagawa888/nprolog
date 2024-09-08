# N-Prolog User's manual

### □ ;
Represents the separation between goals. Disjunction (OR).

### □ ,
Represents the separation between goals. Conjunction (AND).

### □ E1 < E2
Checks if the value of `E1` is less than the value of `E2`.

### □ T1 = T2
Attempts to unify `T1` and `T2`.

### □ T1 \\= T2
Fails if `T1` unifies with `T2`.

### □ Struct =.. List
Known as "univ". Converts a structure to a list or a list to a structure.

### □ E1 =< E2
Checks if the value of `E1` is less than or equal to the value of `E2`.

### □ E1 > E2
Checks if the value of `E1` is greater than the value of `E2`.

### □ E1 >= E2
Checks if the value of `E1` is greater than or equal to the value of `E2`.

### □ E1 =:= E2
Checks if the value of `E1` is equal to the value of `E2`.

### □ E1 =\\= E2
Checks if the value of `E1` is not equal to the value of `E2`.

### □ T1 == T2
Checks if `T1` and `T2` are identical (equivalent).

### □ T1 \\== T2
Checks if `T1` and `T2` are not identical (not equivalent).

### □ T1 @< T2
Checks if `T1` precedes `T2`.

### □ T1 @=< T2
Checks if `T1` precedes `T2` or is equal to it.

### □ T1 @> T2
Checks if `T1` succeeds `T2`.

### □ T1 @>= T2
Checks if `T1` succeeds `T2` or is equal to it.

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

### □ ansi_cub(N)
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
The predicate ansi_ed erases the display.

### □ ansi_el
The predicate ansi_el erases from the cursor position to end of line.

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
Unify X with the result of subtracting 1 from N.

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
Call Edlog as an editor. When you exit Edlog, the contents of the file will be read into the interpreter.
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
Deconstruct the structure Struct into its name Name and arity Arity, or construct a structure Struct from the given Name and Arity.

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
Evaluate the arithmetic expression E and unify the result with X.

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
Execute the shell command and succeed.

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

### □ writeq(Term)
Write to standard output device so that the term can be read as a Prolog term
Enclose the atom and function in quotation marks. 

### □ writeq(Time,Term)
Write the term to the specified file so that the term can be read as a Prolog term
Enclose the atom and function in quotation marks. 

## Extended Predicates

- `atom_concat(E1, E2, X)`  
  Unifies `X` with the atom that results from concatenating atoms `E1` and `E2`.

- `append(L1, L2, X)`  
  Unifies `X` with the list that results from concatenating lists `L1` and `L2`.

- `bitween(start, end, Value)`  
  Unifies `Value` with integers from `start` to `end`.

- `char_code(E, X)`  
  Unifies `X` with the internal code of character `E`.

- `compile_file(fn)`  
  Compiles the Prolog code from the file `fn` and generates an object file.

- `compound(E)`  
  Checks whether `E` is a compound term.

- `ground(E)`  
  Checks whether `E` contains no uninstantiated variables.

- `heapd(start, end)`  
  Displays the heap region addresses from `start` to `end`.

- `member(E, L)`  
  Checks whether atom `E` is a member of the list `L`.

- `measure(E)`  
  Measures and displays the execution time of the predicate `E`.

- `predicate_property(E, X)`  
  Unifies `X` with the properties of the predicate `E`.

- `reverse(L, X)`  
  Unifies `X` with the list that results from reversing the list `L`.

- `bagof(X, Pred, Bag)`  
  Collects all `X` that unify with the predicate `Pred` into the list `Bag`.

- `setof(X, Pred, Bag)`  
  Collects all `X` that unify with the predicate `Pred` into the list `Bag`, with duplicates removed.

- `findall(X, Pred, Bag)`  
  Collects all `X` that unify with the predicate `Pred` into the list `Bag`.

## function

- pi Constant representing the value of π (pi).
- X + Y Addition.
- X - Y Subtraction.
- X * Y Multiplication.
- X / Y Division resulting in a floating-point number.
- X // Y Integer division resulting in an integer.
- X ^ Y Exponentiation (power).
- X ** Y Exponentiation (power).
- X << Y Bitwise left shift of X by Y positions (integers only).
- X >> Y Bitwise right shift of X by Y positions (integers only).
- X mod Y Modulo operation, returning the remainder of X divided by Y (integers only).
- X /\ Y Logical AND.
- X \/ Y Logical OR.
- \X Complement (bitwise NOT).
- abs(X) Absolute value of X.
- sin(X) Sine of X.
- asin(X) Arcsine (inverse sine) of X.
- cos(X) Cosine of X.
- acos(X) Arccosine (inverse cosine) of X.
- tan(X) Tangent of X.
- atan(X) Arctangent (inverse tangent) of X.
- exp(X) Exponential function of X.
- ln(X) Logarithm of X.
- log(X) Base-10 logarithm of X.
- sqrt(X) Square root of X.
- randi(n) Random integer between 0 and n (inclusive).
- random Random floating-point number between 0 and 1 (inclusive).

## Debugger command
Start debugging by running the program. When the program reaches a spy point, it will be executed. At that point, the debugger will pause the program and display the port and goal at the current position. For example, enable the debugger, set a spy point on the predicate my_appendn, and then start debugging my_append.


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

After finishing debugging, run the notrace command. If you forget to do this, it will slow down the execution of your program.

prolog

```
?- notrace.
```

The following symbols indicate how the debugger has reached the current goal:

    **: Indicates that the goal is a spy point.
    *>: Indicates that the goal is a spy point, and the goal was reached due to the skip command.
    >: The goal is not a spy point, but it was reached due to the skip command.
    -> x: Indicates that the debugger is backtracking to a previous choice point.

There are four ports:

    CALL: The port where the goal is called. The interpreter assigns a number to each goal call. The numbering starts at 0 when the debugger is called and ends at 0 when debugging finishes.
    EXIT: The port where the program exits when the goal succeeds.
    REDO: The port where the program re-enters the goal through backtracking.
    FAIL: The port where the program exits when the goal fails.

- a
Suspend and terminate the program. Turn off the debugger and return to the interpreter prompt.

- b
The program being debugged does not exit but returns to the interpreter prompt. By typing end_of_file, you can exit the suspended state and continue debugging. Multiple interpreter prompts will be displayed for each valid interruption. For example, if there are three interruptions enabled, the interpreter prompt will display:

prolog

```
???-
```

- c
Instruct the debugger to creep to the next port, allowing you to step through the execution. Pressing the Enter key has the same effect as entering the c command.

- d
Display the current goal.

- e
Exit the interpreter and return to the Linux prompt.

- f
Directly advance the debugger to the FAIL port. This command is valid if you know that the goal will fail.

- h
Display the help screen.

- l
Leap from one spy point to another. This allows you to skip the step-by-step execution and jump to the next spy point.

- n
Turn off the debugger.

- q
Skip to the EXIT or FAIL port of the goal. However, if there is a spy point set within that goal, execution will stop at that spy point.

- s
Skip to the EXIT or FAIL port of the goal, even if there are other spy points in the goal. This command can only be used from the CALL or REDO ports.
<esc>
This is the same as pressing the escape key or entering the s command.

- w
Write the current goal to the output.

- X
This command can be used at the FAIL or REDO port. It causes the debugger to continue failing until it reaches a CALL or EXIT port.

- @
Call a secondary goal and return to the debugger when that goal finishes.

- ;
At the EXIT port, this command causes the debugger to proceed to the REDO port of the current goal.


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

## Multiple World Mechanism
The multiple world mechanism similar to that implemented in Dr. Hideyuki Nakajima's Prolog/KR is extended. Use the with/2 predicate.
There is an example in the mpw.pl file in the tests folder.
See Chapter 7 https://stacks.stanford.edu/file/druid:bv252vf8932/bv252vf8932.pdf

## Edlog editor
Edlog is editor for N-Prolog.

### invoke
`edlog`  or `edlog filename` onterminal.

For more details, enter ctrl+h. see help. 

## Hello

My name is Kenichi Sasagawa.
I learned prolog at Arity/Prolog in the 1980s.
Now, I'm making a Prolog interpreter and compiler.
I want to make it compatible with the familiar Arity/Prolog.
Thank you.