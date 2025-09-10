# GPIO (libgpiod)

On Raspberry Pi, N-Prolog can access GPIO through libgpiod. If libgpiod-dev is installed, these functions are available. Otherwise they are disabled.

# Spec

```
EISL <==================================> C (libgpiod)

;; Initialize GPIO chip
gpio_init <===> gpiod_chip_open("/dev/gpiochip0")
;; Returns: YES on success, NO on failure.

;; Close GPIO chip
gpio_close <===> gpiod_chip_close(struct gpiod_chip *)
;; Returns: YES on success.

;; Set pin mode
gpio_set_mode(Pin, input | output) <===> gpiod_line_request_input/output(line, "nprolog")
;; Returns: YES on success. Raises error on failure or invalid args.

;; Write pin value
gpio_write(Pin, Value) <===> gpiod_line_set_value(line, value)
;; value: 0 or 1
;; Returns: YES on success, NO on failure.

;; Read pin value
gpio_read(Pin, Value) <===> gpiod_line_get_value(line)
;; Returns: Value 0 or 1. Raises error on failure.

;; Request event detection on pin
gpio_event_request(Pin, rising | falling | both) <===> gpiod_line_request_*_edge_events(line, "nprolog")
;; Returns: YES on success, NO on failure. Raises error on invalid args.

;; Wait for event with timeout
gpio_event_wait(Pin ,Timeout-ms) <===> gpiod_line_event_wait(line, &ts)
;; timeout-ms: integer, milliseconds
;; Returns: YES if event occurred, NO if timeout, negative on error.

;; Read last event
gpio_event_read(Pin,Event) <===> gpiod_line_event_read(line, &event)
;; Returns: Event rising or falling for the detected event.
;; Raises error if no valid event.

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
;; Note:
;;   - Pin number is checked. Using non-PWM pins will raise an error.

```

