/*
Originaly rewritten in Prolog by Shouzou Takeoka 2007/FEB/06
modified by Kenichi Sasagawa 2018/6/29
To play
 reconsult(sta-trek.pl).
 ?- trek.  

*/
%%%
%%% Trek in Prolog
%%% Original BASIC version is 
%%% http://www.dunnington.u-net.com/public/startrek/startrek.txt
%%% (some information in http://www.dunnington.u-net.com/public/startrek/)
%%%
%%% Rewritten in Scheme/Common Lisp by Shozo TAKEOKA (take@axe-inc.co.jp)
%%% http://www.takeoka.org/~take/
%%% CommonLisp Ver.  2006/OCT/09
%%%
%%% Prolog Ver1.0  2007/FEB/06
%%%
%%% Tested system:
%%%   SWIProlog under Windows, FreeBSD, MacOSX
%%%       http://www.swi-prolog.org/
%%%   GnuProlog under Windows, FreeBSD, MacOSX
%%%       http://www.gprolog.org/
%%%
%%%
% consult('C:/take/src/prolog/trek.pl').
% init.
% qqq.
%% enterQuad.
% newq.
%
%% todo
%%  computer.
%%   warp-energy,
%%


%for O-Prolog
irandom(R,N) :-  R is random(N).

/*
:- dynamic(irandom/2).
defRand :- retractall(irandom(_,_)).
defRand :-
	current_prolog_flag(prolog_name,'GNU Prolog'),
	%%for GnuProlog
	!,asserta((irandom(R,N) :- !,random(RR),R is floor(RR * N + 0.0))).
defRand :-
	%%for SWIProlog
	!,asserta((irandom(R,N) :- (!,R is random(N)))).
*/

:- dynamic(sec/3).
:- dynamic(quad/2).
:- dynamic(kl/4).
:- dynamic(vdb/2).
:- dynamic(damage/2).


%%%
inc(X) :-
	!,vdb(X,V),
	NN is V + 1,
	put_vdb(X,NN).

inc(X,N) :-
	!,vdb(X,V),
	NN is V + N,
	put_vdb(X,NN).
dec(X) :-
	!,vdb(X,V),
	NN is V - 1,
	put_vdb(X,NN).

dec(X,N) :-
	!,vdb(X,V),
	NN is V - N,
	put_vdb(X,NN).

put_vdb(X,V) :- 
	retract(vdb(X,_)),
	!,asserta(vdb(X,V)).
put_vdb(X,V) :- 
	!,asserta(vdb(X,V)).
%
put_damage(X,V) :- 
	retract(damage(X,_)),
	!,asserta(damage(X,V)).
put_damage(X,V) :- 
	!,asserta(damage(X,V)).
%%
put_q(X,Y,V) :- 
	!,I is X * 8 + Y,
	put_qi(I,V).
put_qi(I,V) :- 
	retract(quad(I,_)),
	!,asserta(quad(I,V)).
put_qi(I,V) :- 
	!,asserta(quad(I,V)).

quad(X,Y,V) :-
	!,I is X * 8 + Y,
	quad(I,V).

%%
put_sec(X,Y,O) :- 
%	print(' put_sec:1=' + X + Y),
	retract(sec(X,Y,_)),
%	print(' put_sec:2=' + X + Y),
	!,asserta(sec(X,Y,O)).
put_sec(X,Y,O) :- 
	!,asserta(sec(X,Y,O)).

%%
put_ep(XX,YY) :- 
	X is floor(XX + 0.5),
	Y is floor(YY + 0.5),
	!,put_sec(X,Y,e),
	put_vdb(ex,X),put_vdb(ey,Y).

%%

%%
trek :-
	!,
	dispTitle,
	trek0.

trek0 :-
	!,
	%defRand,
	init,
	galaxy,
	trek00.

trek00 :-
	true,
	dispMission,
	acceptp,
	!,enterQuad,
	trek1.
trek00 :- !,trek0.

trek1 :-
	catch(mainLoop,Result, doFinal(Result)).

%trek :-
%	!,print('End.'),nl.

acceptp :-
	!,read(A),
	A == y.
%%
mainLoop :-
	!,nl,write('Command?'),
	read(COM),
	doCom(COM),
	energySuccessCheck,
	kattack,
	mainLoop.

%
energySuccessCheck :-
	vdb(ktotal,0),
	!,throw(success).

energySuccessCheck :-
	vdb(shield,S),
	vdb(energy,E),
	10 >= S + E,
	!,throw(energy0).

energySuccessCheck :-
	damage(shield,D),
	vdb(energy,E),
	D < 0,
	10 >= E,
	!,throw(energy0).

energySuccessCheck :- !.
%%

kattack :-
	vdb(kattack,1),
	!,krandmove,
	kla.
kattack :- !.


doCom(p) :- !,phaser.
doCom(t) :- !,torpedo.
doCom(l) :- !,lrs.
doCom(s) :- !,srs.
doCom(z) :- !,shield.
doCom(w) :- !,nav.
doCom(r) :- !,damageReport.
doCom(c) :- !,computer.
%
doCom(g) :- !,gmap.
doCom(cr) :- !,compStatReport.
doCom(tk) :- !,compTorpedo.
doCom(nb) :- !,baseNav.
%
% for Debug
doCom(kll) :- !,kll.
doCom(gal) :- !,gal.
doCom(srs) :- !,srs1(0).
doCom(repo) :- !,showStatRepair.
doCom(ttl) :- !,dispTitle.
doCom(call) :- !,myCall.
%%doCom(xx) :- !,retractall(sec(_,_,_)).
%
doCom(_) :- !,
	write('ENTER ONE OF THE FOLLOWING:'),nl,
	write('--------------------------'),nl,
	write('  w  (WARP)'),nl,
	write('  s  (FOR SHORT RANGE SENSOR SCAN)'),nl,
	write('  l  (FOR LONG RANGE SENSOR SCAN)'),nl,
	write('  p  (TO FIRE PHASERS)'),nl,
	write('  t  (TO FIRE PHOTON TORPEDOES)'),nl,
	write('  z  (TO RAISE OR LOWER SHIELDS)'),nl,
	write('  r  (FOR DAMAGE CONTROL REPORTS)'),nl,
	write('  c  (TO CALL ON LIBRARY-COMPUTER)'),nl,

	write(' ---- debug --'),nl,
	write('  g   (Galactic record)'),nl,
	write('  cr  (Computer Stat Report)'),nl,
	write('  tk  (torpedo course)'),nl,
	write('  nb  (base navigation)'),nl,
	write('  kll (Klingon List)'),nl,
	write('  gal (Galaxy Map)'),nl,
	write('  srs (srs)'),nl,
	write('  repo(Damage report)'),nl,
	write('  title()'),nl,
	write('  call(invoke clause as a goal)'),nl,
%    write('  XXX  (TO RESIGN YOUR COMMAND)'),nl,
	write('  (zzz  break for debug)'),nl.

%
myCall :-
	!,print('call:'),
	read(X),
	myCallx(X).
myCallx(X) :-
	call(X).
myCallx(X) :- !.

%%%
abo0 :-
	!,retractall(quad(_,_)),
	retractall(vdb(_,_)),
	retractall(damage(_,_)),
	retractall(sec(_,_,_)).

%
init :-
	!,abo0,
	init0.
%
init0 :-
	!,
	irandom(Rmn1,5),Rmn is Rmn1/10,
	put_vdb(damageRepairMagicNumber,Rmn),
	%
	irandom(Rt,20),
	T is floor(Rt + 20.0)*100,
	put_vdb(time0,T),   % initial time
	put_vdb(time,T),    % current time
	%
	irandom(Rtp,10),
	Tp is 25 + floor(Rtp + 0.0),
	put_vdb(timePeriod,Tp),
	%
	clrDamage,
	put_vdb(ex,0),
	put_vdb(ey,0),
	put_vdb(e-destroyed, nil),
	put_vdb(ktotal0,0),  %Klingon Initial#
	put_vdb(ktotal,0),
	put_vdb(basetotal,0),
	put_vdb(qx,0),
	put_vdb(qy,0),
	put_vdb(energy,3000),
	put_vdb(torpedo,10),
	put_vdb(condi,green),
	put_vdb(shield,0),
	put_vdb(docked,nil),
	put_vdb(kattack,0),
	put_vdb(bx,0),
	put_vdb(by,0),
	put_vdb(c-star,0),
	put_vdb(c-base,0),
	put_vdb(c-klingon,0).


%%%% Galaxy
galaxy :-
	!,galax(0),
	vdb(ktotal,K),
	put_vdb(ktotal0,K).

galax(64).
galax(I) :-
	!,galq(I),
	II is I + 1,
	galax(II).

galq(I) :-
	!,galk(K),
	galb(B),
	gals(S),
%	print(' gal1 I K B S'+[I,K,B,S]),
        inc(ktotal,K),
	inc(basetotal,B),
	put_qi(I,(S,B,K,nil)).

% Star Q
gals(S) :-
	!,irandom(RRR,8),S is RRR + 1.

% Base Q
galb(B) :-
	irandom(R,100),
	R > 96,
	!, B is 1.
galb(B) :-
	!,B is 0.

% klingon  Q

galk(K) :-
	!,irandom(R,100),
	galk1(R,K)
%	print('galk R K'+[R,K])
        .

galk1(R,K) :-
	R > 98,
	!,K is 3.
galk1(R,K) :-
	R > 95,
	!,K is 2.
galk1(R,K) :-
	R > 8,
	!,K is 1.
galk1(_,K) :-
	!,K is 0.




%%Quadrant
enterQuad :-
	!,vdb(qx,X),
	vdb(qy,Y),
	enterQuad(X,Y).
enterQuad(X,Y) :-
	!,
	nl,write('NOW ENTERING QUADRANT '),
	write(X),
	write(','),
	write(Y),
	write(' . . .'),
	put_vdb(qx,X),
	put_vdb(qy,Y),
	quad(X,Y,(S,B,K,_)),
	put_vdb(c-star,S),
	put_vdb(c-klingon,K),
	put_vdb(c-base,B),
	put_q(X,Y,(S,B,K,t)),
	newq.

%%
%%
newq :-
	!,newquad0,
	vdb(ex,X),vdb(ey,Y),
	put_ep(X,Y),
	nl,write('SECTOR AT '),
	write(X),write(','),write(Y),
	newKlingon,
	newBase,
	vdb(c-star, NS),
	newStars(NS).

newquad0 :-
	!,retractall(sec(_,_,_)),
%	print(' newquad0 '),
	newquad1(0).

%
newquad1(8) :-!.
newquad1(I) :-
	!,newquad2(I,0),
	II is I + 1,
	newquad1(II).

newquad2(_,8) :-!.
newquad2(I,J) :-
	!,
%	print(' newquad2=' + I + J),
	asserta(sec(I,J,-)),
%	print(' newquadNIL=' + I + J),
	JJ is J + 1,
	newquad2(I,JJ).


%
newKlingon :-
	!,retractall(kl(_,_,_,_)),
	vdb(c-klingon, N),
	newKl(N).
%
newKl(0) :-!.
newKl(N) :-
	!,
%print(' newKl '),
	NN is N - 1,
	newObj(k, X,Y),
	irandom(RRR,10),
	E is 200 * (RRR + 5) * 0.1,
%	print('Kl=' + NN + X + Y + E),
	asserta(kl(NN,X,Y,E)),
	newKl(NN).



%%
newStars(0) :-!.
newStars(N) :-
	!,
%	print(' newStars '),
	newObj('*',_,_),
	NN is N - 1,
	newStars(NN).
%
newObj(O,X,Y) :-
	irandom(X,8),irandom(Y,8),
%	print(' tryObj=' + X + Y),
	sec(X,Y,-),
	!,
%	print(' obj=' + O + X + Y),
	put_sec(X,Y,O).

newObj(O,X,Y) :-
	!,newObj(O,X,Y).

%%
newBase :-
%	print(' newBase '),
	vdb(c-base,0),!.

newBase :-
	!,newObj(b,X,Y),
	put_vdb(bx,X),
	put_vdb(by,Y).



%%%
shield :-
	damage(shield,D),
	(D >= 0 ->
	    shield1;
	    write('SHIELD CONTROL INOPERABLE.'),nl).

shield1 :-
	vdb(energy, E),
	vdb(shield, S),
	EE is S + E,
	write('ENERGY AVAILABLE ='),
	write(EE),
	write('.  NUMBER OF UNITS TO SHIELDS ?'),
	read(X),
	!,shi1(X,S,E).

shi1(X,_,_) :-
	X < 0,
	!,write('<SHIELDS UNCHANGED>'),nl.
shi1(X,S,E) :-
	X > S + E,
	!,write('SHIELD CONTROL:  "THIS IS NOT THE FEDERATION TREASURY."'),
	write('<SHIELDS UNCHANGED>').
shi1(X,S,E) :-
	!,EE is S + E - X,
	put_vdb(shield,X),
	put_vdb(energy,EE),
	write('DEFLECTOR CONTROL ROOM:'),
	write('  \"SHIELDS NOW AT '),
	write(X),
	write(' UNITS PER YOUR COMMAND.\"'),nl.




%% Long range sensor
lrs :-
	damage(lrs,D),
	(D >= 0 ->
	    lrs1(-1);
	    write('LONG RANGE SENSORS ARE INOPERABLE.'),nl).


lrs1(2).
lrs1(I) :-
	!,nl,
	lrs11(I,-1),
	II is I + 1,
	lrs1(II).

lrs11(_,2).
lrs11(I,J) :-
	vdb(qx,X),vdb(qy,Y),
	XX is X + I, YY is Y + J,
	XX >= 0,
	XX =< 7,
	YY >= 0,
	YY =< 7,
	!,quad(XX,YY,(S,B,K,_)),
	write(S),write(B),write(K),write(' '),
        put_q(XX,YY,(S,B,K,t)),
	JJ is J + 1,
	lrs11(I,JJ).
lrs11(I,J) :-
	!,write('--- '),
	JJ is J + 1,
	lrs11(I,JJ).



%%% Short range sensor
srs :-
	damage(srs,D),
	(D >= 0 ->
	    condUpdate,srs1(0);
	    write('*** SHORT RANGE SENSORS ARE OUT ***'),nl).


srs1(8) :-!.
srs1(I) :-
	!,nl,write(I),write('|'),
	srs11(I,0),
	srsinfo(I),
	II is I + 1,
	srs1(II).

srs11(_,8) :-!.
srs11(I,J) :-
	!,sec(I,J,O),
	write(O),write(' '),
	JJ is J + 1,
	srs11(I,JJ).

%
srsinfo(0) :-
	!,vdb(time,T),
	Ti is floor(T * 10.0)/10,
	write('        STARDATE           '),
	write( Ti ).

srsinfo(1) :-
	!,vdb(condi,X),
	write('        CONDITION          '),
	write(X).

srsinfo(2) :-
	!,vdb(qx,X),vdb(qy,Y),
	write('        QUADRANT           '),
	write(X),write(','),write(Y).

srsinfo(3) :-
	!,vdb(ex,X),vdb(ey,Y),
	write('        SECTOR             '),
	write(X),write(','),write(Y).

srsinfo(4) :-
	!,vdb(torpedo,X),
	write('        PHOTON TORPEDOES   '),
	write(X).

srsinfo(5) :-
	!,vdb(energy, E),
        vdb(shield,S),
	EE is E + S,
	write('        TOTAL ENERGY       '),
	write(EE).

srsinfo(6) :-
	!,vdb(shield,S),
	write('        SHIELDS            '),
	write(S).

srsinfo(7) :-
	!,vdb(ktotal, K),
	write('        KLINGONS REMAINING '),
	write(K).

srsinfo :-
	srsinfo(_),
	nl,
	fail.


%%% Phaser
phaser :-
	damage(phaser,D),
	(D >= 0 ->
	    phaser0;
	    write('PHASERS INOPERATIVE.'),nl).

phaser0 :-
	vdb(c-klingon,N),
	(N =\= 0 ->
	    phaser1;
	    noenemy).

phaser1 :-
	damage(comp,D),
	(D >= 0 ->
	    write('PHASERS LOCKED ON TARGET;  '),
	    phaser3;
	    write('COMPUTER FAILURE HAMPERS ACCURACY.'),nl,
	    phaser3).

phaser3 :-
	vdb(energy, E),
	write('ENERGY AVAILABLE = '),
	write(E),
	write(' UNITS'),nl,
	write('NUMBER OF UNITS TO FIRE ?'),
	read(P),
	(P =< E ->
	    phaser31(P);
	    true).

phaser31(P) :-
	(P > 0 ->
	    phaser4(P);
	    true).

phaser4(P) :-
	!,
	dec(energy, P),
	put_vdb(kattack,1),
	vdb(c-klingon,N),
	phaserLock(P,PP),
	H1 is PP /N ,
	pha6(H1).

phaserLock(P,PP) :-
	damage(comp,D),
	(D >= 0 ->
	    PP is P;
	    irandom(PP,P)).

pha6(P) :-	
	kl(KK,_,_,_),
	pha7(KK,P),
	fail.
pha6(_) :- !.


pha7(K,P) :-
	!,kl(K,_,_,E),
%	print(' pha7 kl=' + K + E ),
	kdistance(K, D),
	irandom(RRR,10),
	H is (P / D) * (2 + RRR/10),
%	print(' pha7 H='+ H + 'D=' + D + 'P=' +P),
	pha71(K,H).


kdistance(K,D) :-
	!,kl(K,Kx,Ky,_),
	vdb(ex,Ex),vdb(ey,Ey),
	Dx is Ex - Kx,
	Dy is Ey - Ky,
	D is sqrt(Dx * Dx + Dy * Dy)
%	print(' kdis Ex Kx Ey Ky'+ [D, Ex, Kx, Ey, Ky]),nl
	.

pha71(K,H) :-
	kl(K,Kx,Ky,Ke),
	H =< Ke * 0.15,
	!,write('SENSORS SHOW NO DAMAGE TO ENEMY AT '),
	write(Kx),write(','),write(Ky),write('.'),nl.


pha71(K,H) :-
	!,kl(K,Kx,Ky,Ke),
	pha711(H,K,Kx,Ky,Ke).

pha711(H,K,Kx,Ky,Ke) :-
	!,Kee is Ke - H,
	retract(kl(K,_,_,_)),
	asserta(kl(K,Kx,Ky,Kee)),
	write(' '),write(H),write(' UNIT HIT ON KLINGON AT SECTOR '),
	write(Kx),write(','),write(Ky),write('.'),nl,
        pha72(K,Kee).

pha72(K, Kee) :-
	Kee =< 0,
	!,kdelete(K).

pha72(_, Kee) :-
	!,
	write(' (SENSORS SHOW '),
	write(Kee),
	write('  UNITS REMAINING)'),nl.



%%
kdelete(K) :-
	!,write('*** KLINGON DESTROYED ***'),nl,
	dec(ktotal),
	dec(c-klingon),
	vdb(c-klingon,Knn),
	vdb(qx,QX),vdb(qy,QY),
	quad(QX,QY,(S,B,_,F)),
        put_q(QX,QY,(S,B,Knn,F)),
	kl(K,X,Y,_),
	put_sec(X,Y,-),
	retract(kl(K,_,_,_)).

kdelete(X,Y) :-
	!,kl(K,X,Y,_),
	kdelete(K).

	


%%% Klingon Attack
kla :-
	put_vdb(kattack,0),
	vdb(c-klingon,N),
	N =\= 0,
	!,kla1.
kla :- !.

kla1 :-
	write('--- KLINGON Attack --'),nl,
	vdb(docked,t),
	!,
	write('STARBASE SHIELDS PROTECT THE ENTERPRISE.'),nl.
kla1 :-
	!,kla2.

kla2 :-
	kl(K, Kx, Ky, Ke),
	kla3(K, Kx, Ky, Ke),
	fail.
kla2 :- !.

kla3(K, Kx, Ky, Ke) :-
	!,vdb(energy, E),
	E > 0,
        vdb(e-destroyed,nil),
	kdistance(K,D),
	irandom(RR,10),
	H is (Ke / D) * (2 + (RR / 10)),
%	print(' K H D Ke Kx Ky'+ [K, H, D, Ke, Kx, Ky]),nl,
	dec(shield, H),
	vdb(shield, SS),
	irandom(RRR,10),
	Kee is  (Ke / (3 + (RRR / 10))),
	retract(kl(K,_,_,_)),
	asserta(kl(K,Kx,Ky,Kee)),
	write(H),
	write(' UNIT HIT ON ENTERPRISE FROM SECTOR '),
	write(Kx),write(','),write(Ky),write(' .'),nl,
	kla4(H,SS).

kla4(H,S) :-
	S > 0,
	!,write('      <SHIELDS DOWN TO '),
	write(S),
	write(' UNITS>'),nl,
	makeDamage(H,S).
kla4(_,_) :-
	!,enterpriseDestroyed.

%

enterpriseDestroyed :-
	!,put_vdb(e-destroyed, t),
	throw(destroyed).



%
makeDamage(H,S) :-
	H >= 20,
	irandom(R,10),
	R =< 6,
	0.02 < H / S,
	!,
	irandom(Rrr,50),
	Dam is -1 *((H / S) + (Rrr / 100)),
	%
	irandom(RD,8),
	devices(Dev),
	znth(Dev,RD,(Damdev,Name)),
	damage(Damdev,DamO),
	DamNew is DamO + Dam,
	put_damage(Damdev,DamNew),
	%
	write('DAMAGE CONTROL: " '),
	write(Name),
	write(' DAMAGED BY THE HIT"'),
%	print([Dam,DamO,DamNew]),
	nl.

%%%
repairByWarp :-
	!,
%	print(' repairByWarp '),
	devices(X),
	map(repair1dev,X).

repair1dev((X,Name)) :-
	damage(X,D),
%	print(' repair1dev '+[X,D]),
	D < 0,
	!,DD is D + 1,
%	print(' Inc'+ D),
	put_damage(X,DD),
	repair1dev1(X,Name,DD).
repair1dev(_) :-!.

repair1dev1(X,Name,DD) :-
	DD >= 0,
	!,put_damage(X,0),
	write(Name),
	write(' REPAIR COMPLETED.'),
	nl.
repair1dev1(_,_,_) :-!.




%%%
dockedrepair :-
	vdb(docked,nil),
	!.
	
dockedrepair :-
	!,
% print(' dockedRepair '),
	devices(X),
	mapsum(damagep,X,Sum),
%	print('Sum='+ Sum),
	(Sum > 0 ->
	    needRepair(Sum);
	    true).


damagep((X,_),R) :-
	!,damage(X,D),
	(D < 0 ->
	    R is 0.1;
	    R is 0).

needRepair(D3) :-
	!,
	vdb(damageRepairMagicNumber,MN),
	D33 is D3 + MN,
	(D33 >= 1 ->
	    D333 is 0.9;
	    D333 is D33),
	write('TECHNICIANS STANDING BY TO EFFECT REPAIRS TO YOUR SHIP;'),nl,
	write('ESTIMATED TIME TO REPAIR: '),
	Days is floor(D333*100.0)* 0.01,
	write(Days),
	write(' STARDATES.'),nl,
	write('WILL YOU AUTHORIZE THE REPAIR ORDER (Y/N)'),
	read(A),
	(A == y ->
	    clrDamage,
	    T is D333 + 0.1,
	    incTime(T),
	    showStatRepair;
	    true).
	
	


%%
damageByWarp :-
%	print('damageByWarp'),
	irandom(R,10),
	R =< 2,
	!,irandom(RD,8),
	devices(Dev),
	znth(Dev,RD,(Damdev,Name)),
	damage(Damdev,DamO),
	write('DAMAGE CONTROL REPORT:  '),
	write(Name),
	damageByWarp1(Damdev,DamO).
damageByWarp :-!.

damageByWarp1(Damdev,DamO) :-
	irandom(R,10),
	R =< 6,
	!,irandom(Rr,500),
	write(' DAMAGED'),nl,
	DamNew is DamO  - (1 + (Rr /100)),
	put_damage(Damdev,DamNew).

damageByWarp1(Damdev,DamO) :-
	!,irandom(Rr,300),
	write(' STATE OF REPAIR IMPROVED'),nl,
	DamNew is DamO + (1 + (Rr /100)),
	(DamNew > 0 -> DamNN is 0 ; DamNN is DamNew),
	put_damage(Damdev,DamNN).
	



%%
%damage-report
damageReport :-
	!,damrepo1,
	dockedrepair.

damrepo1 :-
	damage(damcon, D),
	(D >= 0 ->
	    showStatRepair;
	    write('DAMAGE CONTROL REPORT NOT AVAILABLE.'),nl).

showStatRepair :-
	write('DEVICE             STATE OF REPAIR'),nl,
	write('------             ---------------'),nl,
	dispdamage.

%	     (* (floor->exact (* 100 (vector-ref *ddd* (1+ i)))) 0.1)))))

