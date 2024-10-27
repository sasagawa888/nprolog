% monkey and banana from Bratko's book

move(state(middle,onbox,middle,hasnot),
     grasp,
     state(middle,onbox,middle,has)).

move(state(P,onfloor,P,H),
     climb,
     state(P,onbox,P,H)).

move(state(P1,onfloor,P1,H),
     push(P1,P2),
     state(P2,onfloor,P2,H)).

move(state(P1,onfloor,B,H),
     walk(P1,P2),
     state(P2,onfloor,B,H)).

canget(state(_,_,_,has)).
canget(State1) :-
    move(State1,Move,State2),
    write(Move),
    canget(State2).
    

%canget(state(atdoor,onfloor,atwindow,hasnot)).

display_room :-
     ansi_ed(),
     write('Window                          _________________'),nl,
     write('__________                       |         |  '),nl,
     write('|                                | Banana  |  '),nl,
     write('|                                |_________|  '),nl,
     write('|                                    ||       '),nl,
     write('|                                    ||       '),nl,
     write('|                                   (==)      '),nl,
     write('|                                             '),nl,
     write('                                              '),nl,
     write('                                    '),nl,
     write(' Door                 Window        '),nl,
     write('________             ________       '),nl,                    
     write('|                    |              '),nl,
     write('|                    |              '),nl,
     write('|                    |              '),nl,
     write('|                    |              '),nl,
     write('|          _______   |              '),nl,
     write('            Floor                   '),nl.

display_monkey(X,Y) :-
     ansi_cup(X,Y),
     write(' Monkey'),nl,          
     write(' (o o)'),nl,         
     write(' (   )'),nl,         
     write(' /|__|'),nl,      
     write('//    ').

display_box(X,Y) :-
     ansi_cup(X,Y),
     write('|-------|'),nl,
     write(' |     | '),nl,
     write(' | Box | '),nl,
     write(' |     | '),nl,
     write(' |_____| ').