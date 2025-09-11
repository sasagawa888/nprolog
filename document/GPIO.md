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

```