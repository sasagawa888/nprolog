% Sox library



sox_play(N,O) :-
    note(N,O,F),
    string_term(S,F),
    atom_string(A,S),
    atom_concat('play -n synth 0.4 sine ',A,C),
    shell(C).


semitone(c,  -9).
semitone(cs, -8).
semitone(d,  -7).
semitone(ds, -6).
semitone(e,  -5).
semitone(f,  -4).
semitone(fs, -3).
semitone(g,  -2).
semitone(gs, -1).
semitone(a,   0).
semitone(as,  1).
semitone(b,   2).

note(Note, Oct, Freq) :-
    semitone(Note, S),
    N is S + 12*(Oct - 4),
    Freq is 440 * 2 ** (N / 12).


    