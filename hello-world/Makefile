build:
	arduino-cli compile --fqbn arduino:avr:uno . 
upload:
	arduino-cli upload -p /dev/cu.usbmodem14201 --fqbn arduino:avr:uno .
log:
	cat /dev/cu.usbmodem14201
loghex:
	od -x < /dev/cu.usbmodem14201


