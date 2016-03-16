
#define VCCIN  5.0 //Source Voltage
#define SAMPLING  50  // in mili seconds

/*
reneczechdev@gmail.com
v 1.0 rel 03/16
Simple meas. with arduino ADC 
Using External Vin at 5V
*/
//Anlogic pins

const int VRefPin = A0;
const int VoutPin = A1;
const int VLM35Pin = A2;
const int VAD590Pin = A3;
//Led low O2 level or some other condition
int ledPin =  13;

//Number of measurements
const int avTimes = 64;


void setup() {
  // initialize serial communication at 9600
   Serial.begin(9600);
   pinMode(ledPin, OUTPUT);
   digitalWrite(ledPin, LOW);
   analogReference(EXTERNAL);
}

void loop() {
  //Take the measurements
  float VRef = measureIt(VRefPin,avTimes);
  float Vout= measureIt(VoutPin,avTimes);
  //float VLM35 = measureIt(VLM35Pin,avTimes);
  float VAD590 = measureIt(VAD590Pin,avTimes);
   
  //Some calculations in Arduino
  float Temp = VAD590 * 94.190347;
  float VO2_Corr = (VRef-Vout)  * (1+0.0108183/2.791437*(300.-Temp)) - 0.2992; 
  float Oxigeno = VO2_Corr / 2.47292 * 20.94 ;

 // if there's any serial available, read it:
  while (Serial.available() > 0) {

  //Look for command read set as "a":adquire
  if (Serial.read() == 'a') {
      delay(500);
      
  Serial.print(VRef,5);
  Serial.print("\t");
  Serial.print(Vout,5);
  Serial.print("\t");
  Serial.print(VAD590,5);
  Serial.print("\t");
  Serial.print(Temp,2);
  Serial.print("\t");
  Serial.print(Oxigeno,2);
  Serial.print("\t");
  Serial.println(VO2_Corr,3);
  }
     delay(500);
     //digitalWrite(ledPin, LOW);
  }

  if(Oxigeno<19)  digitalWrite(ledPin, HIGH);
}


float measureIt(int readPin, int avTimes){  
  float Vi = 0;
  float VMeas=0 ;
  
  for (int i = 1; i <= avTimes; i++) { 
    int measDigVal = analogRead(readPin); //ANALOGICO
   delay(SAMPLING);
    // Convert the analog reading (which goes from 0 - 1023) to a VOut (0 - 5V):
     Vi = measDigVal* (VCCIN / 1023.0);
    VMeas = VMeas + Vi;
  }
   VMeas /=(avTimes*1.0);
  return VMeas;
}

