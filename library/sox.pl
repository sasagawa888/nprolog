% Sox library

:- module(sox,[sox_play/1]).
% N is -60 ~ 67 C4 is 0
sox_play(N) :-
    integer_midi(N,M),
    midi_freq(M,F),
    string_term(S,F),
    atom_string(A,S),
    atom_concat('play -n synth 0.4 sine ',A,C1),
    atom_concat(C1, ' >/dev/null 2>&1', C2),
    shell(C2).

% Midi is midi note 0~127 C4=60
midi_freq(Midi, Freq) :-
    Freq is 440 * 2 ** ((Midi - 69)/12).

% integer 0 -> midi 60
integer_midi(Integer,Midi) :-
    Midi is Integer+60.