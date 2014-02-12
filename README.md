Arduino Web Viewer
===
My arduino debug tool. Web viewable.

Installation
---

To get working you'll need npm and node

[Installation instructions](https://gist.github.com/isaacs/579814)


after these things are installed run

    npm install


then run

    sudo npm install -g supervisor
    
    
you will have to rename your serial port to match where the arduino is

    var portName = "/dev/tty.usbmodem1411"
    

to whatever port your arduino occupies then run

    supervisor node readdata.js
   
Arduino Code
---

The code for the arduino is located in

    ./arduino_code/serial
    
It is ugly as sin....and uncommented...oops.

There are two main ideas here, I added two important functions.

###PrintD

    void printD(int port, boolean analogue, boolean in){...}
    
PrintD prints out the value of a port in graphable format by this program. Lets say you want to print pin 7, which is a digital input port.

    printD(7,false,true);
    
This is basically a wrapper for my communication protocal which may be seen below.

![image](http://i.imgur.com/Dqb7xl9.png =256x256)    

###myAnalogWrite

    void myAnalogWrite(int port, int val){...}
    
In order to handle pwm I had to wrap analog write in my own function that keeps track of written values. This is self reported by the programmer.
    

Usage
---

Well...if you managed to understand my arduino code you shuold just hook up the arduino, load the code. Then you should run: 

    supervisor node readdata.js
    
then point a browser at your computer with port 7113.

    http://localhost:7113
    
when it asks for an IP enter your own again. (just hitting enter will default to localhost)
 