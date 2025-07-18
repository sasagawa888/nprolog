% chemistry
element(hydrogen, 1, 1.008).
element(helium, 2, 4.0026022).
element(lithium, 3, 6.94).
element(beryllium, 4, 9.01218315).
element(boron, 5, 10.81).
element(carbon, 6, 12.011).
element(nitrogen, 7, 14.007).
element(oxygen, 8, 15.999).
element(fluorine, 9, 18.9984031636).
element(neon, 10, 20.17976).
element(sodium, 11, 22.989769282).
element(magnesium, 12, 24.305).
element(aluminium, 13, 26.98153857).
element(silicon, 14, 28.085).
element(phosphorus, 15, 30.9737619985).
element(sulfur, 16, 32.06).
element(chlorine, 17, 35.45).
element(argon, 18, 39.9481).
element(potassium, 19, 39.09831).
element(calcium, 20, 40.0784).
element(scandium, 21, 44.9559085).
element(titanium, 22, 47.8671).
element(vanadium, 23, 50.94151).
element(chromium, 24, 51.99616).
element(manganese, 25, 54.9380443).
element(iron, 26, 55.8452).
element(cobalt, 27, 58.9331944).
element(nickel, 28, 58.69344).
element(copper, 29, 63.5463).
element(zinc, 30, 65.382).
element(gallium, 31, 69.7231).
element(germanium, 32, 72.6308).
element(arsenic, 33, 74.9215956).
element(selenium, 34, 78.9718).
element(bromine, 35, 79.904).
element(krypton, 36, 83.7982).
element(rubidium, 37, 85.46783).
element(strontium, 38, 87.621).
element(yttrium, 39, 88.905842).
element(zirconium, 40, 91.2242).
element(niobium, 41, 92.906372).
element(molybdenum, 42, 95.951).
element(technetium, 43, 98).
element(ruthenium, 44, 101.072).
element(rhodium, 45, 102.905502).
element(palladium, 46, 106.421).
element(silver, 47, 107.86822).
element(cadmium, 48, 112.4144).
element(indium, 49, 114.8181).
element(tin, 50, 118.7107).
element(antimony, 51, 121.7601).
element(tellurium, 52, 127.603).
element(iodine, 53, 126.904473).
element(xenon, 54, 131.2936).
element(cesium, 55, 132.905451966).
element(barium, 56, 137.3277).
element(lanthanum, 57, 138.905477).
element(cerium, 58, 140.1161).
element(praseodymium, 59, 140.907662).
element(neodymium, 60, 144.2423).
element(promethium, 61, 145).
element(samarium, 62, 150.362).
element(europium, 63, 151.9641).
element(gadolinium, 64, 157.253).
element(terbium, 65, 158.925352).
element(dysprosium, 66, 162.5001).
element(holmium, 67, 164.930332).
element(erbium, 68, 167.2593).
element(thulium, 69, 168.934222).
element(ytterbium, 70, 173.0451).
element(lutetium, 71, 174.96681).
element(hafnium, 72, 178.492).
element(tantalum, 73, 180.947882).
element(tungsten, 74, 183.841).
element(rhenium, 75, 186.2071).
element(osmium, 76, 190.233).
element(iridium, 77, 192.2173).
element(platinum, 78, 195.0849).
element(gold, 79, 196.9665695).
element(mercury, 80, 200.5923).
element(thallium, 81, 204.38).
element(lead, 82, 207.21).
element(bismuth, 83, 208.980401).
element(polonium, 84, 209).
element(astatine, 85, 210).
element(radon, 86, 222).
element(francium, 87, 223).
element(radium, 88, 226).
element(actinium, 89, 227).
element(thorium, 90, 232.03774).
element(protactinium, 91, 231.035882).
element(uranium, 92, 238.028913).
element(neptunium, 93, 237).
element(plutonium, 94, 244).
element(americium, 95, 243).
element(curium, 96, 247).
element(berkelium, 97, 247).
element(californium, 98, 251).
element(einsteinium, 99, 252).
element(fermium, 100, 257).
element(mendelevium, 101, 258).
element(nobelium, 102, 259).
element(lawrencium, 103, 266).
element(rutherfordium, 104, 267).
element(dubnium, 105, 268).
element(seaborgium, 106, 269).
element(bohrium, 107, 270).
element(hassium, 108, 269).
element(meitnerium, 109, 278).
element(darmstadtium, 110, 281).
element(roentgenium, 111, 282).
element(copernicium, 112, 285).
element(nihonium, 113, 286).
element(flerovium, 114, 289).
element(moscovium, 115, 289).
element(livermorium, 116, 293).
element(tennessine, 117, 294).
element(oganesson, 118, 294).
element(ununennium, 119, 315).
element(unbinilium, 120, 320).

shell_data([2, 8, 8, 18, 18, 32 ,32]).

groupe(X,G) :-
    period(X,P),
    groupe1(X,P,G).

groupe1(X,P,G) :-
    P == 1,
    X == 1,G = 1.
grouep1(X,P,G) :-
    P == 1,
    X == 2,G = 18.
groupe1(X,P,G) :-
    P == 2,
    X =< 4,
    G is X - 2.
groupe1(X,P,G) :-
    P == 2,
    X > 4,
    G is X + 8.
groupe1(X,P,G) :-
    P == 3,
    X =< 12,
    G is X - 10.
groupe1(X,P,G) :-
    P == 3,
    X > 12,
    G is X.
groupe1(X,P,G) :-
    P == 4,
    G is X - 18.
groupe1(X,P,G) :-
    P == 5,
    G is X - 36.
groupe1(X,P,G) :-
    P == 6,
    X >= 57, X =< 71,
    G = 3.
groupe1(X,P,G) :-
    P == 6,
    X =< 56,
    G is X - 54.
groupe1(X,P,G) :-
    P == 6,
    X >= 72,
    G is X - 68.
groupe1(X,P,G) :-
    P == 7,
    X >= 89, X =< 103,
    G is 3.
groupe1(X,P,G) :-
    P == 7,
    X =< 88,
    G is X - 86.
groupe1(X,P,G) :-
    P == 7,
    X =< 104,
    G is X - 100.
groupe1(X,P,G) :-
    P == 8,
    X >= 139, X =< 153,
    G = 3.
groupe1(X,P,G) :-
    P == 8,
    X =< 120,
    G is X - 118.
groupe1(X,P,G) :-
    P == 8,
    X >= 154,
    G is X - 150.
groupe1(X,P,G) :-
    P == 9,
    X >= 171, X =< 173,
    G is 3.
groupe1(X,P,G) :-
    P == 9,
    G is X - 168.

period(X,P) :-
    shell_data(S),
    period1(X,S,1,P).
period1(X,[],_,_) :- fail.
period1(X,[S|Ss],P,P) :-
    X =< S.
period1(X,[S|Ss],Y,P) :-
    X > S,
    X1 is X - S,
    Y1 is Y + 1,
    period1(X1,Ss,Y1,P).
