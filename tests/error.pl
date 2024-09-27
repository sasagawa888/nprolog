/*
#define SYNTAX_ERR      1
#define BUILTIN_EXIST   2
#define CANT_READ       3
#define NOT_COMPUTABLE  4
#define OUT_OF_RANGE    5
#define MALLOC_OVERF    6
#define WRONG_ARGS      7
#define NOT_NUM         8
#define NOT_STR         9
#define NOT_LIST        10
#define NOT_ATOM         11
#define ILLEGAL_OPL_INPUT   12
#define UNCAUGHT_EXCEPTION       13
#define CANT_OPEN       14
#define FILE_EXIST      15
#define ILLEGAL_ARGS    16
#define NOT_CONS        17
#define CANT_MODIFY     18
#define NOT_INT         19
#define NOT_STREAM      20
#define NOT_OUT_STREAM  21
#define NOT_IN_STREAM   22
#define NOT_CHAR        23
#define NOT_FLT         24
#define CTRL_OVERF      25
#define END_STREAM      26
#define DIV_ZERO        27
#define CANT_PARSE      28
#define NOT_ARITHMETIC  29
#define FLT_OVERF       30
#define FLT_UNDERF      31
#define STACK_OVERF     32
#define SYSTEM_ERROR    33
#define UNDEF_PRED		34
#define EOF_ERROR       35
#define INSTANTATION_ERR    36
#define EXPONENT_ERR    37
#define OPE_SPEC_ERR    38
#define NOT_CALLABLE    39
#define NOT_VAR         40
#define EXISTENCE_ERR   41
#define NOT_SOURCE      42
#define ALIAS_EXIST     43
#define NOT_IO_MODE     44
#define NOT_CLOSE_OPTION    45   
#define NOT_STREAM_OPTION   46
#define NOT_OUTPUT_STREAM   47
#define NOT_ATOMIC          48
#define NOT_LESS_THAN_ZERO  49
#define NOT_COMPOUND        50
#define NON_EMPTY_LIST      51
#define NOT_INPUT_STREAM    52
#define PAST_EOF_INPUT      53
#define EVALUATION_ERR      54
#define STATIC_PROCEDURE    55
#define PRED_INDICATOR      56
#define NOT_OPEN_OPTION     57
#define OPE_PRIORITY_ERR    58
#define MODIFY_OPE_ERR      59
#define NOT_CHAR_CODE       60
#define RESOURCE_ERR        61
#define NOT_ORDER           62
#define NOT_TERM            63
#define RECORD_OVERF        64
#define NOT_RECORD          65
#define VARIANT_OVERF       66
#define ARITY_ERR           67

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
