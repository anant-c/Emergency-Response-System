#include <Arduino.h>
#include "ultrasonic.h"

const int trigPin = 12; // D6
const int echoPin = 14; // D5

#define SOUND_VELOCITY 0.034

long duration;
float distanceCm;

void configUltraSonic(void){
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

float getUltraSonicValue(void){
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    
    // Calculate the distance
    distanceCm = duration * SOUND_VELOCITY/2;
      
    return distanceCm;
}