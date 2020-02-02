build:
	arduino-cli compile --fqbn arduino:avr:nano:cpu=atmega328 . 
upload:
	arduino-cli upload -p /dev/cu.usbserial-1420 --fqbn arduino:avr:nano:cpu=atmega328 .
log:
	cat /dev/cu.usbserial-1420
loghex:
	od -x < /dev/cu.usbserial-1420


