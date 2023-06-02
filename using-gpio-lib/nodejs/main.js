var fs = require('fs');
var GPIO = require('./gpiolib');

var blink_period = 500; // in milliseconds

var gpio_154 = new GPIO.NewGpio('154', 'out', '0');

// Set the pin mode of GPIO pin
GPIO.pinMode(gpio_154, function(err, pin) {
    if (err) throw err; // Error occurred during pin export
        setInterval(function() {
	    // Blink the led by writing 1 or 0 to the pin using digitalWrite
            gpio_154.value == '0' ? GPIO.digitalWrite(gpio_154, '1') : GPIO.digitalWrite(gpio_154, '0');
        }, blink_period);
});
