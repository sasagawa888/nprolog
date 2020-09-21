%ISO/IEC DTR 13211-3


:- op(1105,xfy,'|').

phrase(GRBody,SO) :-
    phrase(GRBody,SO,[]).


phrase(GRBody,SO,S) :-
    dcg_body(GRBody,SO,S,Goal),
    call(Goal).

dcg_expand(X) :-
    dcg_rule(X,Y),assert(Y).

expand_term(X,Y) :-
   dcg_rule(X,Y).


% This program uses append/3 as defined in the Prolog prologue.

% Expands a DCG rule into a Prolog rule, when no error condition applies.

dcg_rule(( NonTerminal, Terminals --> GRBody ), ( Head :- Body )) :-
   dcg_non_terminal(NonTerminal, S0, S, Head),
   dcg_body(GRBody, S0, S1, Goal1),
   dcg_terminals(Terminals, S, S1, Goal2),
   Body = ( Goal1, Goal2 ).
dcg_rule(( NonTerminal --> GRBody ), ( Head :- Body )) :-
   NonTerminal \= ( _, _ ),
   dcg_non_terminal(NonTerminal, S0, S, Head),
   dcg_body(GRBody, S0, S, Body).

dcg_non_terminal(NonTerminal, S0, S, Goal) :-
   NonTerminal =.. NonTerminalUniv,
   append(NonTerminalUniv, [S0, S], GoalUniv),
   Goal =.. GoalUniv.

dcg_terminals(Terminals, S0, S, S0 = List) :-
   append(Terminals, S, List).

dcg_body(Var, S0, S, Body) :-
   var(Var),
   Body = phrase(Var, S0, S).
dcg_body(GRBody, S0, S, Body) :-
   nonvar(GRBody),
   dcg_constr(GRBody),
   dcg_cbody(GRBody, S0, S, Body).
dcg_body(NonTerminal, S0, S, Goal) :-
   nonvar(NonTerminal),
   \+ dcg_constr(NonTerminal),
   NonTerminal \= ( _ -> _ ),
   NonTerminal \= ( \+ _ ),
   dcg_non_terminal(NonTerminal, S0, S, Goal).

% The following constructs in a grammar rule body
% are defined in the corresponding subclauses.

dcg_constr([]).        % 7.14.1
dcg_constr([_|_]).     % 7.14.2 - terminal sequence
dcg_constr(( _, _ )).  % 7.14.3 - concatenation
dcg_constr(( _ ; _ )). % 7.14.4 - alternative
                       % 7.14.5 - if-then-else
dcg_constr(( _'|'_ )). % 7.14.6 - alternative
dcg_constr({_}).       % 7.14.7
dcg_constr(call(_)).   % 7.14.8
dcg_constr(phrase(_)). % 7.14.9
dcg_constr(!).         % 7.14.10
% dcg_constr(\+ _).    % 7.14.11 - not (existence implementation dep.)
% dcg_constr((_->_)).  % 7.14.12 - if-then (existence implementation dep.)

% The principal functor of the first argument indicates
% the construct to be expanded.

dcg_cbody([], S0, S, S0 = S ).
dcg_cbody([T|Ts], S0, S, Goal) :-
   dcg_terminals([T|Ts], S0, S, Goal).
dcg_cbody(( GRFirst, GRSecond ), S0, S, ( First, Second )) :-
   dcg_body(GRFirst, S0, S1, First),
   dcg_body(GRSecond, S1, S, Second).
dcg_cbody(( GREither ; GROr ), S0, S, ( Either ; Or )) :-
   \+ subsumes_term(( _ -> _ ),GREither),
   dcg_body(GREither, S0, S, Either),
   dcg_body(GROr, S0, S, Or).
dcg_cbody(( GRCond ; GRElse ), S0, S, ( Cond ; Else )) :-
   subsumes_term(( _GRIf -> _GRThen ), GRCond),
   dcg_cbody(GRCond, S0, S, Cond),
   dcg_body(GRElse, S0, S, Else).
dcg_cbody(( GREither '|' GROr ), S0, S, ( Either ; Or )) :-
   dcg_body(GREither, S0, S, Either),
   dcg_body(GROr, S0, S, Or).
dcg_cbody({Goal}, S0, S, ( Goal, S0 = S )).
dcg_cbody(call(Cont), S0, S, call(Cont, S0, S)).
dcg_cbody(phrase(Body), S0, S, phrase(Body, S0, S)).
dcg_cbody(!, S0, S, ( !, S0 = S )).
dcg_cbody(\+ GRBody, S0, S, ( \+ phrase(GRBody,S0,_), S0 = S )).
dcg_cbody(( GRIf -> GRThen ), S0, S, ( If -> Then )) :-
   dcg_body(GRIf, S0, S1, If),
   dcg_body(GRThen, S1, S, Then).


