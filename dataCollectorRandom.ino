// Generates Random Values

float temperature, airHumidity, groundHumidity, windIntensity;
int r;

void setup() {
        Serial.begin(9600);
        randomSeed(analogRead(0));
        temperature = 20.0;
        airHumidity = 40.0;
        groundHumidity = 50.0;
        windIntensity = 10.0;
}

void loop() {
        r = random(-10,10);
        temperature += temperature*r/100;

        r = random(-10,10);
        airHumidity += airHumidity*r/100;

        r = random(-10,10);
        groundHumidity += groundHumidity*r/100;

        r = random(-10,10);
        windIntensity += windIntensity*r/100;
        if (windIntensity < 0)
                windIntensity = 0;

        // It's worth noting that this code is generating random values for each sensor reading, so the simulated sensor readings will fluctuate randomly over time.
        String toPrint = String(temperature) + ' ' + String(airHumidity) + ' ' + String(groundHumidity) + ' ' + String(windIntensity);
        Serial.println(toPrint);

        delay(3000)
}
