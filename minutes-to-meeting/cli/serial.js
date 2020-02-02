import SerialPort from 'serialport'

const serialport = new SerialPort('/dev/cu.usbserial-1420')

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms))
}

// Number base of bytes sent. As byte is max 255, it has to be smaller.
const BASE = 200

const sendValue = async (serialport, value) => {

  // Marks start of data
  serialport.write([201])

  let sent = 0;

  for (let i = 0; i <= 10; i++) {
    const byte = (Math.floor((value - sent) % Math.pow(BASE, i + 1))) / Math.pow(BASE, i)
    sent += byte * Math.pow(BASE, i)
    serialport.write([byte])
    await sleep(100)
  }

  // Marks end of data
  serialport.write([202])
}


let initDone = false

const init = async () => {
  // This will restart the arduino board
  serialport.write([0])

  await sleep(50)

  // Wait until arduino sends something. This means it will have booted
  while (true) {
    if (serialport.read() != null) break

    await sleep(50)
  }

  initDone = true
}

export const sendValueToArduino = async (value) => {
  if (!initDone) {
    await init()
  }

  await sendValue(serialport, value)
}

