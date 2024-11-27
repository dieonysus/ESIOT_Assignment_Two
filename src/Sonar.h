#ifndef __SONAR__
#define __SONAR__

class Sonar {
private:
    int trigPin;
    int echoPin;

public:
    Sonar(int trigPin, int echoPin);

    void initSonar();

    long measureDistance();
};

#endif
