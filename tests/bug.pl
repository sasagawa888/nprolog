:-  use_module(utils).
% ---- utility ----

run(Test) :-
    write(Test), write(' : '),
    ( call(Test) -> writeln(ok)
    ; writeln(fail)
    ).