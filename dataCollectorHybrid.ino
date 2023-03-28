// Reads Analog Temperature value and Randomly Generates all other values

float analogPin0 = A0, value, temperature, airHumidity, groundHumidity, windIntensity;
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
    value = (analogRead(analogPin0) - 511) / 50;
    temperature += temperature * value / 100;

    r = random(-10, 10);
    airHumidity += airHumidity * r / 100;

    r = random(-10, 10);
    groundHumidity += groundHumidity * r / 100;

    r = random(-10, 10);
    windIntensity += windIntensity * r / 100;
    if (windIntensity < 0) {
        windIntensity = 0;
    }

    // It's worth noting that airHum, groundHum and airInt values are randomly generated, while temp value is generated based on the analog sensor reading.
    // The random value generated for each variable is a value between -10% and 10%, scaled by the current value of the variable. 
    // This means that the simulated sensor readings will fluctuate randomly over time, but will generally trend upwards or downwards based on the initial value of the analog input pin.
    
    String toPrint = String(temperature) + ' ' + String(airHumidity) + ' ' + String(groundHumidity) + ' ' + String(windIntensity);
    Serial.println(toPrint);

    delay(3000);
}
