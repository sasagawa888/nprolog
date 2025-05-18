% test for GNU-Prolog
% ?- statistics(runtime, [T0|_]), send(Vars), statistics(runtime, [T1|_]), T is T1 - T0. 
send(Vars) :-
    Vars = [S,E,N,D,M,O,R,Y],
    fd_domain(Vars, 0, 9),
    fd_all_different(Vars),
    S #\= 0,
    M #\= 0,
    1000*S + 100*E + 10*N + D + 1000*M + 100*O + 10*R + E
    #= 10000*M + 1000*O + 100*N + 10*E + Y,
    fd_labeling(Vars).
