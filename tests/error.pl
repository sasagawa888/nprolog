/*
SYNTAX_ERR      1
BUILTIN_EXIST   2
CANT_READ       3
NOT_COMPUTABLE  4
OUT_OF_RANGE    5
MALLOC_OVERF    6
WRONG_ARGS      7
NOT_NUM         8
NOT_STR         9
NOT_LIST        10
NOT_ATOM         11
ILLEGAL_OPL_INPUT   12
UNCAUGHT_EXCEPTION       13
CANT_OPEN       14
FILE_EXIST      15
ILLEGAL_ARGS    16
NOT_CONS        17
CANT_MODIFY     18
NOT_INT         19
NOT_STREAM      20
NOT_OUT_STREAM  21
NOT_IN_STREAM   22
NOT_CHAR        23
NOT_FLT         24
CTRL_OVERF      25
END_STREAM      26
DIV_ZERO        27
CANT_PARSE      28
NOT_ARITHMETIC  29
FLT_OVERF       30
FLT_UNDERF      31
STACK_OVERF     32
SYSTEM_ERROR    33
UNDEF_PRED		34
EOF_ERROR       35
INSTANTATION_ERR    36
EXPONENT_ERR    37
OPE_SPEC_ERR    38
NOT_CALLABLE    39
NOT_VAR         40
EXISTENCE_ERR   41
NOT_SOURCE      42
ALIAS_EXIST     43
NOT_IO_MODE     44
NOT_CLOSE_OPTION    45   
NOT_STREAM_OPTION   46
NOT_OUTPUT_STREAM   47
NOT_ATOMIC          48
LESS_THAN_ZERO      49
NOT_COMPOUND        50
NON_EMPTY_LIST      51
NOT_INPUT_STREAM    52
PAST_EOF_INPUT      53
EVALUATION_ERR      54
STATIC_PROCEDURE    55
PRED_INDICATOR      56
NOT_OPEN_OPTION     57
OPE_PRIORITY_ERR    58
MODIFY_OPE_ERR      59
NOT_CHAR_CODE       60
RESOURCE_ERR        61
NOT_ORDER           62
NOT_TERM            63
RECORD_OVERF        64
NOT_RECORD          65
VARIANT_OVERF       66
ARITY_ERR           67

*/

%length
:- n_error(length(1,1),10).
:- n_error(length([],a),19).
:- n_error(length([],0,2),67).
:- n_error(length([a|b],N),7).
:- n_error(length([],-1),49).

%member
:- n_error(member(a,b),10).
:- n_error(member(a,$abc$),10).
:- n_error(member(a,[],s),67).

%append
:- n_error(append(a,[1,2,3],X),10).
:- n_error(append([1,2,3],b,X),10).
:- n_error(append([1,2,3],[],a),10).
:- n_error(append([1,2,3],[],X,Y),67).

%halt
:- n_error(halt(1),67).
:- n_error(halt(1,2),67).

%read_line
:- n_error(read_line(a,X),20).
:- n_error(read_line(1,X),20).
:- n_error(read_line(0,a),40).

%read_string
:- n_error(read_string(-1,X),7).
:- n_error(read_string(1025,X),7).
:- n_error(read_string(10,a),40).

%sort 
:- n_error(sort(a,X),10).
:- n_error(sort([1,3,2],a),40).
:- n_error(sort([1,3,2],1),40).
:- n_error(sort([1,2,3],X,Z),67).

%keysort
:- n_error(keysort(a,X),10).
:- n_error(keysort([a-3,b-2],a),40).
:- n_error(keysort([a-3,b-2],X,Y),67).

%compare
:- n_error(compare([1],a,b),11).
:- n_error(compare(==,a,b),62).
:- n_error(compare(=,a,b,X),67).

%classify
:- n_error(atom(a,2),67).
:- n_error(list(a,2),67).
:- n_error(float(a,2),67).
:- n_error(integer(a,2),67).
:- n_error(number(a,2),67).
:- n_error(string(a,2),67).
:- n_error(ref(a,2),67).
:- n_error(atomic(a,2),67).
:- n_error(var(a,2),67).
:- n_error(nonvar(a,2),67).

%reverse
:- n_error(reverse([1|2],X),7).
:- n_error(reverse(X,[3|4]),7).
:- n_error(reverse([1,2,3],X,Y),67).
:- n_error(reverse(1,X),10).
:- n_error(reverse(X,2),10).
:- n_error(reverse([1,2],X,Y),67).

%tab
:- n_error(tab(a),19).
:- n_error(tab(-1),49).
:- n_error(tab(1,3),20).
:- n_error(tab(a,b,c),67).

%nl 
:- n_error(nl(a),20).
:- n_error(nl(a,3,2),67).

%stdin
:- n_error(stdin(a,get(C)),20).
:- n_error(stdin(a,b,c),67).

%stdout
:- n_error(stdout(a,write(1)),20).
:- n_error(stdout(a,b,c),67).

%shell
:- n_error(shell(1),11).
:- n_error(shell,67).
:- n_error(shell(1,2),67).

%see 
:- n_error(see('###.##',1),67).

%functions
:- n_error(A is sin(a),54).
:- n_error(A is sin(3,1),67).
:- n_error(A is cos(a),54).
:- n_error(A is cos($abc$),54).
:- n_error(A is cos(3,1),67).
:- n_error(A is tan(a),54).
:- n_error(A is 1/0, 27).
:- n_error(A is 1//0, 27).
:- n_error(A is 1.2 mod 3,19).
:- n_error(A is 1 mod 3.2,19).
:- n_error(A is sin(X),36).
:- n_error(A is X << 2,36).
:- n_error(A is 1 >> Y,36).
