:- module(iso,[sub_atom/5,numbervars/3,'$VAR'/1,term_variables/2]).


% sub_atom(+Atom, ?Before, ?Length, ?After, ?SubAtom)

sub_atom(Atom, Before, Length, After, SubAtom) :-
    atom(Atom),
    atom_chars(Atom, Chars),
    append(Front, Rest, Chars),
    append(Middle, Back, Rest),
    length(Front, Before),
    length(Middle, Length),
    length(Back, After),
    atom_chars(SubAtom, Middle).


numbervars(Term, Start, End) :-
    numbervars_(Term, Start, End).
numbervars_(Var, N, N1) :-
    var(Var),
    !,
    Var = '$VAR'(N),
    N1 is N + 1.
numbervars_(Term, N0, N) :-
    atomic(Term),
    !,
    N = N0.
numbervars_(Term, N0, N) :-
    Term =.. [_|Args],
    numbervars_list(Args, N0, N).
numbervars_list([], N, N).
numbervars_list([H|T], N0, N) :-
    numbervars_(H, N0, N1),
    numbervars_list(T, N1, N).


term_variables(Term, Vars) :-
    term_variables_(Term, [], Vars).
term_variables_(Var, Acc, Vars) :-
    var(Var),
    !,
    ( member(Var, Acc) ->
        Vars = Acc
    ;
        Vars = [Var|Acc]
    ).
term_variables_(Term, Acc, Vars) :-
    atomic(Term),
    !,
    Vars = Acc.
term_variables_(Term, Acc, Vars) :-
    Term =.. [_|Args],
    term_variables_list(Args, Acc, Vars).
term_variables_list([], Vars, Vars).
term_variables_list([H|T], Acc, Vars) :-
    term_variables_(H, Acc, Acc1),
    term_variables_list(T, Acc1, Vars).