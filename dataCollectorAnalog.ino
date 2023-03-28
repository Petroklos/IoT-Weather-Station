// This code is measuring values from sensors, so the sensor readings will reflect the real-world conditions.

float analogPin0 = A0, analogPin1 = A1, analogPin2 = A2, analogPin3 = A3;
float temperature, airHumidity, groundHumidity, windIntensity, tempValue;

void setup() {
        Serial.begin(9600);
        temperature = analogRead(analogPin0);
        airHumidity = 40.0;
        groundHumidity = 50.0;
        windIntensity = 10.0;
}

void loop() {
        tempValue = (analogRead(analogPin0)-511)/50;
        temperature += temperature * tempValue/100;

        tempValue = (analogRead(analogPin1)-511)/50;
        airHumidity += airHumidity * tempValue/100;

        tempValue = (analogRead(analogPin2)-511)/50;
        groundHumidity += groundHumidity * tempValue/100;

        tempValue = (analogRead(analogPin3)-511)/50;
        windIntensity += windIntensity * tempValue/100;
        if (windIntensity < 0) windIntensity = 0;
        
        String toPrint = String(temperature) + ' ' + String(airHumidity) + ' ' + String(groundHumidity) + ' ' + String(windIntensity);
        Serial.println(toPrint);

        delay(3000);
}
