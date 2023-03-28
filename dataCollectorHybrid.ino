// This code is measuring the analog temperature reading and generating random values for the air humidity, ground humidity, and wind intensity readings.

float analogPin0 = A0
float temperature, airHumidity, groundHumidity, windIntensity, tempValue;
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
    tempValue = (analogRead(analogPin0) - 511) / 50;
    temperature += temperature * tempValue / 100;

    r = random(-10, 10);
    airHumidity += airHumidity * r / 100;

    r = random(-10, 10);
    groundHumidity += groundHumidity * r / 100;

    r = random(-10, 10);
    windIntensity += windIntensity * r / 100;
    if (windIntensity < 0) {
        windIntensity = 0;
    }

    String toPrint = String(temperature) + ' ' + String(airHumidity) + ' ' + String(groundHumidity) + ' ' + String(windIntensity);
    Serial.println(toPrint);

    delay(3000);
}
