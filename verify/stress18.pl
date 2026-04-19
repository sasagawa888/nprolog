

/*
?- boss3(1,L,N,Y,Z,A).
L = [p,q]
N = 2
Y = a
Z = ok
A = y .
yes
?- boss3(2,L,N,Y,Z,A).
L = [r]
N = 1
Y = b
Z = ng
A = w .
yes
?- 
*/

boss(X,L,N,Y,Z,A) :-
    ( X = 1 ->
        Y = a
    ;
        Y = b
    ),
    ( Y = Z ->
        Z = ok
    ;
        Z = ng
    ),
    ( X = 1 ->
        ( X = 2 ->
            A = x
        ;
            ( X = 1 ->
                A = y
            ;
                A = z
            )
        )
    ;
        A = w
    ),
    ( A = y ->
        N = 2, L = [p,q]
    ;
        N = 1, L = [r]
    ),
    ( A = y ; A = z ),
    ( true -> true ; true ),
    length(L,N).

boss3(X,L,N,Y,Z,A) :-
    ( X = 1 ->
        Y = a
    ;
        Y = b
    ),
    ( Y = a ->
        Z = ok
    ;
        Z = ng
    ),
    ( X = 1 ->
        ( X = 2 ->
            A = x
        ;
            ( X = 1 ->
                A = y
            ;
                A = z
            )
        )
    ;
        A = w
    ),
    ( A = y ->
        N = 2, L = [p,q]
    ;
        N = 1, L = [r]
    ).