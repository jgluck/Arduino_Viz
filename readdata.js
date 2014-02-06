////////////////////////////////////////////////////////
// Use the cool library                               //
// git://github.com/voodootikigod/node-serialport.git //
// to read the serial port where arduino is sitting.  //
////////////////////////////////////////////////////////               
var com = require("serialport"), express = require('express'), app = express()
  , server = require('http').createServer(app)
  , io = require('socket.io').listen(server);

server.listen(7113);
io.set('log level', 0);


var sockArray = [];

var portName = "/dev/tty.usbmodem1421"


app.use(express.static(__dirname + '/public'));


//begin serial port code 

var serialPort = new com.SerialPort(portName, {
    baudrate: 9600,
    parser: com.parsers.readline('\r\n')
  });

serialPort.on('open',function() {
  console.log('Port open');
});

serialPort.on('data', function(data) {
  if(data.split(" ")[0]==="p'"){
    for(var i = 0; i < sockArray.length; i++){
      sockArray[i].emit('news',{someData: data});
    }
  }else{
    console.log(data);
    for(var i = 0; i < sockArray.length; i++){
      sockArray[i].emit('messages',{payload: data});
    }
  }
});

serialPort.on('error', function(err) {
  console.log(err);
});


serialPort.on('close',function(){
  console.log("Closed Port");
})

//end serial port code

io.sockets.on('connection', function (socket) {
  sockArray.push(socket);
});