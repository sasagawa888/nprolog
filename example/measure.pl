/*
example for raspberry Pi3
use ultrasonic sensor
*/

setup :-
    wiringpi_setup_gpio(X),
    pin_mode(23,output),
    pin_mode(24,input),
    digital_write(23,0),
    delay(1000).

measure(X) :-
    digital_write(23,1),
    delay_microseconds(11),
    digital_write(23,0),
    read_wait(1),
    timer_microseconds(on),
    read_wait(0),
    timer_microseconds(off),
    timer_microseconds(T),
    X is T * 34000 /2.

read_wait(X) :-
    repeat,
    digital_read(24,Y),
    X == Y,!.
