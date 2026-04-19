
p11(X) :-
    ( X = 100 ; X = 200 ),
    !.

det_body(Head,(((_->_),_);_),_). % a->b,c;d->e,f
det_body(Head,(_->_;_),_).       % a->b;c
det_body(_,(_;_),_) :- fail,!.
det_body(_,((_;_),_),_).