dispdamage :-
	!,devices(X),
	map(disp1damage,X).

disp1damage((X,Name)) :-
	!,damage(X,D),
	DD is floor(D * 100.0) * -0.1,
	write(Name),
	write('  '),
	write(DD),nl.

%
map(_,[]) :-!.
map(F,L) :-
	!,select(A,L,LR),
%	print(' map '+(F,A)),
	X =.. [F,A],
%	print(' map '+X),
	call(X),
	map(F,LR).

%%
mapsum(F,L,Sum) :-!,mapsum0(F,L,0,Sum).

mapsum0(_,[],S,SS) :-!, SS is S.
mapsum0(F,L,S,SS) :-
	!,select(A,L,LR),
	X =.. [F,A,R],
%	print(' mapsum '+X),
	call(X),
%	print(' mapsumR '+X),
	S1 is S + R,
	mapsum0(F,LR,S1,SS).
%


%
clrDamage :-
	!,devices(X),
	map(clrDamage1,X).

clrDamage1((X,_)) :-
	!,put_damage(X,0).

%
devices(
 [
 (warp,
 'WARP ENGINES'),
 (srs,
 'SHORT RANGE SENSORS'),
 (lrs,
 'LONG RANGE SENSORS'),
 (phaser,
 'PHASER CONTROL'),
 (torpedo,
 'PHOTON TUBES'),
 (damcon,
 'DAMAGE CONTROL'),
 (shield,
 'SHIELD CONTROL'),
 (comp,
 'LIBRARY-COMPUTER')
]).

