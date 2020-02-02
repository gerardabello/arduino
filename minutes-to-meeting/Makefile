#!make
include .env
export

test:
	env
build:
	arduino-cli compile --fqbn $(FQBN) . 
upload:
	arduino-cli upload -p $(PORT) --fqbn $(FQBN) .
log:
	cat $(PORT)
loghex:
	od -x < $(PORT)


