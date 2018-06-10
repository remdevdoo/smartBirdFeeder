require('dotenv').config()

var ttn = require("ttn");
const express = require('express');
const app = express();

const appID = process.env.APPID;
const accessKey = process.env.ACCESSKEY;



// Global variable to store TTN data.
var data = null;

//Discover handler and open mqtt connection
ttn.data(appID, accessKey)
  .then(function (client) {
    client.on("uplink", function (devID, payload) {
      data = payload.payload_fields.volume;
      console.log("Received uplink from ", devID);
      console.log(data);

    })
  })

  .catch(function (error) {
    console.error("Error", error)
    process.exit(1)
  })

app.use(express.static(__dirname + '/'));


//Server webpage on /volume.
app.get('/volume', function (req, res) {

  //Parse global variable in JSON format.
  var msg = JSON.stringify({

    payload: data

  });

  //Send JSON to /volume
  res.send(msg);
  console.log("format after JSON: " + msg);

});

//Run server on port 2000
app.listen(2000);
console.log("Running at Port 2000");
console.log(process.env.appID);