# IoT Weather Station

The IoT Weather Station project tracks environmental values using Arduinos for endpoints, Raspberry PIs for data aggregators, and a Windows PC for database management and data presentation. It sends alerts to administrators when certain environmental conditions are not met.

## Server Setup

1. Download XAMPP from https://www.apachefriends.org/download.html, run Apache and MySQL.

2. Open http://localhost/phpmyadmin/ and create a new database named weatherStation.

3. Execute the SQL script found in databaseCode.sql to create the necessary tables and user for the Grafana data source.

4. Install Grafana for your system, open localhost:3000 on your browser.

5. In Grafana, add a data source for MySQL:
```
Host: localhost:3306
Database: weatherStation
User: grafana
Password: pass
```

6. Create a dashboard and add a new panel:
```
FROM: weatherData
Time Column: dateTime
Select: *your desired value*
```

## RPi Setup

1. The Raspberry Pis will be connected to the server via network. Ensure they are on the same local network or a shared VPN, or using a static IP with the server ports made accessible to the public.

2. Run the rpiGet.py script on the Raspberry Pi to collect data from the Arduino and send it to the server. It requires Python to be installed and may need extra libraries. The eMail function needs a real email for the sender and reads login data from the file login.txt.

## Arduino Setup

1. The Arduinos will be connected to the Raspberry Pis via Serial (e.g., USB).

2. Depending on the current use case, download the desired file in the respective sketch folder and execute the code. There are three code variants for the Arduinos:

    * `dataCollectorAnalog.ino` reads analog data from the analog pins. This would be executed in real-world scenarios.

    * `dataCollectorRandom.ino` generates random values for testing purposes. This would be executed to test the communication between endpoints, aggregator, and database.

    * `dataCollectorHybrid.ino` reads analog data for some values and generates random data for the rest. This would be used in lab scenarios to verify the whole system but with limited access to sensors.

3. Depending on the current use case, download the desired file in the respective sketch folder and execute the code. For example, if using Arduino UNO boards:
```
sudo apt-get install arduino-cli
arduino-cli sketch new dataCollectorX
arduino-cli compile ./dataCollectorX/ --fqbn arduino:avr:uno
arduino-cli upload ./dataCollectorX/ --fqbn arduino:avr:uno -p /dev/ttyACM0
```

## Endnotes

This project has been tested on a Windows PC but should work on a Linux server as well, potentially even the data-aggregating Raspberry Pi for small enough installations.
