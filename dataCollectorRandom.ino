// This code is generating random values for each sensor reading, so the simulated sensor readings will fluctuate randomly over time.

float temperature, airHumidity, groundHumidity, windIntensity;
int randomValue;

void setup() {
        Serial.begin(9600);
        randomSeed(analogRead(0));
        temperature = 20.0;
        airHumidity = 40.0;
        groundHumidity = 50.0;
        windIntensity = 10.0;
}

void loop() {
        randomValue = random(-10,10);
        temperature += temperature * randomValue/100;

        r = random(-10,10);
        airHumidity += airHumidity * randomValue/100;

        r = random(-10,10);
        groundHumidity += groundHumidity * randomValue/100;

        r = random(-10,10);
        windIntensity += windIntensity * randomValue/100;
        if (windIntensity < 0) windIntensity = 0;

        String toPrint = String(temperature) + ' ' + String(airHumidity) + ' ' + String(groundHumidity) + ' ' + String(windIntensity);
        Serial.println(toPrint);

        delay(3000);
}
