CREATE DATABASE weatherStation;

CREATE USER 'grafana'@'%' IDENTIFIED VIA mysql_native_password USING '***';

GRANT ALL PRIVILEGES ON *.* TO 'grafana'@'%' REQUIRE NONE WITH GRANT OPTION MAX_QUERIES_PER_HOUR 0 MAX_CONNECTIONS_PER_HOUR 0 MAX_UPDATES_PER_HOUR 0 MAX_USER_CONNECTIONS 0;

CREATE TABLE `weatherStation`.`weatherData` (
  `count` INT(255) NOT NULL AUTO_INCREMENT,
  `temperature` FLOAT(5) NOT NULL ,
  `airHumidity` FLOAT(5) NOT NULL ,
  `groundHumidity` FLOAT(5) NOT NULL ,
  `windIntensity` FLOAT(5) NOT NULL,
  `dateTime` DATETIME NOT NULL,
  PRIMARY KEY(count)
) ENGINE = InnoDB;
