var fs = require('fs');

var export_path = '/sys/class/gpio/export';

function NewGpio (id, direction, state) {
	this.number = id;
	this.path = '/sys/class/gpio/gpio' + id + '/';
	this.direction = direction;
	this.value = state;
}

function pinMode(pin, callback) {
	fs.stat(pin.path, function(err, stats) {
		if (!err) {
			callback(null, pin); // GPIO already exported, no error
		} else {
			fs.writeFile(export_path, pin.number, function(err) {
				if (err) {
					callback(err, null); // Error occurred during export
				}
				else {
					callback(null, pin); // Pin successfully exported
				}
			});
		}
		fs.writeFile(pin.path + 'direction', pin.direction, function(err) {
			if (err) callback(err, null); // Error occurred during configuration
			else callback(null, pin); // Pin successfully configured
		});
	});
}

function digitalWrite(pin, value) {
	fs.writeFile(pin.path + 'value', value, function(err) {
		if (err) throw err; // Error occurred while writing pin value
		pin.value = value; // Toggle pin value for next iteration
	});
}

module.exports = { NewGpio, digitalWrite, pinMode }
