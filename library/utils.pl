:- module(utils,[read_codes/2,tokenize/2]).

read_codes(Stream, Codes) :-
    get_code(Stream, C),
    ( C =  end_of_file ->
        Codes = []
    ; Codes = [C|Rest],
      read_codes(Stream, Rest)
    ).


% --- entry ---
tokenize(Codes, Tokens) :-
    tokens(Tokens, Codes, []).

tokens(T, In, Out) :-
    skip_cm(In,In1),
    tokens(T,In1,Out).
tokens([T|Ts], In, Out) :-
    skip_ws(In, In1),
    token(T, In1, In2), !,
    tokens(Ts, In2, Out).
tokens([], In, Out) :-
    skip_ws(In, Out).

% --- whitespace ---
skip_ws([C|Cs], Rest) :-
    is_space(C), !,
    skip_ws(Cs, Rest).
skip_ws(Rest, Rest).

is_space(9).   % \t
is_space(10).  % \n
is_space(13).  % \r
is_space(32).  % space

% --- comment ---
skip_cm([47,42|Cs], Rest) :-
    skip_cm1(Cs,Rest).
skip_cm1([42,47|Cs],Cs).
skip_cm1([C|Cs],Rest) :-
    skip_cm1(Cs,Rest).
skip_cm1([], []) :- !.

% --- token ---
token('<>', [60,62|Cs], Cs) :- !.
token('<=', [60,61|Cs], Cs) :- !.
token('>=', [62,61|Cs], Cs) :- !.
token(S, [C|Cs], Cs) :- one_char_sym(C, S), !.
token(N, In, Out) :- read_digits(In, Ds, Out), Ds \= [], number_codes(N, Ds), !.
token(A, In, Out) :- read_word(In, Cs, Out), Cs \= [], atom_codes(A, Cs), !.

% a symbol
one_char_sym(40,'(').
one_char_sym(41,')').
one_char_sym(44,',').
one_char_sym(46,'.').
one_char_sym(59,';').
one_char_sym(43,'+').  
one_char_sym(42,'*').
one_char_sym(60,'<').
one_char_sym(62,'>').
one_char_sym(58,':').
one_char_sym(61,'=').

% digits
read_digits([C|Cs], [C|Ds], Out) :-
    is_digit(C), !,
    read_digits(Cs, Ds, Out).
read_digits(Out, [], Out).

is_digit(C) :- C >= 48, C =< 57.

% word: [A-Za-z_][A-Za-z0-9_]*
read_word([C|Cs], [C|Ws], Out) :-
    is_word_start(C), !,
    read_word_rest(Cs, Ws, Out).
read_word(In, [], In).

read_word_rest([C|Cs], [C|Ws], Out) :-
    is_word_char(C), !,
    read_word_rest(Cs, Ws, Out).
read_word_rest(Out, [], Out).

is_word_start(C) :- is_alpha(C) ; C =:= 95.  % '_'
is_word_char(C)  :- is_alpha(C) ; is_digit(C) ; C =:= 95.

is_alpha(C) :- (C >= 65, C =< 90) ; (C >= 97, C =< 122).