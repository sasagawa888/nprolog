# wiringPi 
On paspberry PI, N-Prolog includes builtin predicates of WiringPi. 

```
N-Prolog <==================================> C
wiringpi_spi_setup(ch speed) <===> wiringPiSPISetup (SPI_CH, SPI_SPEED)
wiringpi_setup_gpio  <===> wiringPiSetupGpio()
pin_mode(n, 'output) <====> pinMode(n, OUTPUT) or 'input -> INPUT 'pwm-output -> PWM_OUTPUT
digital_write(n, v) <===> digitalWrite(n, v)
digital_write_byte(v) <===> digitalWriteByte(value)
digital_read(pin) <===> digitalRead(pin)
delay(howlong) <===> void delay(unsigned int howLong)
delay_microseconds(howlong) <===> void delay_microseconds(unsigned int howLong)
pull_up_dn_control(pin, pud) <===> pullUpDnControl(pin,pud)
pwm_set_mode('pwm_mode_ms) <===> pwmSetMode(PWM_MODE_MS); or 'pwm_mode_bal -> PWM_MODE_BAL
pwm_set_clock(n) <===> pwmSetClock(n)
pwm_set_range(n) <===> pwmSetRange(n)
pwm_write(pin, value) <===> pwmWrite(pin , value)

timer_microseconds/1
usage:  timer_microseconds(on).   timer on
        timer_microseconds(off).  timer off
        timer_microsecons(X).     unify X elapsed time. float number ,unit seconds , valid digits microsecnods
        see tests/measure.pl
```