%%%
compStatReport :-
	!,
	write('   STATUS REPORT:'),nl,
	write('   -------------'),nl,
	vdb(ktotal,Kt),
	write(Kt),
	write(' KLINGON(s) LEFT. /'),
	vdb(ktotal0,Kt0),
	write(Kt0),
	write(' KLINGONS at opening.'),	nl,
	%
	vdb(time0,T0),
	vdb(time,T),
	vdb(timePeriod,Tp),
	TT is floor((T0 + Tp - T)/ 10.0) * 10,
	write(' MISSION MUST BE COMPLETED IN '),
	write(TT),
	write(' STARDATES.'),nl,
	%
	baseStat,
	damageReport.

baseStat :-
	vdb(basetotal,B),
	B > 0,
	!,
	write(' THE FEDERATION IS MAINTAINING '),
	write(B),
	write(' STARBASE(s) IN THE GALAXY.'),nl,nl.
baseStat :-
	!,write('YOUR STUPIDITY HAS LEFT YOU ON YOUR OWN IN THE GALAXY'),nl,
	write('-- YOU HAVE NO STARBASES LEFT!'),nl,nl.



%    comp
%%%

condUpdate :-
	vdb(docked,t),!.
condUpdate :-
	vdb(c-klingon,N),
	N =\= 0,
	!,put_vdb(condi,red).
