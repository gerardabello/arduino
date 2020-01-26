import {getEvents} from './google-calendar.js'
import {sendValueToArduino} from './serial.js'


const dateSecondsDiff = (date1, date2) => {
  const diff = Math.abs(date2 - date1);
  return Math.floor((diff/1000));
}

const main = async () => {
  const events = await getEvents()
  const nextEventDate = events[0].start
  const secondsToNextEvent = dateSecondsDiff(new Date(), nextEventDate)
  await sendValueToArduino(secondsToNextEvent)
}

main().then(process.exit)
