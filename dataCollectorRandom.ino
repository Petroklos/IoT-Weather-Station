//random value generator

float temp, airHum, groundHum, airInt;
int r;

void setup() {
        Serial.begin(9600);
        randomSeed(analogRead(0));
        temp = 20.0;
        airHum = 40.0;
        groundHum = 50.0;
        airInt = 10.0;
}

void loop() {
        r = random(-10,10);
        temp = temp + temp*r/100;

        r = random(-10,10);
        airHum = airHum + airHum*r/100;

        r = random(-10,10);
        groundHum = groundHum + groundHum*r/100;

        r = random(-10,10);
        airInt = airInt + airInt*r/100;
        if (airInt < 0)
                airInt = 0;

        String toPrint = String(temp) + ' ' + String(airHum) + ' ' + String(groundHum) + ' ' + String(airInt);
        Serial.println(toPrint);

        delay(3000);
}