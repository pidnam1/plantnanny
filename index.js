var express = require("express");
const path = require("path");

var app = express();
var http = require("http").Server(app);
var server = app.listen(5000, () => {
  //Start the server, listening on port 4000.
  console.log("Listening to requests on port 5000...");
});

//Testing graph
app.use(express.static(path.join(__dirname, "")));
app.get("/graph", function (req, res) {
  res.sendFile(path.join(__dirname, "/graph.html"));
});

//Main page
app.get("/", function (req, res) {
  res.sendFile(path.join(__dirname, "/index.html"));
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

const { SerialPort } = require("serialport");
const { ReadlineParser } = require("@serialport/parser-readline");
const port = new SerialPort({
  path: "/dev/cu.usbserial-1420", //put your serial port here
  baudRate: 115200,
});

//Read the line only when new line comes. Buffer fooling around with speed.
const parser = port.pipe(new ReadlineParser({ delimiter: "\r\n", Buffer: 2 }));
parser.on("data", (temp) => {
  //Read data and print to test
  console.log(temp);
  //console.log("backend");
  var today = new Date();
  io.sockets.emit("temp", {
    date: today.getDate() + "-" + today.getMonth() + 1 + "-" + today.getFullYear(),
    time: today.getHours() + ":" + today.getMinutes(),
    temp: temp,
  }); //emit the datd i.e. {date, time, temp} to all the connected clients.
});

io.on("connection", (socket) => {
  console.log("Someone connected."); //show a log as a new client connects, check socket is working.
});
