import {getEvents} from './google-calendar.js'
import {sendValueToArduino} from './serial.js'

function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms))
}


const dateSecondsDiff = (date1, date2) => {
  const diff = Math.abs(date2 - date1);
  return Math.floor((diff/1000));
}

let events

const updateEventsLoop = async () => {
  while (true) {
  events = await getEvents()
      //await sleep(15 * 60 * 1000)
      await sleep(14 * 1000)
  }
}

let lastTimeSend
const setTimeInArduino = async time => {
  if (lastTimeSend && time.getTime() === lastTimeSend.getTime()) return
  lastTimeSend = time
  const secondsToTime = dateSecondsDiff(new Date(), time)
  await sendValueToArduino(secondsToTime)
}

// Ignores meeting length. Considers to be in meeting for the first 10 minutes
const currentlyInMeeting = events => {
  const MEETING_LENGTH = 10 * 60 * 1000
  const now = new Date()
  return events.filter(e => 
    { 
      return e.start < now && (new Date(e.end.getTime() + MEETING_LENGTH)) > now
    }
  ).length > 0
}

const hoursAgo = n => {
  const now = new Date()
  const fiveHoursAgo = new Date(now.getTime() - n * 60 * 60 * 1000)
  return fiveHoursAgo
}

const hoursFuture= n => {
  const now = new Date()
  return fiveHoursAgo
}

const main = async () => {

  updateEventsLoop()

  while (true) {
    if (events) {
      // if in meeting, no need to do anything as the display will be at 0
      if (!currentlyInMeeting(events)) {
        // Events is sorted by time
        const now = new Date()
        const nextEvent = events.find(e => e.start > now)
        if (nextEvent) {
          await setTimeInArduino(nextEvent.start)
        }
      }
      await sleep(10 * 1000)
    }

    await sleep(100)
  }
}

main().then(process.exit)
