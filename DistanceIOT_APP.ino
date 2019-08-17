/*
This project is a notification app that communicates through Node-Red IOT. It simply
sends the value "count" through Serial so Node Red can interpret the value from this code.
Once sent over, the value is sent to a gauge node that diplays it as a level. A function node is used
that sends notifications on the app as well as text messages through the Twilio node once it gets in the 
RED ZONE. The value comes from an ultrasonic distance sensor.
*/

#include<Arduino.h>

int maxRange = 200;
int minRange = 0;
long duration, distance;

int ledPin = 11;
int trigPin = 3;
int echoPin = 4;

void numberCount();
void setup(){
    pinMode(ledPin, OUTPUT);
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    Serial.begin(9600);
}

void loop(){
    // numberCount();
    digitalWrite(trigPin, LOW); 
    delayMicroseconds(2); 

    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10); 
    
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    
    //Calculate the distance (in cm) based on the speed of sound.
    distance = duration/58.2;
    
    if (distance >= maxRange || distance <= minRange){

        Serial.println("OUT OF RANGE");
    }
    else {
    /* Send the distance to the computer using Serial protocol, and
    turn LED OFF to indicate successful reading. */
    Serial.println(distance);
    // digitalWrite(ledPin, LOW); 
    }

    if (distance < 23){
        digitalWrite(ledPin, HIGH);
    } else {
        digitalWrite(ledPin, LOW);
    }
    
    
    //Delay 50ms before next reading.
    delay(50);
}

void numberCount(){
    for(int count = 0; count < 11; count++){
        Serial.println(count);
        delay(1000);

        if(count > 10){
            count = 0;
        }
    } 
}



