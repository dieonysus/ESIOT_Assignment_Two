#include "Sonar.h"
#include "Arduino.h"

Sonar::Sonar(int trigPin, int echoPin) {
    this->trigPin = trigPin;
    this->echoPin = echoPin;
}


void Sonar::initSonar() {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

long Sonar::measureDistance() {
    long duration, distance;

    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    duration = pulseIn(echoPin, HIGH);

    distance = duration * 0.034 / 2;

    return distance;
}