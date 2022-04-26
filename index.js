var express = require("express");
var express = require("express");
var path = require("path");
var bodyParser = require("body-parser");
var app = express();
const cors = require("cors");
var http = require("http").Server(app);
var server = app.listen(5000, () => {
  //Start the server, listening on port 4000.
  console.log("Listening to requests on port 5000...");
});
var allowCrossDomain = function (req, res, next) {
  res.header("Access-Control-Allow-Origin", "*");
  res.header("Access-Control-Allow-Methods", "GET,PUT,POST,DELETE");
  res.header("Access-Control-Allow-Headers", "Content-Type");

  next();
};

app.use(allowCrossDomain);
//Testing graph
app.use(express.static(path.join(__dirname, "")));
app.use(bodyParser.urlencoded({ extended: false }));
app.get("/graph", function (req, res) {
  res.sendFile(path.join(__dirname, "/graph.html"));
});

//Main page
app.get("/", function (req, res) {
  res.sendFile(path.join(__dirname, "/index.html"));
});

const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const port = new SerialPort({
  // path: "/dev/cu.usbserial-1420", //put your serial port here
  path: "COM5",
  baudRate: 115200,
});
//post request
app.post("/", cors(), function (req, res) {
  console.log("hey");
  console.log(req.body);
  let temp_min = req.body.temperature_input_min;
  let light_min = req.body.light_input_min;
  let soil_min = req.body.soil_input_min;
  let temp_max = req.body.temperature_input_max;
  let light_max = req.body.light_input_max;
  let soil_max = req.body.soil_input_max;
  port.write(
    temp_min +
      " " +
      temp_max +
      " " +
      light_min +
      " " +
      light_max +
      " " +
      soil_min +
      " " +
      soil_max +
      " ",
    (err) => {
      if (err) {
        return console.log("Error on write: ", err.message);
      }
      console.log("message written");
    }
  );
  res.status(204).send();
});
const io = require("socket.io")(server, {
  cors: {
    origin: "http://localhost:5000",
    methods: ["GET", "POST"],
    transports: ["websocket", "polling"],
    credentials: true,
  },
  allowEIO3: true,
}); //Bind socket.io to our express server.

app.use(express.static("public")); //Send index.html page on GET /

//Read the line only when new line comes. Buffer fooling around with speed.
const parser = port.pipe(new ReadlineParser({ delimiter: "\r\n", Buffer: 2 }));
parser.on("data", (temp, light, soil, norm_light, norm_soil, norm_temp) => {
  //Read data and print to test
  console.log(temp);
  //console.log("backend");
  var today = new Date();
  setInterval(() => {
    io.sockets.emit("temp", {
      date: today.getDate() + "-" + today.getMonth() + 1 + "-" + today.getFullYear(),
      time: today.getHours() + ":" + today.getMinutes(),
      temp: temp,
      light: light,
      soil: soil,
      norm_temp: norm_temp,
      norm_light: norm_light,
      norm_soil: norm_soil,
    }); //emit the datd i.e. {date, time, temp} to all the connected clients.
  }, 5000);
});

io.on("connection", (socket) => {
  console.log("Someone connected.");
  // let today = new Date();
  // counter = 0;
  // setInterval(() => {
  //   counter += 1;
  //   socket.emit("temp", {
  //     date: today.getDate() + "-" + today.getMonth() + 1 + "-" + today.getFullYear(),
  //     time: today.getHours() + ":" + today.getMinutes(),
  //     temp: 40 + counter,
  //     light: 55 - counter,
  //     soil: 80 - counter,
  //     norm_temp: 0.4,
  //     norm_light: 0.4,
  //     norm_soil: -0.4,
  //   }); //show a log as a new client connects, check socket is working.
  // }, 5000);
});
