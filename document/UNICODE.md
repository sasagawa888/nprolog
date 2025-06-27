# Unicode
N-Prolog supports UNICODE.
Internally, it uses UTF-8.

# Example

```

鳥類(X) :-
    温血(X),
    脊椎動物(X),
    羽根(X).

?- name(動物,X).
X = [21205,29289] .
yes
?- 

እንፎች(X) :-
    ሞቃት(X),
    እግርተኞች(X),
    ተንቀሳቃሽ(X).


?- char_code(あ,X).
X = 12354 .
yes
?- char_code(X,12354).
X = あ .
yes
?- 

?- atom_codes(こんにちは,X).
X = [12371,12435,12395,12385,12399] .
yes
?- atom_codes(X,[12371,12435,12395,12385,12399]).
X = こんにちは .
yes
?- 
```

