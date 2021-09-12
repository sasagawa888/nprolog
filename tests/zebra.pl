% zebra puzzle
% https://coursys.sfu.ca/2018fa-cmpt-384-d1/pages/ZebraPuzzle
% Thanks to SFU
%h(Nationality, Pet, Cigarette, Drink, Color)
zebra_owner(Owner) :-
    houses(Hs),
    member(h(Owner,zebra,_,_,_), Hs).

water_drinker(Drinker) :-
	houses(Hs),
	member(h(Drinker,_,_,water,_), Hs).


houses(Hs) :-
	length(Hs, 5),                                            %  1
	member(h(english,_,_,_,red), Hs),                         %  2
	member(h(spanish,dog,_,_,_), Hs),                         %  3
	member(h(_,_,_,coffee,green), Hs),                        %  4
	member(h(ukrainian,_,_,tea,_), Hs),                       %  5
	adjacent(h(_,_,_,_,green), h(_,_,_,_,white), Hs),             %  6
	member(h(_,snake,winston,_,_), Hs),                       %  7
	member(h(_,_,kool,_,yellow), Hs),                         %  8
	Hs = [_,_,h(_,_,_,milk,_),_,_],                           %  9
	Hs = [h(norwegian,_,_,_,_)|_],                            % 10
	adjacent(h(_,fox,_,_,_), h(_,_,chesterfield,_,_), Hs),        % 11
	adjacent(h(_,_,kool,_,_), h(_,horse,_,_,_), Hs),              % 12
	member(h(_,_,lucky,juice,_), Hs),                         % 13
	member(h(japanese,_,kent,_,_), Hs),                       % 14
	adjacent(h(norwegian,_,_,_,_), h(_,_,_,_,blue), Hs),          % 15
	member(h(_,_,_,water,_), Hs),		% one of them drinks water
	member(h(_,zebra,_,_,_), Hs).		% one of them owns a zebra

adjacent(A, B, Ls) :- append(_, [A,B|_], Ls).
adjacent(A, B, Ls) :- append(_, [B,A|_], Ls).


test :- between(1,1000,N),zebra_owner(O),fail.

/*
Queries
?- zebra_owner(Owner).

?- water_drinker(Drinker).

?- houses(Houses).
*/