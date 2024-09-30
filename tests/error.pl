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

%assert asserta assertz
:- n_error(assert(1),39).
:- n_error(asserta(1),39).
:- n_error(assertz(1),39).
:- n_error(assert(write),2).
:- n_error(asserta(write),2).
:- n_error(assertz(display),2).

%call 
:- n_error(call(1),39).
:- n_error(call(a),41).

%break end_of_file
:- n_error(break(1),67).
:- n_error(end_of_file(1),67).

%length
:- n_error(length(1,1),10).
:- n_error(length([],a),19).
:- n_error(length([],0,2),67).
:- n_error(length([a|b],N),7).
:- n_error(length([],-1),49).

%member
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

%write writeq display put
:- n_error(write(1,2),20).
:- n_error(write(user_output,a,b),67).
:- n_error(writeq(1,2),20).
:- n_error(writeq(user_output,a,b),67).
:- n_error(display(2,1),20).
:- n_error(display(user_output,a,b),67).
:- n_error(put(a),19).
:- n_error(put(user_output,a),19).
:- n_error(put(user_output,77,a),67).

%inc dec 
:- n_error(inc(1,a),19).
:- n_error(inc(a,2),19).
:- n_error(inc(1,2,3),67).
:- n_error(dec(1,a),19).
:- n_error(dec(a,2),19).
:- n_error(dec(1,2,3),67).

%record
:- n_error(eraseall(1),11).
:- n_error(eraseall(a,b),67).
:- n_error(key(1,X),11).
:- n_error(key(a,b),40).
:- n_error(instance(a,X),19).
:- n_error(instance(0,a),40).
:- n_error(instance(0,X,3),67).
:- n_error(nref(a,X),19).
:- n_error(pref(a,X),19).
:- n_error(recorda(1,a,Y),11).
:- n_error(recorda(assert,a,Y),2).
:- n_error(recorda(foo,a,_,y),67).
:- n_error(recordz(1,a,Y),11).
:- n_error(recordz(assert,a,Y),2).
:- n_error(recordz(foo,a,_,y),67).

%timer
:- n_error(ctr_set(-1,0),7).
:- n_error(ctr_set(31,0),7).
:- n_error(ctr_set(0,a),19).
:- n_error(ctr_set(0,1,a),67).
:- n_error(ctr_inc(-1,0),7).
:- n_error(ctr_inc(31,0),7).
:- n_error(ctr_inc(0,a),40).
:- n_error(ctr_inc(0,1,a),67).
:- n_error(ctr_dec(-1,0),7).
:- n_error(ctr_dec(31,0),7).
:- n_error(ctr_dec(0,a),40).
:- n_error(ctr_dec(0,1,a),67).
:- n_error(ctr_is(-1,0),7).
:- n_error(ctr_is(0,a),40).
:- n_error(ctr_is(0,1,a),67).

%consult reconsult
:- n_error(consult(1),11).
:- n_error(reconsult(1),11).
:- n_error(consult(1,2),67).
:- n_error(reconsult(1,2),67).

%file
:- n_error(told(1),67).
:- n_error(telling(1,2),67).
:- n_error(seeing(a),40).
:- n_error(see('###.##',1),67).

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
:- n_error(stdin(user_input,1),39).

%stdout
:- n_error(stdout(a,write(1)),20).
:- n_error(stdout(a,b,c),67).
:- n_error(stdout(user_output,1),39).

%stdinout
:- n_error(stdinout(a,user_output,write(1)),20).
:- n_error(stdinout(user_input,b,write(1)),20).
:- n_error(stdinout(a,b,c,d),67).
:- n_error(stdinout(user_input,user_output,1),39).


%shell
:- n_error(shell(1),11).
:- n_error(shell,67).
:- n_error(shell(1,2),67).

%op 
:- n_error(op(a,fx,b),19).
:- n_error(op(-1,fx,b),58).
:- n_error(op(1201,fx,b),58).
:- n_error(op(500,a,b),38).
:- n_error(op(500,xfx,[1]),11).
:- n_error(op(500,xfx,a,b),67).

%current_op
:- n_error(current_op(a,yfx,b),19).
:- n_error(current_op(1201,yfx,b),58).
:- n_error(current_op(100,[1],b),38).
:- n_error(current_op(100,ff,X),38).
:- n_error(current_op(100,xfx,[1]),11).
:- n_error(current_op(100,xfx,b,a),67).


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


%cursol
:- n_error(ansi_cup(a,1),19).
:- n_error(ansi_cup(2,a),19).
:- n_error(ansi_cup(A,1),36).
:- n_error(ansi_cup(2,B),36).
:- n_error(ansi_cup(2,3,4),67).
:- n_error(ansi_cuu(a),19).
:- n_error(ansi_cuu(1,2),67).
:- n_error(ansi_cud(a),19).
:- n_error(ansi_cud(1,2),67).
:- n_error(ansi_cuf(a),19).
:- n_error(ansi_cuf(1,2),67).
:- n_error(ansi_cub(a),19).
:- n_error(ansi_cub(1,2),67).
:- n_error(ansi_scp(1),67).
:- n_error(ansi_rcp(1),67).
:- n_error(ansi_ed(1),67).
:- n_error(ansi_el(1),67).

%arg 
:- n_error(arg(a,foo(1,2),X),19).
:- n_error(arg(-1,foo(1,2),X),49).
:- n_error(arg(1,X,Y),36).
:- n_error(arg(1,write(1),X,Y),67).

%string_length
:- n_error(string_length(1,X),9).
:- n_error(string_length($sdf$,a),19).
:- n_error(string_length($asdf$,X,y),67).

%system 
:- n_error(system(1),7).

%name
:- n_error(name(1,X),11).
:- n_error(name($asdf$,2),11).
:- n_error(name($asdf$,[1],d),67).

%listing 
:- n_error(listing(1),7).
:- n_error(listing(a-3),7).
:- n_error(listing(a,2),67).

%gc
:- n_error(gc(t),7).
:- n_error(gc(full,1),67).

%eq
:- n_error(eq(1,2,3),67).

%concat
:- n_error(concat(1,$asdf$,X),9).
:- n_error(concat($123$,2,Y),9).
:- n_error(concat($123$,$asdf$,1),40).
:- n_error(concat([1,2],X),9).
:- n_error(concat([$as$,$df$],a),40).
:- n_error(concat($asdf$,$asdf$,X,y),67).

%current_predicate
:- n_error(current_predicate(1),7).
:- n_error(current_predicate(foo,2),67).

%date date_day
:- n_error(date(1),40).
:- n_error(date(X,Y),67).
:- n_error(date_day(1,Y),7).
:- n_error(date_day(1,2,3),67).

%functor
:- n_error(functor(X,$asdf$,3),48).
:- n_error(functor(X,foo,a),19).
