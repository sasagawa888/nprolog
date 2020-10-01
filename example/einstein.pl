/*
http://www.jekejeke.ch/idatab/doclet/prod/docs/10_dev/10_docu/03_interface/07_appendix/01_port/01_einstein.p.html
*/

rightTo(L, R, [L,R | _]).
rightTo(L, R, [_ | Rest])
	:- rightTo(L, R, Rest).

nextTo(X, Y, List) :-
	rightTo(X, Y, List).
nextTo(X, Y, List) :-
	rightTo(Y, X, List).

einstein(Houses, FishOwner) :-
   Houses = [[house,norwegian,_,_,_,_],_,[house,_,_,_,milk,_],_,_],
   member([house,brit,_,_,_,red], Houses),
   member([house,swede,dog,_,_,_], Houses),
   member([house,dane,_,_,tea,_], Houses),
   rightTo([house,_,_,_,_,green], [house,_,_,_,_,white], Houses),
   member([house,_,_,_,coffee,green], Houses),
   member([house,_,bird,pallmall,_,_], Houses),
   member([house,_,_,dunhill,_,yellow], Houses),
   nextTo([house,_,_,dunhill,_,_], [house,_,horse,_,_,_], Houses),
   member([house,_,_,_,milk,_],Houses),
   nextTo([house,_,_,marlboro,_,_], [house,_,cat,_,_,_], Houses),
   nextTo([house,_,_,marlboro,_,_], [house,_,_,_,water,_], Houses),
   member([house,_,_,winfield,beer,_], Houses),
   member([house,german,_,rothmans,_,_], Houses),
   nextTo([house,norwegian,_,_,_,_], [house,_,_,_,_,blue], Houses),
   member([house,FishOwner,fish,_,_,_], Houses).

test :- einstein(X,Y),write(X),write(Y).

