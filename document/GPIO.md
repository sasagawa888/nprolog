# GPIO (libgpiod)

On Raspberry Pi, N-Prolog can access GPIO through libgpiod. If libgpiod-dev is installed, these functions are available. Otherwise they are disabled.

# Spec
- gpio_init/0
- gpio_close/0
- gpio_set_mode/2
- gpio_write/2
- gpio_read/2
- gpio_event_request/2
- gpio_event_wait/2
- gpio_event_read/2
- sleep/1
- usleep/1

NPL <==================================> C (libgpiod)

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

