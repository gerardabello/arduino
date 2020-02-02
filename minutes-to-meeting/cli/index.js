import {getEvents} from './google-calendar.js'
import Serial from './serial.js'
import  dotenv from 'dotenv' 

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
      await sleep(15 * 60 * 1000)
  }
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

const main = async (serial) => {

  updateEventsLoop()

  const fail = await serial.init()

  if (fail) return

  while (true) {
    if (events) {
      // if in meeting, no need to do anything as the display will be at 0
      if (!currentlyInMeeting(events)) {
        // Events is sorted by time
        const now = new Date()
        const nextEvent = events.find(e => e.start > now)
        if (nextEvent) {
          const secondsToTime = dateSecondsDiff(new Date(), nextEvent.start)
          await serial.sendValue(secondsToTime)
        }
      }
      await sleep(5 * 1000)
    }

    await sleep(100)
  }
}

const errorWrappedMain = () => new Promise((resolve, reject) =>  {
  dotenv.config({ path: '../.env' })
    const serial = new Serial(process.env.PORT, reject)
    main(serial).then(resolve).catch(reject)
})

const index = async () => {
  while(true){
    try {
      await errorWrappedMain()
    }catch(e) {
      console.error(e)
      await sleep(1 * 1000)
    }
  }
}


index().then(process.exit).catch(e => {
  console.error(e)
  process.exit()
})
