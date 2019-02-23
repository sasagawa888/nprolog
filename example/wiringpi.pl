:- c_include('<wiringPi.h>').
:- c_include('<wiringPiSPI.h>').
:- c_option('-lwiringPi').

wiringpi_setup_gpio(X) :-
    c_lang('Junify(varX,Jmakeint(wiringPiSetupGpio()));').

wiringpi_spi_setup_ch_speed(X,Y,Z) :-
    c_lang('Junify(varZ,Fmakeint(wiringPiSPISetup(Jget_int(Jderef(varX)),Jget_int(Jderef(varY)))));').

pwm_set_mode(pwm_mode_ms) :-
    c_lang('pwmSetMode(PWM_MODE_MS);').
pwm_set_mode(pwm_mode_bal) :-
    c_lang('pwmSetMode(PWM_MODE_BAL);').
  
pwm_set_range(X) :-
    integer(X),
    c_lang('pwmSetRange(Jget_int(Jderef(varX)));').

pwm_set_clock(X) :-
    integer(X),
    c_lang('pwmSetClock(Jget_int(Jderef(varX)));').

pin_mode(X,input) :-
    c_lang('pinMode(Jget_int(Jderef(varX)), INPUT);').
pin_mode(X,output) :-
    c_lang('pinMode(Jget_int(Jderef(varX)), OUTPUT);').
pin_mode(X,pwm_output) :-
    c_lang('pinMode(Jget_int(Jderef(varX)), PWM_OUTPUT);').

digital_write(X,Y) :-
    integer(X),
    integer(Y),
    c_lang('digitalWrite(Jget_int(Jderef(varX)),Jget_int(Jderef(varY)));').

digital_write_byte(X) :-
    integer(X),
    c_lang('digitalWriteByte(Jget_int(Jderef(varX)));').

pwm_write(X,Y) :-
    integer(X),
    integer(Y),
    c_lang('pwmWrite(Jget_int(Jderef(varX)),Jget_int(Jderef(varY)));').

pull_up_dn_control(X,Y) :-
    integer(X),
    integer(Y),
    c_lang('pullUpDnControl(Jget_int(Jderef(varX)),Jget_int(Jderef(varY)));').
    
digital_read(X,Y) :-
    % integer(X),
    c_lang('Junify(varY,Jmakeint(digitalRead(Jget_int(Jderef(varX)))));').

delay(X) :-
    integer(X),
    c_lang('delay(Jget_int(Jderef(varX)));').

delay_microseconds(X) :-
    c_lang('delayMicroseconds(Jget_int(Jderef(varX)));').