condUpdate :-
	vdb(energy, E),
	E < 300,
	!,put_vdb(condi,yellow).
condUpdate :-
	!,put_vdb(condi,green).



dockedp :-
	vdb(ex,X),vdb(ey,Y),
	dckp(X,Y),
	!,put_vdb(docked,t),
	put_vdb(condi,docked),
	put_vdb(energy,3000),
	put_vdb(torpedo,10),
	put_vdb(shield,0),
	write('SHIELDS DROPPED FOR DOCKING PURPOSES.'),nl.
dockedp :-
	!,put_vdb(docked,nil).


dckp(X,Y) :-
	XX is X - 1,YY is Y - 1,
	sec(XX,YY,b),!.
dckp(X,Y) :-
	XX is X,YY is Y - 1,
	sec(XX,YY,b),!.
dckp(X,Y) :-
	XX is X + 1,YY is Y - 1,
	sec(XX,YY,b),!.

dckp(X,Y) :-
	XX is X - 1,YY is Y,
	sec(XX,YY,b),!.
%dckp(X,Y) :-
%	XX is X,YY is Y,
%	sec(XX,YY,b),!.
dckp(X,Y) :-
	XX is X + 1,YY is Y,
	sec(XX,YY,b),!.

dckp(X,Y) :-
	XX is X - 1,YY is Y + 1,
	sec(XX,YY,b),!.
