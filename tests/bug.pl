

for_any(P,Q) :-
        P,
        ifthenelse(Q,fail,(!,fail)).
for_any(P,Q).
