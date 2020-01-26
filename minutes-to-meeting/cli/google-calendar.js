import fs from 'fs'
import readline from 'readline'
import googleapis from 'googleapis'

const google = googleapis.google

// If modifying these scopes, delete token.json.
const SCOPES = ['https://www.googleapis.com/auth/calendar.readonly'];
// The file token.json stores the user's access and refresh tokens, and is
// created automatically when the authorization flow completes for the first
// time.
const TOKEN_PATH = 'token.json';


/**
 * Create an OAuth2 client with the given credentials, and then execute the
 * given callback function.
 * @param {Object} credentials The authorization client credentials.
 * @param {function} callback The callback to call with the authorized client.
 */
function authorize(credentials) {
  return new Promise((resolve, reject) => {
    const {client_secret, client_id, redirect_uris} = credentials.installed;
    const oAuth2Client = new google.auth.OAuth2(
      client_id, client_secret, redirect_uris[0]);

    // Check if we have previously stored a token.
    fs.readFile(TOKEN_PATH, (err, token) => {
      if (err) return getAccessToken(oAuth2Client, resolve);
      oAuth2Client.setCredentials(JSON.parse(token));
      resolve(oAuth2Client);
    });
  })
}

/**
 * Get and store new token after prompting for user authorization, and then
 * execute the given callback with the authorized OAuth2 client.
 * @param {google.auth.OAuth2} oAuth2Client The OAuth2 client to get token for.
 * @param {getEventsCallback} callback The callback for the authorized client.
 */
function getAccessToken(oAuth2Client, callback) {
  const authUrl = oAuth2Client.generateAuthUrl({
    access_type: 'offline',
    scope: SCOPES,
  });
  console.log('Authorize this app by visiting this url:', authUrl);
  const rl = readline.createInterface({
    input: process.stdin,
    output: process.stdout,
  });
  rl.question('Enter the code from that page here: ', (code) => {
    rl.close();
    oAuth2Client.getToken(code, (err, token) => {
      if (err) return console.error('Error retrieving access token', err);
      oAuth2Client.setCredentials(token);
      // Store the token to disk for later program executions
      fs.writeFile(TOKEN_PATH, JSON.stringify(token), (err) => {
        if (err) return console.error(err);
        console.log('Token stored to', TOKEN_PATH);
      });
      callback(oAuth2Client);
    });
  });
}


const getCalendars = auth => new Promise(resolve => {
  const calendar = google.calendar({version: 'v3', auth});
  console.log(calendar.calendarList)
  calendar.calendarList.list({
  }, (err, res) => {
    console.log(res.data)
  });
})

const getEventsInCalendar = (auth, calendarId) => new Promise(resolve => {
  const calendar = google.calendar({version: 'v3', auth});

  calendar.events.list({
    calendarId,
    timeMin: (new Date()).toISOString(),
    maxResults: 100,
    singleEvents: true,
    orderBy: 'startTime',
  }, (err, res) => {
    if (err) return console.log('The API returned an error: ' + err);
    const events = res.data.items;
    console.log(events)
    resolve(events.filter(e => e.status === 'confirmed')
      .filter(e => e.start.dateTime != null)
      .map(e => ({summary:e.summary, start: new Date(e.start.dateTime), end: new Date(e.end.dateTime)
      })))

  });


})

export const getEvents = async () => {
  const credentials = await fs.promises.readFile('credentials.json')
  // Authorize a client with credentials, then call the Google Calendar API.
  const auth = await authorize(JSON.parse(credentials))
  const events = [
    ...(await getEventsInCalendar(auth, 'gerard.abello@typeform.com')),
    ...(await getEventsInCalendar(auth, 'typeform.tf_o0r83elo19pfc5i0244r6en85c@group.calendar.google.com')),
  ]

  const sortedEvents = events.sort(function(a,b){
    return a.start - b.start;
  });

  return sortedEvents
}
