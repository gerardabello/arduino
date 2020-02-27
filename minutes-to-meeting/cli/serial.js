import SerialPort from 'serialport'

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms))
}

// Number base of bytes sent. As byte is max 255, it has to be smaller.
const BASE = 200

class Serial {
  constructor(port, onError) {
    this.serialport = new SerialPort(port)

    this.serialport.on('error', onError)
  }


  async sendValue  ( value) {
    // Marks start of data
    this.serialport.write([201])

    let sent = 0;

    for (let i = 0; i <= 10; i++) {
      const byte = (Math.floor((value - sent) % Math.pow(BASE, i + 1))) / Math.pow(BASE, i)
      sent += byte * Math.pow(BASE, i)
      this.serialport.write([byte])
      await sleep(100)
    }

    // Marks end of data
    this.serialport.write([202])
  }

  async init () {
    // This will restart the arduino board
    this.serialport.write([0])

    let i = 0

    // Wait until arduino sends something. This means it will have booted
    while (true) {
      console.log('Waiting for controller...')
      if (this.serialport.read() != null) break

      i++
      if (i > 5) return true

      await sleep(1000)
    }

    return false
  }
}



export default Serial



