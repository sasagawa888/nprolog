% JSON

:- op(500,xfy,':').

:- set_prolog_flag(string,iso).


:- module(json,[term_json/2]).

reset_json :- set_prolog_flag(string,arity).

term_json(T,J) :-
    var(J),
    term_to_json(T,J).
term_json(T,J) :-
    var(T),
    json_to_term(J,T).

term_to_json(X,J) :-
    string(X).

term_to_json('@true',"true").

term_to_json('@null',"null").

term_to_json(X,J) :-
    atom(X),
    string_term(J,X).

term_to_json(X,X) :-
    number(X).

term_to_json(X,Y) :-
    var(X),
    n_variable_convert(X,A),
    string_term(Y,A).

term_to_json((A=B),J) :-
    term_to_json(A,A1),
    term_to_json(B,B1),
    J = {A1:B1}.


term_to_json(X,J) :-
    list(X),
    term_to_json_list(X,J).


term_to_json_list([],[]).
term_to_json_list([L|Ls],[J|Js]) :-
    term_to_json(L,J),
    term_to_json_list(Ls,Js).

term_to_json(X,J) :-
    n_property(X,predicate),
    X =.. [P|A],
    string_term(P1,P),
    term_to_json_list(A,A1),
    J = {"predicate" : P1,"argument" : A1}.

term_to_json((X,Y),J) :-
    term_to_json(X,X1),
    term_to_json(Y,Y1),
    J = (X1,Y1).

term_to_json((H :- B),J) :-
    term_to_json(H,H1),
    term_to_json(B,B1),
    J = {"head":H1,"body":B1}.


json_to_term("true",'@true').

json_to_term("null",'@null').

json_to_term(X,T) :-
    string(X),
    string_term(X,T).

json_to_term(X,X) :-
    number(X).

json_to_term({"predicate":A,"argument":B},T) :-
    string_term(A,P),
    json_to_term_list(B,L),
    T =.. [P|L].

json_to_term({"head":H,"body":B},T) :-
    json_to_term(H,H1),
    json_to_term(B,B1),
    T = :-(H1,B1).

json_to_term((X:Y),T) :-
    json_to_term(X,X1),
    json_to_term(Y,Y1),
    T = (X1=Y1).

json_to_term({X,Y},T) :-
    json_to_term(X,X1),
    json_to_term(Y,Y1),
    T = (X1,Y1).
json_to_term({X},T) :-
    json_to_term(X,T).

json_to_term(X,T) :-
    list(X),
    json_to_term_list(X,T).


json_to_term_list([],[]).
json_to_term_list([L|Ls],[T|Ts]) :-
    json_to_term(L,T),
    json_to_term_list(Ls,Ts).
