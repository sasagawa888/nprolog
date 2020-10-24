setup :-
    not(flag),wiringpi_setup_gpio,assert(flag),
    pin_mode(5,output).

test(0).
test(N) :-
    digital_write(5,1),
    delay(1000),
    digital_write(5,0),
    delay(1000),
    N1 is N - 1,
    test(N1).

    