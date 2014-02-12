int x = 0;
int counter = 0;
int led = 3;
int debugPins[13]; //required

void setup(){
  Serial.begin(115200);
  pinMode(led, OUTPUT);
}

void loop(){
//  String printOut = "Hi me";
 //String printOut = "sensorValue=" + String(sensorValue) + ", analogOut=" + String(analogOut);
  doIt();
  doIt4();
//  doIt2();
//  doIt3();
}

void doIt4(){
 printD(0,true,true); 
}

void doIt3(){
  printDTherm(0,true,true);
  delay(500);
}

void doIt2(){
  digitalWrite(led, HIGH);
  printD(led,false,false);
  delay(5000);
  digitalWrite(led,LOW);
  printD(led,false,false);
  delay(5000);
}

void doIt(){
   x = x + 1;
 String po2;
 counter = counter += 1;
 if(x==25){
   x=0;
 }
 if(counter>50){
   po2 = "p' 2,"+ String(x*(25-x)) + ",out";
   Serial.println(po2);
 }
 String printOut = "p' 1,"+ String(x) + ",out";
 Serial.println(printOut);
 printOut = "p' 3,"+ String(x^2) + ",in";
 Serial.println(printOut);
  printOut = "p' 4,";
  Serial.print(printOut);
  Serial.print(pow(x,2));
  Serial.println(",out");
 delay(100);
 if(counter%100 == 0){
   Serial.println("Counter has reached: "+ String(counter));
   counter = 50;
 }
   myAnalogWrite(13,255-((x*x)*(-1*(x%2))));
   printD(13,true,false);
 }


void myAnalogWrite(int port, int val){
  analogWrite(port,val);
  debugPins[port-1] = val;
}

//Prints to serial the value from a port.
void printD(int port, boolean analogue, boolean in){
  int sensorValue = 0;
  String io = "";
  if(in){
    io = "in";
    if(analogue){
     sensorValue = analogRead(port); 
    }else{
     sensorValue = digitalRead(port);
    }
  }else{
    io = "out";
    if(analogue){
      sensorValue = debugPins[port-1];
    }else{
      sensorValue = digitalRead(port);
    } 
  }
//  Serial.println(PORTB);
//  Serial.println("Port was: "+String(sensorValue));
  Serial.print("p' ");
  Serial.print(String(port));
  Serial.print(",");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.println(io);
  
}

//    if(port>0 && port<8){
//      sensorValue = bitRead(PORTD,port);
//    }else if(port>7 && port<13){
//      sensorValue = bitRead(PORTB,port);
//    }



void printDTherm(int port, boolean analogue, boolean in){
    int sensorValue = 0;
  String io = "";
  if(in){
    io = "in";
    if(analogue){
     sensorValue = analogRead(port); 
    }else{
     sensorValue = digitalRead(port);
    }
  }else{
    io = "out";
//    if(port>0 && port<8){
//      sensorValue = bitRead(PORTD,port);
//    }else if(port>7 && port<13){
//      sensorValue = bitRead(PORTB,port);
//    }
  sensorValue = digitalRead(port);
    
  }
  Serial.println(sensorValue);
  Serial.println(Thermister(sensorValue));
//  Serial.println("Port was: "+String(sensorValue));
  Serial.print("p' ");
  Serial.print(String(port));
  Serial.print(",");
  Serial.print(Thermister(sensorValue));
  Serial.print(",");
  Serial.println(io);
}



double Thermister (int RawADC) {
double Temp;
Temp = log (((10240000/RawADC) - 10000));
Temp = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp)) * Temp);
Temp = Temp - 273.15; // Convert Kelvin to Celcius
return Temp;
}
