%test for east asian language
/*
N-Prolog supports Unicode characters in atoms and strings.

For left-to-right scripts (e.g., Latin, Cyrillic, Japanese),
atoms can be written without quotes.

For right-to-left scripts (e.g., Arabic),
atoms must be enclosed in quotes due to limitations in the lexer.

*/


%Tai
tai :- write(ขอบคุณ).

%tamil
tamil :- write(நன்றி).

%arabian
arabian :- write('شكرًا لك').

%russian
russian :- write(Спасибо).

%hebrew
hebrew :- write('תודה לך').
