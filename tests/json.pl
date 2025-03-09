% JSON


term_to_json_str(X,S) :-
    term_to_json(X,Y),
    string_term(S,Y).

term_to_json(X,J) :-
    string(X),
    string_term(X,Y).

term_to_json(X,J) :-
    atom(X),
    string_term(X,Y).

term_to_json(X,X) :-
    number(X).


term_to_json(X,J) :-
    list(X),
    term_to_json_list(X,J).


term_to_json_list([],[]).
term_to_json_list([L|Ls],[J|Js]) :-
    term_to_json(L,J),
    term_to_json_list(Ls,Js).


    
