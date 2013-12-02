#include <Servo.h> 
 
Servo myservo;  // create servo object

int LED_redeyes_pin = 5;  // pin for LED eye circuit
int lightPin = 0;         // pin for PhotoResistor
int threshold = 600;      // min amount of light (relative), change this based on your needs
int prankcount = 0;
int blinkcount = 0;

void setup() {
  pinMode(LED_redeyes_pin, OUTPUT);
  myservo.attach(9);   // attaches the servo on pin 9 to the servo object 
  //Serial.begin(9600);  // testing, open the serial port at 9600 bps
}

void loop(){
  myservo.writeMicroseconds(1500);   // not moving
  //Serial.println(analogRead(lightPin),DEC);  // testing, see what the photo resistor is reading
 
  if(prankcount < 1) {
    if((analogRead(lightPin) < threshold)){ 
     
     do {
       // flick curtain once
       delay(5000);                      // once the light goes on, wait this long then flick the curtain
       myservo.writeMicroseconds(3000);  // turn clockwise
       delay(100);                       // motor moves very briefly
       myservo.writeMicroseconds(1500);  // stop turning moving
       prankcount ++;
    
       do {
         // blink eyes
         digitalWrite(LED_redeyes_pin,HIGH);  // LEDs on
         delay(100);
         digitalWrite(LED_redeyes_pin,LOW);   // LEDs off
         delay(100);
         blinkcount ++;
       } while((analogRead(lightPin) < threshold) and (blinkcount < 60));  // blink on and off 60 times
      
      } while (prankcount < 1);  // only run the sequence once when the lights go on
    } 
  }
  
  if(analogRead(lightPin) > threshold){
    // reset the prank
    prankcount = 0;
    blinkcount = 0;
  }
}
