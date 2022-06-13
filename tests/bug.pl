ifx(Test, Then, _) :- Test, !, Then.
ifx(_ , _ , Else) :- Else.
ticket(Age, Money) :-  
 ifx(Age < 13, Money is 500, Money is 1000).


 foo(Test) :- call(Test).
 bar(Test).