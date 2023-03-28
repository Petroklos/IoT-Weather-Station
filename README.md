# IoT Weather Station

Using Arduinos for endpoints, Raspberry PIs for data aggregators and a Windows PC for database management and data presentation, this simple IoT project tracks the desired enviromental values and informs the administrators when things go wrong.

Open http://localhost/phpmyadmin/ and execute the SQL script found in databaseCode.sql.

## RPi Code

Run the code found in rpiGet.py. It will need python to have been installed and might need some extra libraries as well.

Its eMail function needs a real eMail for the sender. It reads its login data from the file "login.txt".

The Raspberry PIs will be connected to the Server via Network. Make sure that they're on the same local network, or on a shared VPN, or using a static IP with the Server Ports made accessible to the public.

## Arduino Code

The Arduinos will be connected to the Raspberry PIs via Serial, eg USB.

There's three code variants:
- *dataCollectorAnalog.ino* reads analog data from the analog pins. This would be executed in real world scenarios.
- *dataCollectorRandom.ino* generates random values for testing purposes. This would be executed to test the communication between endpoints, agregator and database.
- *dataCollectorHybrid.ino* reads analog data for some values and generates random data for the rest. This would be used in lab scenarios to verify the whole system but with limited access to sensors.

Based on the current usecase, download the desired file in the respective sketch folder and execute the code.

eg, if using Arduino UNO boards:
```
sudo apt-get install arduino-cli
arduino-cli sketch new dataCollectorX
arduino-cli compile ./dataCollectorX/ --fqbn arduino:avr:uno
arduino-cli upload ./dataCollectorX/ --fqbn arduino:avr:uno -p /dev/ttyACM0
```

## Server

Download XAMPP from https://www.apachefriends.org/download.html, run Apache and MySQL.

This has been tested on a Windows PC but should work perfectly fine on a Linux Server as well, potentially even the data agregating Raspberry PI for small enough installations.

## Grafana:
Install Grafana for your System, open localhost:3000 on your browser.

Data Sources -> Add data source -> MySQL
```
Host: localhost:3306
Database: weatherStation
User: grafana
Password: pass
```
Create -> Dashboard -> Add New Panel
```
FROM: weatherData
Time Columnd: dateTime
Select: *your desired value*
```
Apply
