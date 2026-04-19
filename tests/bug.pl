:-  use_module(utils).
% ---- utility ----

run(Test) :-
    write(Test), write(' : '),
    ( call(Test) -> write(ok)
    ; write(fail)
    ).