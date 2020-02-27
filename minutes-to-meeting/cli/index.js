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
    try {
      events = await getEvents()
      await sleep(15 * 60 * 1000)
    }catch(e) {
      console.log('Could not fetch google calendar events: ', e)
      process.exit(1)
    }
  }
}

// Ignores meeting length. Considers to be in meeting for the first 10 minutes
const currentlyInMeeting = events => {
  const MEETING_LENGTH = 10 * 60 * 1000
  const now = new Date()
  const currentEvents = events.filter(e => 
    { 
      return e.start < now && (new Date(e.start.getTime() + MEETING_LENGTH)) > now
    }
  )

  return currentEvents.length > 0
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
  dotenv.config({ path: '../.env' })
  const serial = new Serial(process.env.PORT, e => {
    console.log('Error with device connection: ', e)
    process.exit(1)
  })

  const fail = await serial.init()

  if (fail) {
    console.error('Could not connect to device')
    return
  }

  updateEventsLoop()

  while (true) {
    if (events) {
      // if in meeting, no need to do anything as the display will be at 0
      if (!currentlyInMeeting(events)) {
        // Events is sorted by time
        const now = new Date()
        const nextEvent = events.find(e => e.start > now)
        if (nextEvent) {
          console.log(`Next event: ${nextEvent.summary}`)
          const secondsToTime = dateSecondsDiff(new Date(), nextEvent.start)
          await serial.sendValue(secondsToTime)
        }
      }else{
        console.log('Currently in meeting')
      }
      await sleep(5 * 1000)
    }

    await sleep(100)
  }
}

main().then(process.exit).catch(e => {
  console.error(e)
  process.exit()
})
