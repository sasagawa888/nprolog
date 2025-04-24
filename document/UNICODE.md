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

```



