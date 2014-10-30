DEPLOYMENT

- Install node.js and MongoDB (figure it out!)

- You must have a Twilio acccount for this application to work.
  - Sign up at Twilio and obtain a phone number

- You also need a publicly accessible server for Twilio to callback to when SMS arrives
  - see ngrok.com for a way to expose localhost externally

- Login to Twilio and redirect the callback page to http://<yourserver>/api/smsMessage


There is a version currently hosted on OpenShift.  This project has all the crap
needed to make that work (they use environment vars to figure out the right
ports and address to use.  It will work locally or on OpenShift).