dckp(X,Y) :-
	XX is X,YY is Y + 1,
	sec(XX,YY,b),!.
dckp(X,Y) :-
	XX is X + 1,YY is Y + 1,
	sec(XX,YY,b),!.



%% Warp

nav :-
	nav0.
nav :- !.

nav0 :-
	!,inputCourse('LT. SULU' , C1),
	inputFactor(W1),
	navEnergy(W1, N),
	nav1(C1,N,W1).


nav1(C1,N,W1) :-
	number(N),
	!,
%	print(' C1 W1 N '+ [C1, W1, N]),
	kla,
	repairByWarp,
	damageByWarp,
	nav4(C1, N),
	navDecNenergy(N),
	warpTime(W1),
	dockedp,
	condUpdate.

nav1(_,_,_) :- !.

% %%%exitQuad -> 1, %%%
warpTime(W1) :-
	(W1 < 1 ->
	    T8 is floor(W1 * 10.0) * 0.1;
	    T8 is 1),
	incTime(T8).
%

%
nav4(C, N) :-
	!,nav5(C, N).

nav4(_,_) :- !.


navDecNenergy(N) :-
	!,X is N * 10,
	dec(energy,X),
	vdb(energy,E),
	navDecNenergy1(E).

navDecNenergy1(E) :-
	E >= 0,
	!.

navDecNenergy1(E) :-
	write('SHIELD CONTROL SUPPLIES ENERGY TO COMPLETE THE MANEUVER.'),nl,
	inc(shield,E),
	put_vdb(energy,0),
	vdb(shield,S),
	(S < 0 ->
	    put_vdb(shield,0);
	    true).




nav5(C, N) :-
	!,vdb(ex,Ex),vdb(ey,Ey),
	calVec(x,C, Dx),
	calVec(y,C, Dy),
%	print(' Ex Ey Dx Dy '+[Ex,Ey,Dx,Dy]),
	put_sec(Ex,Ey,-),
	nav51loop(Ex,Ey,Dx,Dy,N).

nav51loop(Ex,Ey,_,_,0) :-
	!,put_ep(Ex,Ey).
nav51loop(Ex,Ey,Dx,Dy,N) :-
	!,Exx is Ex + Dx,
	Eyy is Ey + Dy,
	nav52(Exx,Eyy,Dx,Dy,N).

nav52(Exx,Eyy,Dx,Dy,N) :-
	Exx >= 0,
	Exx =< 7,
	Eyy >= 0,
	Eyy =< 7,
	!,nav53(Exx,Eyy,Dx,Dy,N).

nav52(Exx,Eyy,Dx,Dy,N) :-
	!,exitQuad(Exx,Eyy,Dx,Dy,N).

nav53(Exx,Eyy,Dx,Dy,N) :-
	Exxx is floor(Exx + 0.5),
	Eyyy is floor(Eyy + 0.5),
	sec(Exxx,Eyyy,-),
	!,NN is N - 1,
	write(' ('),write(Exxx),write(','),write(Eyyy),write(')'),
	nav51loop(Exx,Eyy,Dx,Dy,NN).

nav53(Exx,Eyy,Dx,Dy,_) :-
        !,Ex is Exx - Dx,
        Ey is Eyy - Dy,
	nl,write('WARP ENGINES SHUT DOWN AT SECTOR '),
	write(Ex),
	write(','),
	write(Ey),
	write('.  DUE TO BAD NAVAGATION'),nl,
	put_ep(Ex,Ey).
	
%%
exitQuad(X,Y,Dx,Dy,N) :-
	!,exq1(qx,X,Dx,N,Qx,Sx),
%	print(' exq1(qx)'+ (Qx,Sx)),
	exq1(qy,Y,Dy,N,Qy,Sy),
%	print(' exq1(qy)'+ (Qy,Sy)),
        put_vdb(ex,Sx),
        put_vdb(ey,Sy),
	exitQ1(Qx,Qy,Sx,Sy).

