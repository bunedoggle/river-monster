// Load the model file
var Boat     = require('./app/models/piData/boat');
var bodyParser = require('body-parser');
var mongoose   = require('mongoose');

//provide a sensible default for local development
mongodb_connection_string = 'mongodb://localhost/lock';
//take advantage of openshift env vars when available:
if(process.env.OPENSHIFT_MONGODB_DB_URL){
  mongodb_connection_string = process.env.OPENSHIFT_MONGODB_DB_URL + 'lock';
}

// Setup DB Location
mongoose.connect(mongodb_connection_string); // connect to our database


// Here lies most the work... rest endpoints and DB connection... should really
// seperate some of this into a controller... oh well.
module.exports = function(app) {

  app.use(bodyParser.urlencoded({ extended: true }));
  app.use(bodyParser.json());

  app.get('/', function(req, res) {
    res.json({ message: 'Welcome to the Lock.  Keep hands and feet inside the boat.' });
  });

  // This is the route used by twilio to callback when a sms is received
  // It can be called manually as well... I suppose.
  app.post('/api/smsMessage', function(req, res) {
    var boat = new Boat(); 		// create a new instance of the Boat model
    boat.phoneNumber = req.body.From;
    boat.rawMessage = req.body.Body;
    var parts = boat.rawMessage.split(",");
    boat.valid = false;
    if(parts.length == 3) {
      boat.valid = true;
      boat.boatId = parts[0];
      boat.temp = parts[1];
      boat.timestamp = parts[2];
    }

    // save the boat and check for errors
    boat.save(function(err) {
      if (err)
        res.send(err);
      res.json({ message: 'Boat created! ' + boat.phoneNumber });
    });
      console.log("DATA: " + req.body.Body);

    });

  // manually create a boat (accessed at POST http://localhost:8080/api/boats)
  // This is mostly for testing purposes
  app.post('/api/boats', function(req, res) {

      var boat = new Boat(); 		// create a new instance of the Boat model
      boat.phoneNumber = req.body.phoneNumber;
      boat.rawMessage = req.body.rawMessage;
      console.log(req.body);
      var parts = boat.rawMessage.split(",");
      boat.valid = false;
      if(parts.length == 3) {
        boat.valid = true;
        boat.boatId = parts[0];
        boat.temp = parts[1];
        boat.timestamp = parts[2];
      }

      // save the boat and check for errors
      boat.save(function(err) {
        if (err)
          res.send(err);
        res.json({ message: 'Boat created! ' + boat.phoneNumber });
      });

    });

  // get a list of boats (accessed at GET http://localhost:8080/api/boats)
  app.get('/api/boats', function(req, res) {
      Boat.find(function(err, boats) {
        if (err)
          res.send(err);

        res.json(boats);
      });
    });

  // get the boat with that id (accessed at GET http://localhost:8080/api/boats/:boat_id)
  app.get('/api/boats/:boat_id', function(req, res) {
      Boat.findById(req.params.boat_id, function(err, boat) {
        if (err)
          res.send(err);
        res.json(boat.name);
      });
    });
}
