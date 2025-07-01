

rule([b,e],[c,e]).
rule([c,e],[c,a]).

convert([],[]).
convert([X1,X2|Rest],[Y1,Y2|Rest1]) :-
        rule([X1,X2],[Y1,Y2]),
        convert(Rest,Rest1).
convert([X1,X2|Rest],[X1,X2|Rest1]) :-
        convert(Rest,Rest1).