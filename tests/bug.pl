
maplist(P,[]).
maplist(P,[E|Es]) :-
        %X =.. [P,E],
        %call(X),
        maplist(P,Es).