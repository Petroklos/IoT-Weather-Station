RPi Data-Manager, with Arduino Data-Collector and SQL on Windows Data-Storage 

	Server:
Download XAMPP from https://www.apachefriends.org/download.html, run Apache and MySQL.


	Database:
Open http://localhost/phpmyadmin/ and execute the following SQL script:

	CREATE DATABASE weatherStation;

	CREATE USER 'fostinis'@'%' IDENTIFIED VIA mysql_native_password USING '***';
	GRANT ALL PRIVILEGES ON *.* TO 'fostinis'@'%' REQUIRE NONE WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;

	CREATE TABLE `weatherStation`.`weatherData` (`count` INT(255) NOT NULL AUTO_INCREMENT, `temperature` FLOAT(5) NOT NULL , `airHumidity` FLOAT(5) NOT NULL , `groundHumidity` FLOAT(5) NOT NULL , `airIntensity` FLOAT(5) NOT NULL,`dateTime` DATETIME NOT NULL, PRIMARY KEY(count)) ENGINE = InnoDB;
	
	
	RPi Code:
sudo apt-get install python

Run the code found in rpiGet.py, it might need some more "sudo apt-get install"s for some libraries.

Its eMail function needs a real eMail for the sender. It reads its login data from a file "login.txt", not included here.


	Arduino Code:
sudo apt-get install arduino-cli

There's three code variants, one that generates random values, one that gets analog data from the analog pins and the hybrid which gets analog data for "temperature" and random data for the rest.
Based on what script you want, run the corresponding code and download the corresponding file in the corresponding sketch folder.

arduino-cli sketch new dataCollectorRandom
arduino-cli compile ./dataCollectorRandom/ --fqbn arduino:avr:uno
arduino-cli upload ./dataCollectorRandom/ --fqbn arduino:avr:uno -p /dev/ttyACM0

arduino-cli sketch new dataCollectorAnalog
arduino-cli compile ./dataCollectorAnalog/ --fqbn arduino:avr:uno
arduino-cli upload ./dataCollectorAnalog/ --fqbn arduino:avr:uno -p /dev/

arduino-cli sketch new dataCollectorHybrid
arduino-cli compile ./dataCollectorHybrid/ --fqbn arduino:avr:uno
arduino-cli upload ./dataCollectorHybrid/ --fqbn arduino:avr:uno -p /dev/

	Grafana:
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
