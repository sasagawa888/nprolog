# GPIO (pigpio)

On Raspberry Pi, N-Prolog can access GPIO using the pigpio library. If pigpio is installed and the daemon is running, these functions are available. Otherwise they are disabled.

# Spec

```
EISL <==================================> C (pigpio)

;; Initialize GPIO
gpio_init <===> gpioInitialise()
;; Returns: YES on success, NO on failure.

;; Terminate GPIO
gpio_close <===> gpioTerminate()
;; Returns: YES on success.

;; Set pin mode
gpio_set_mode(Pin, input | output) <===> gpioSetMode(Pin, PI_INPUT | PI_OUTPUT)
;; Returns: YES on success. Raises error on failure or invalid args.

;; Write pin value
gpio_write(Pin, Value) <===> gpioWrite(Pin, Value)
;; Value: 0 or 1
;; Returns: YES on success, NO on failure.

;; Read pin value
gpio_read(Pin, Value) <===> gpioRead(Pin)
;; Returns: Value 0 or 1. Raises error on failure.

;; Start hardware PWM on a servo
gpio_servo_start(Pin, Angle) <===> gpioServo(Pin, pulse_width)
;; Pin: GPIO number (must support hardware PWM)
;; Angle: 0-180 degrees
;; pulse_width: automatically converted 1000us (0°) - 2000us (180°)
;; Returns: YES on success. Raises error on invalid args.
;; Note:
;;   - Only the following GPIO pins support hardware PWM:
;;       PWM0: 12, 18
;;       PWM1: 13, 19
;;   - Pin number is checked. Using non-PWM pins will raise an error.
;;   - Angle out of range (0-180°) will raise an error.

;; Stop hardware PWM on a servo
gpio_servo_stop(Pin) <===> gpioServo(Pin, 0)
;; Pin: GPIO number
;; Stops PWM output on the given pin.
;; Returns: YES on success. Raises error on invalid args.

;; Optional delays
sleep(Seconds) <===> sleep(Seconds)
usleep(Microseconds) <===> usleep(Microseconds)
;; Provides simple blocking delays.
```