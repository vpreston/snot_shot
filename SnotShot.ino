//*****SNOTSHOT SENSOR SYSTEM************

/*This is a simple sensor system that will attach to the SnotShot system.
It will indicate when a copter is above snotshot by lighting an ultrabright LED.  
Additionally, it will timestamp and data log sonar ranges so altitude of the 
copter can be caught.

ACTION ITEMS:
- Write to CSV File for later use
*/  
//***************************************************************************

//Include libraries when applicable
#include <Time.h>
#include <Servo.h>

//****************************GLOBALS*****************************************
boolean ledON;               //used to toggle the led
unsigned long newtime;       //the time at the start of loop()
unsigned long timeperiod;    //time for loop() in milliseconds.
int estop_val;               //etop_val == LOW is stopped

int ESTOP = 100;

float bat_volt = 8.00;  //Lipo battery voltage

const int numReadings = 7;
int average = 0;
int index = 0;
int total = 0;
int readings[numReadings];

//*******************Logging Data into File *************************************

//USE AN ALTERNATE SKETCH

//*******************MAPPING OF DIO PINS *************************************
int led_pin = 0;   //USER LED on the ArbotiX Robocontroller, the blinking light
int ESTOP_pin = 23;     //manual switch on the model...stops all servos
int blink_pin = 1;    //running LED
int indicator_pin = 2;
//******************MAPPING OF ANALOG PINS******************************
int sonar_pin = 0;
Servo shoot;
int shoot_pin = 15;
//****************************************************************************

//***********************THE SETUP LOOP**************************************
void setup()
{
  // start serial port at 38400 bps:
  Serial.begin(38400);
  // wait to connect
  delay(1000);
  
  for (int thisReading = 0; thisReading < numReadings; thisReading++)
    readings[thisReading] = 0;
  
  shoot.attach(shoot_pin);
  shoot.writeMicroseconds(1500); 
  //setup input pins
  pinMode(ESTOP_pin, INPUT);           // set pin to input
  digitalWrite(ESTOP_pin, HIGH);       // turn on pullup resistors, 20k resitor to 5VDC on input pin
  pinMode(sonar_pin, INPUT);
  
  //setup output pins
  pinMode(led_pin, OUTPUT);  // initialize the digital pin as an output for onboard LED
  pinMode(blink_pin, OUTPUT);  //output for remote blinking LED
  pinMode(indicator_pin, OUTPUT);
  digitalWrite(indicator_pin, LOW);
  
  //setup the timing and blinky led
  ledON = false;        //used to toggle the board led with loop timer
  timeperiod = 100;    //loop time in milliseconds
  
}// end setup
//*************************THE MAIN PROGRAM LOOP******************************
void loop()
{
  //use the computer clock to create a timed loop, read the present time to start the timer
  newtime = millis();
  
  //read the value of the ESTOP switch, value is LOW when button is pressed, otherwise HIGH
  estop_val = digitalRead(ESTOP_pin);

  //Read the sensor values
  total = total - readings[index];
  readings[index] = analogRead(sonar_pin);
  total = total + readings[index];
  index = index + 1;
  
  if (index >= numReadings)
    index = 0;
  
  average = total/numReadings;

  int dist;
  dist = 0.3914*average + 0.5571;
  
  //print the data
  if (dist <= 108) {
    Serial.println(dist);
    Serial.print(hour());
    Serial.print(":");
    Serial.print(minute());
    Serial.print(":");
    Serial.println(second());
    digitalWrite(indicator_pin, HIGH);
    shoot.writeMicroseconds(2000); 
  }
  else {
    digitalWrite(indicator_pin, LOW);
    shoot.writeMicroseconds(1000); 
  }
  
  //use computer clock to time the loop
   while(millis() < (newtime + timeperiod) )
  {
    //wait until time elaspes
  }
  
  //change the state of the on board LED
  Toggle_led();
  delay(1);
  
}// end void
//****************************************************

//*************SUBROUTINES******************************
void Toggle_led(void)
{
  //toggle the led on the board
  if (ledON == false)
  {
    ledON = true;
    digitalWrite(led_pin, HIGH);   // turn the LED on (HIGH is the voltage level)
    digitalWrite(blink_pin, HIGH);  //turn external LED on
  }  
  else
  {
    ledON = false;
    digitalWrite(led_pin, LOW);    // turn the LED off by making the voltage LOW
    digitalWrite(blink_pin, LOW);  //turn external LED off
  }
}//end Toggle_led
//*******************************************************

//************* end of program****************************
