var mongoose     = require('mongoose');
var Schema       = mongoose.Schema;

var BoatSchema   = new Schema({
	phoneNumber: String,
	rawMessage: String,
	valid: Boolean,
	temp: Number,
	boatId: Number,
	timestamp: Number
});

module.exports = mongoose.model('Boats', BoatSchema);
