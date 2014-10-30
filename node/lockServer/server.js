var express    = require('express'); 		// call express
var app        = express(); 				// define our app using express

// Most the logic is in here... not sure that is right... whatever
require('./routes')(app);

// Server Port... Cus we run it on OpenShift we need to determine if it's local
// or running there
var ipaddress = process.env.OPENSHIFT_NODEJS_IP || "127.0.0.1";
var port = process.env.OPENSHIFT_NODEJS_PORT || 8080;

var router = express.Router(); 				// get an instance of the express Router

// START THE SERVER
 app.listen( port, ipaddress, function() {
console.log((new Date()) + ' Server is listening on port ' + port );
  });