exitQ1(Qx,Qy,Sx,Sy) :-
	vdb(qx,Qox),
	vdb(qy,Qoy),
	Qox =:= Qx,
	Qoy =:= Qy,
	!,write('LT. UHURA: MESSAGE FROM STARFLEET COMMAND --'),nl,
	write('  "PERMISSION TO ATTEMPT CROSSING OF GALACTIC PERIMETER'),nl,
	write('  IS HEREBY *DENIED*.  SHUT DOWN YOUR ENGINES."'),nl,
	write('CHIEF ENGINEER SCOTT:  "WARP ENGINES SHUT DOWN'),nl,
	write('  AT SECTOR '),
	write(Sx),write(','),write(Sy),
	write(' OF QUADRANT '),
	write(Qx),write(','),write(Qy),write('.'),nl,
	put_ep(Sx,Sy).

exitQ1(Qx,Qy,_,_) :-
	!,enterQuad(Qx,Qy).



exq1(A,T,D,N, Qqq,Sss) :-
	!,vdb(A, Q),
	TT is Q * 8 + (N * D) + T,
	QQ is floor(TT / 8.0),
	SS is floor(TT - (QQ * 8.0) + 0.5),
	exq2(QQ,SS,Qqq,Sss).

exq2(QQ,_,Qqq,Sss) :-
	QQ < 0,
	!,Qqq is 0,
	Sss is 0.
exq2(QQ,_,Qqq,Sss) :-
	QQ > 7,
	!,Qqq is 7,
	Sss is 7.
exq2(QQ,SS,Qqq,Sss) :-
	!,Qqq is QQ,
	Sss is SS.
	
	



%%
navEnergy(W1, N) :-
	!,NN is floor( W1 * 8.0 + 0.5),
	nave1(W1, NN, N).

nave1(_, NN, N) :-
	vdb(energy,Ee),
	Ee >= NN,
	!,N is NN.

nave1(W1, NN, N) :-
	!,write('ENGINEERING:  "INSUFFICIENT ENERGY AVAILABLE'),nl,
	write('               FOR MANEUVERING AT WARP '),
	write(W1),
	write(' !"'),nl,
	nave2(W1, NN, N).

nave2(_, NN, t) :-
	damage(shield,D),
	vdb(shield,S),
	vdb(energy,Ee),
	D >= 0,
	S > (NN - Ee),
	!,write('DEFLECTOR CONTROL ROOM:  '),
	write(S),
	write(' UNITS OF ENERGY'),nl,
	write('                          PRESENTLY DEPLOYED TO SHIELDS.').

nave2(_,_, t) :- !.




%% Torpedo
torpedo :-
	vdb(torpedo, T),
	T =< 0,
	!,write('ALL PHOTON TORPEDOES EXPENDED.'),nl.

torpedo :-
	damage(torpedo, T),
	T < 0,
	!,write('PHOTON TUBES ARE NOT OPERATIONAL.'),nl.

torpedo :-
	write('PHOTON TORPEDO '),
	inputCourse('ENSIGN CHEKOV', C),
	!,dec(energy,2),
	dec(torpedo),
	put_vdb(kattack,1),
	top1(C).
torpedo :- !.


top1(C) :-
	!,vdb(ex,Ex),vdb(ey,Ey),
	calVec(x,C, Dx),
	calVec(y,C, Dy),
%	print(' Ex Ey Dx Dy'+[Ex,Ey,Dx,Dy]),
        toploop(Ex,Ey,Dx,Dy).


toploop(Ex,Ey,Dx,Dy) :-
	!,Exx is Ex + Dx,
	Eyy is Ey + Dy,
	top3(Exx,Eyy,Dx,Dy).

top3(Exx,Eyy,Dx,Dy) :-
	Exx >= 0,
	Exx =< 7,
	Eyy >= 0,
	Eyy =< 7,
	!,top4(Exx,Eyy,Dx,Dy).

top3(_,_,_,_) :-
	!,write('\nTORPEDO MISSED.'),nl.

top4(Exx,Eyy,Dx,Dy) :-
	!,X is floor(Exx + 0.5),
	Y is floor(Eyy + 0.5),
	sec(X,Y,O),
	top5(X,Y,Exx,Eyy,Dx,Dy,O).

top5(X,Y,Exx,Eyy,Dx,Dy,-) :-
	!,write(' ('),write(X),write(','),write(Y),write(')'),
	toploop(Exx,Eyy,Dx,Dy).

top5(X,Y,_,_,_,_,'*') :-
	!,nl,write('STAR AT '),
	write(X),write(','),write(Y),
	write(' ABSORBED TORPEDO ENERGY.'),nl,
        deleteStar(X,Y).

top5(X,Y,_,_,_,_,b) :-
	!,nl,write('*** STARBASE DESTROYED AT '),
	write(X),write(','),write(Y),write(' ***'),nl,
        deleteBase(X,Y),
	destroyBase.

top5(X,Y,_,_,_,_,k) :-
	!,nl,write('HIT A Klingon AT '),
	write(X),write(','),write(Y),write('.'),nl,
        kdelete(X,Y).


deleteStar(X,Y) :-
	!,
	dec(c-star),
	vdb(c-star,SS),
	vdb(qx,QX),vdb(qy,QY),
	quad(QX,QY,(_,B,K,F)),
        put_q(QX,QY,(SS,B,K,F)),
	put_sec(X,Y,-).

deleteBase(X,Y) :-
	!,
	dec(basetotal),
	dec(c-base),
	vdb(c-base,SS),
	vdb(qx,QX),vdb(qy,QY),
	quad(QX,QY,(Star,_,K,F)),
        put_q(QX,QY,(Star,SS,K,F)),
	put_sec(X,Y,-).

%%
destroyBase :-
	!,put_vdb(docked,nil),
	put_vdb(kattack,1),
	dBase1.

dBase1 :-
	vdb(basetotal,B),
	vdb(ktotal,K),
	vdb(time,T),
	vdb(time0,T0),   % initial time
	vdb(timePeriod,Tp),
	(B =< 0,
	 K =< (T - T0 -Tp) ->
	    noBaseMessage,
	    throw(nobase);
	    write(
    'STARFLEET COMMAND REVIEWING YOUR RECORD TO CONSIDER COURT MARTIAL!')
	  ).

noBaseMessage :-
	write(
	    'THAT DOES IT, CAPTAIN!!  YOU ARE HEREBY RELIEVED OF COMMAND'),
	write(
	    ' AND SENTENCED TO 99 STARDATES AT HARD LABOR ON CYGNUS 12!!').

