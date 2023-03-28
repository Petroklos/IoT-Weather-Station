# RPi Data-Manager, with Arduino Data-Collector and SQL on Windows Data-Storage

## Server:
Download XAMPP from https://www.apachefriends.org/download.html, run Apache and MySQL.


## Database:
Open http://localhost/phpmyadmin/ and execute the SQL script found in databaseCode.sql
	
	
## RPi Code:
sudo apt-get install python

Run the code found in rpiGet.py, it might need some more "sudo apt-get install"s for some libraries.

Its eMail function needs a real eMail for the sender. It reads its login data from the file "login.txt".


## Arduino Code:
sudo apt-get install arduino-cli

There's three code variants, one that generates random values, one that gets analog data from the analog pins and the hybrid which gets analog data for "temperature" and random data for the rest.
Based on what script you want, run the corresponding code and download the corresponding file in the corresponding sketch folder.

arduino-cli sketch new dataCollectorX
arduino-cli compile ./dataCollectorX/ --fqbn arduino:avr:uno
arduino-cli upload ./dataCollectorX/ --fqbn arduino:avr:uno -p /dev/ttyACM0

## Grafana:
Install Grafana for your System, open localhost:3000 on your browser.

Data Sources -> Add data source -> MySQL
Host: localhost:3306
Database: weatherStation
User: grafana
Password: pass

Create -> Dashboard -> Add New Panel

FROM: weatherData
Time Columnd: dateTime
Select: temperature (or whatever else you want)

Apply