//analog input value generator

float analogPin0 = A0, analogPin1 = A1, analogPin2 = A2, analogPin3 = A3;
float val, temp, airHum, groundHum, airInt;

void setup() {
        Serial.begin(9600);
        temp = analogRead(analogPin0);
        airHum = 40.0;
        groundHum = 50.0;
        airInt = 10.0;
}

void loop() {
        val = (analogRead(analogPin0)-511)/50;
        temp = temp + temp*val/100;

        val = (analogRead(analogPin1)-511)/50;
        airHum = airHum + airHum*val/100;

        val = (analogRead(analogPin2)-511)/50;
        groundHum = groundHum + groundHum*val/100;

        val = (analogRead(analogPin3)-511)/50;
        airInt = airInt + airInt*val/100;
        if (airInt < 0)
                airInt = 0;

        String toPrint = String(temp) + ' ' + String(airHum) + ' ' + String(groundHum) + ' ' + String(airInt);
        Serial.println(toPrint);

        delay(3000);
}