%   ((or (> *base-total* 0)
%	(> *klingon-total* (- *time* *time0* *t-period*)))




%
vt(x,[-1, -1, 0, 1, 1, 1, 0, -1, -1]).
vt(y,[0, 1, 1, 1, 0, -1, -1, -1, 0]).

calVec(Va,C, V) :-
	!,Ci is floor(C + 0.0),
	Cr is C - Ci,
	Cii is Ci + 1,
	vt(Va,Vt),
	znth(Vt,Ci,V1),
        znth(Vt,Cii,V2),
	V is  V1 + Cr * (V2 - V1).
%

znth([A|_],0,A) :- !.
znth([_|D],N,V) :-
	!,NN is N -1,
	znth(D,NN,V).

%
inputFactor(W) :-
	!,inpw1(W).

inpw1(W) :-
	damage(warp, D),
	(D < 0 ->
	    inpw2(W, 0.2);
	    inpw2(W, 8) ).
	
inpw2(W, X) :-
	!,
	write('WARP FACTOR (0-'),write(X),write(')?'),
	read(WW),
	inpw3(WW,W,X).

inpw3(WW,_,_) :-
	WW =< 0,
	!,fail.
inpw3(WW,W,X) :-
	WW =< X,
	!,W is WW.

inpw3(_,W,X) :-
	X < 1,
	!,write('WARP ENGINES ARE DAMAGED.  MAXIUM SPEED = WARP 0.2'),nl,
	inpw2(W, X).

inpw3(WW,W,X) :-
	!,
	write('   CHIEF ENGINEER SCOTT: "THE ENGINES WON\'T TAKE WARP '),
	write(WW),
	write('!"'),
	inpw2(W, X).


%
inputCourse(MAN, C) :-
	!,write('COURSE (0-8, -1)?'),
	read(CC),
	inpc1(MAN,CC,C).

inpc1(_,CC,_) :-
	CC =:= -1,
	!,fail.

inpc1(_,CC,C) :-
	CC >= 0,
	CC =< 8,
	!,inpc2(CC,C).

inpc1(MAN,_,C) :-
	!,
	write('   '),
	write(MAN),
	write(': "INCORRECT COURSE DATA, SIR!"'),
        inputCourse(MAN, C).

inpc2(CC,C) :-
	CC =:= 8,
	!,C is 0.

inpc2(CC,C) :-
	!,C is CC.




%%
noenemy :-
	!,write('SCIENCE OFFICER SPOCK:  "SENSORS SHOW NO ENEMY SHIPS'),nl,
	write('                         IN THIS QUADRANT"').
%%
krandmove :-
	kl(K,X,Y,E),
	krandmove1(K,X,Y,E),
        fail.
krandmove :-!.

krandmove1(K,X,Y,E) :-
	!,krandmove2(X,Y,Nx,Ny),
%	writef('kl%w\n', [kl(K,X,Y,E)]),
	write('KLINGON at '),
	write(X),write(','),write(Y),
	write(' Moves to '),
	write(Nx),write(','),write(Ny),nl,
	put_sec(X,Y,-),
	put_sec(Nx,Ny,k),
	retract(kl(K,_,_,_)),
	asserta(kl(K,Nx,Ny,E)).

krandmove2(X,Y,Nx,Ny) :-
	randmoveVec(X,Nx),
	randmoveVec(Y,Ny),
	sec(Nx,Ny,-),!.
krandmove2(X,Y,Nx,Ny) :-
	!,krandmove2(X,Y,Nx,Ny).


randmoveVec(X,XX) :-
	irandom(RRR,3),
	XX is X - (RRR - 1),
	rmv(XX),!.
randmoveVec(X,XX) :-
	!,randmoveVec(X,XX).

rmv(XX) :-
	!,XX >= 0,
	XX =< 7.

%%%
compTorpedo :-
	vdb(c-klingon,N),
	N =\= 0,
	!,compTorp1.
compTorpedo :-
	!,noenemy.

compTorp1 :-
	kl(K,X,Y,E),
	compTorp2(K,X,Y,E),
        fail.
compTorp1 :-!.

compTorp2(_,X,Y,_) :-
	!,vdb(ex,Ex),vdb(ey,Ey),
	calcP2p(Ex,Ey,X,Y,DIR),
	write('KLINGON at ('),
	write(X),
	write(','),
	write(Y),
	write('): DIRECTION = '),
	write(DIR).

calcP2p(X0,Y0,X1,Y1,Dir) :-
	!,Dx is X1 -X0,
	Dy is Y1 -Y0,
	calcp2p1(Dx,Dy,Dir).

calcp2p1(Dx,Dy,R) :-
	Dx =:= 0,Dy =:= 0,
	!,R is 0.
calcp2p1(Dx,Dy,R) :-
	Dx < 0,Dy >= 0,
	(abs(Dx) > abs(Dy)
         ->
	 calc0(0,Dx,Dy,R) ;
	 calc1(2,Dx,Dy,R) ).

calcp2p1(Dx,Dy,R) :-
	Dx >= 0, Dy >= 0,
	(abs(Dx) < abs(Dy)
         ->
	 calc1(2,Dx,Dy,R) ;
	 calc2(4,Dx,Dy,R) ).

calcp2p1(Dx,Dy,R) :-
	Dx >= 0, Dy < 0,
	(abs(Dx) > abs(Dy)
         ->
	 calc2(4,Dx,Dy,R) ;
	 calc3(6,Dx,Dy,R) ).

calcp2p1(Dx,Dy,R) :-
	Dx < 0, Dy < 0,
	(abs(Dx) < abs(Dy)
         ->
	 calc3(6,Dx,Dy,R) ;
	 calc0(8,Dx,Dy,R) ).

calc0(N,Dx,Dy,R) :-
	!,R is N - Dy /Dx.

calc1(N,Dx,Dy,R) :-
	!,R is N + Dx /Dy.

calc2(N,Dx,Dy,R) :-
	!,calc0(N,Dx,Dy,R).

calc3(N,Dx,Dy,R) :-
	!,calc1(N,Dx,Dy,R).

%%% comp base Nav.
baseNav :-
	vdb(c-base,0),
	!,write(
    'MR. SPOCK:  "SENSORS SHOW NO STARBASES IN THIS QUADRANT."'),
	nl.

baseNav :-
	!,vdb(ex,Ex),vdb(ey,Ey),vdb(bx,Bx),vdb(by,By),
	dispDirectDist(Ex,Ey,Bx,By).

dispDirectDist(X0,Y0,X1,Y1) :-
	!,calcP2p(X0,Y0,X1,Y1,Dir),
	write('DIRECTION = '),
	write(Dir),
	nl,
	Dx is X0 - X1,
	Dy is Y0 - Y1,
	dispDistance(Dx,Dy).

dispDistance(Dx,Dy) :-
	!,D is sqrt(Dx * Dx + Dy * Dy),
	write('DISTANCE = '),
	write(D),
	nl.




%%% Galaxy Record
gmap :-
	!,galmap1.
galmap1 :-
	!,
	vdb(qx,QX),vdb(qy,QY),
	write('       COMPUTER RECORD OF GALAXY FOR QUADRANT '),
	write(QX),write(','),write(QY),nl,
	write('      0   1   2   3   4   5   6   7'),nl,
	write('    +---+---+---+---+---+---+---+---+'),
	galxxx(0,t).

gal :-
	!,galxxx(0,nil).


galxxx(64,_).
galxxx(I,F) :-
	!,galxxxnl(I),
	galx2(I,F),
	II is I + 1,
	galxxx(II,F).
galx2(I,nil) :-
	!,quad(I,(S,B,K,_)),
	write(S),write(B),write(K),write(' ').
galx2(I,t) :-
	quad(I,(S,B,K,t)),
	!,write(S),write(B),write(K),write(' ').
galx2(_,t) :-
	!,write('*** ').

galxxxnl(I) :-
	R is I mod 8,
	R =:= 0,
	!,nl,
	write('  '),
	II is floor(I /8.0),
	write(II),
	write(' |').
galxxxnl(_) :- !.

%%%
incTime(Dt) :-
	inc(time,Dt),
	vdb(time,T),
	vdb(time0,T0),   % initial time
	vdb(timePeriod,Tp),
	T =< T0 + Tp,
	!.
incTime(_) :-
	!,throw(timeout).



%%%
dispTitle :-
	write('THE USS ENTERPRISE --- NCC-1701'),nl,
	write('                  ,------*------,'),nl,
	write('  ,-------------  \'-----  -----\''),nl,
	write('   \'-------- --\'      / /'),nl,
	write('       ,---\' \'-------/ /--,'),nl,
	write('        \'----------------\''),nl
    .
%%%
dispMission :-
	vdb(ktotal,Kt),
	vdb(time0,T0),
	vdb(timePeriod,Tp),
	T is  T0 + Tp,
	vdb(basetotal,B),
	(B =:= 1 ->
	    Be = 'IS ', Gobi = '' ;
	    Be = 'ARE ', Gobi = 'S' ),
	nl,nl,nl,
	write('YOUR ORDERS ARE AS FOLLOWS:'),nl,
	write('--------------------------'),nl,
	write('   DESTROY THE '),
	write(Kt),
	write(' KLINGON WARSHIPS WHICH HAVE INVADED'),nl,
	write('   THE GALAXY BEFORE THEY CAN ATTACK FEDERATION HEADQUARTERS'),nl,
	write('   ON STARDATE '),write(T),
	write('. THIS GIVES YOU '),write(Tp),write(' DAYS.'),nl,
	write(' THERE '),
	write(Be),
	write(B),
	write(' STARBASE'),
	write(Gobi),
	write(' IN THE GALAXY FOR RESUPPLYING YOUR SHIP.'),nl,
	nl,
	write('ARE YOU READY TO ACCEPT COMMAND? ("N" FOR Rebuild the Galaxy)').

%%%

doFinal(destroyed) :-
	!,
	nl,nl,
	write(' *** THE ENTERPRISE HAS BEEN DESTROYED. ***'),nl,
	write('  THE FEDERATION WILL BE CONQUERED.'),nl,
	failMission.

doFinal(timeout) :-
	!,write(' timeout '),
	failMission.

%doFinal(invaded) :-
%	!,write(' invaded ').

doFinal(nobase) :-
	!,write(' nobase '),
	failMission.

doFinal(energy0) :-
	!,
	write('** FATAL ERROR **'),nl,
	write('YOU\'VE JUST STRANDED YOUR SHIP IN SPACE.'),nl,
	write('YOU HAVE INSUFFICIENT MANEUVERING ENERGY,'),nl,
	write('AND SHIELD CONTROL IS PRESENTLY INCAPABLE OF'),nl,
	write('CROSS-CIRCUITING TO ENGINE ROOM!!'),nl,
	failMission.
	

doFinal(success) :-
	!,write(' success '),
	vdb(ktotal0,K),
	vdb(time0,T0),
	vdb(time,T),
	X is K /(T - T0),
	Rate is X * X * 1000,
	write('CONGRATULATIONS, CAPTAIN!  THE LAST KLINGON BATTLE CRUISER'),nl,
	write('MENACING THE FEDERATION HAS BEEN DESTROYED.'),nl,
	write('YOUR EFFICIENCY RATING IS '),
	write(Rate).

failMission :-
	!,vdb(time,T),
	write('IT IS STARDATE '),
	write(T),nl,
	endOfMission.

endOfMission :-
	!,vdb(ktotal,K),
	write('THERE WERE '),
	write(K),
	write(' KLINGON BATTLE CRUISERS LEFT AT'),nl,
	write('THE END OF YOUR MISSION.'),nl.
%  (set! *mission-end* #t)
%  (*game-end* #f))

%%%
computer :-
	damage(comp,D),
	(D >= 0 ->
	    computer0;
	    write('COMPUTER DISABLED.'),nl).

computer0 :-
	!,write('COMPUTER ACTIVE AND AWAITING COMMAND'),nl,
	write('Computer>'),
	read(COM),
	doComp(COM).

doComp(g) :- !,gmap.
doComp(s) :- !,compStatReport.
doComp(t) :- !,compTorpedo.
doComp(b) :- !,baseNav.

doComp(_) :-
	write('FUNCTIONS AVAILABLE FROM LIBRARY-COMPUTER:'),nl,
	write('-----------------------------------------'),nl,
	write('   g = CUMULATIVE GALTIC RECORD'),nl,
	write('   s = STATUS REPORT'),nl,
	write('   t = PHOTON TORPEDO DATA'),nl,
	write('   b = STARBASE NAV DATA'),
%	nl,
%	write('   N = DIRECTION/DISTANCE CALCULATOR'),
	nl.

%	write('   Z = GALAXY 'REGION NAME' MAP'),nl.




%%%
%%% for Debug
% set quad param
qqq :-
	!,put_vdb(c-star,3),
	put_vdb(c-klingon,2),
	put_vdb(c-base,1).
%  X is irandom(RRR,8),	Y is irandom(RRR,8),	put_ep(X,Y),
%
% List Klingons
kll :-
	kl(K,X,Y,E),
	print( kl(K,X,Y,E) ),nl,
        fail.
kll :- !.

vdb :-
	vdb(X,Y),
	print( vdb(X,Y) ),nl,
        fail.

dam :-
	damage(X,Y),
	print( damage(X,Y) ),nl,
        fail.


gald :-
	quad(I,V),
	print( quad(I,V) ),nl,
        fail.

	
%%% EOF
