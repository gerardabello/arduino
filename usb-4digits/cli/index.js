const SerialPort = require('serialport')

  const serialport = new SerialPort('/dev/cu.usbmodem14201')

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms))
}

const sendValue = async value => {
  const n = Math.ceil(9999 / 255)
  const nVal = Math.floor(value / n);
  const lastVal = value - (nVal * (n-1))
  const values = [0,...(Array.from(Array(n - 1).keys()).map(() => nVal)), lastVal]
  for (let i = 0; i < values.length; i++) {
  serialport.write([values[i]])
  await sleep(0)
  }
}

const main = async () => {
  serialport.write([0])

  await sleep(50)

  while (true) {
    if (serialport.read() != null) break

    await sleep(50)
  }

  await sendValue(parseInt(process.argv[2]))
}

main().then(process.exit)

