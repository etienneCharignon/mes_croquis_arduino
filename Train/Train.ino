// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 0;    // variable to store the servo position 
 
void setup() 
{ 
  myservo.attach(7);  // attaches the servo on pin 9 to the servo object 
  pinMode(13, OUTPUT); 
  pinMode(2, INPUT_PULLUP);

  Serial.begin(115200);
} 
 

int buttonState, prevButtonState;

void loop() 
{
    myservo.write(120);              // tell servo to go to position in variable 'pos'
    prevButtonState = buttonState;
    buttonState = digitalRead(2);
    Serial.println(buttonState);
    
    if (buttonState == LOW && prevButtonState == LOW) {
        digitalWrite(13, HIGH);
        delay(5000);                               // in steps of 1 degree 
        myservo.write(10);              // tell servo to go to position in variable 'pos'
        delay(2000);                               // in steps of 1 degree 
        digitalWrite(13, LOW);
    }
} 
