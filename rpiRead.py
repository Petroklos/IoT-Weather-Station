import serial
import sys
import array
import mysql.connector
import smtplib
import ssl
import datetime

weather = [[]]
temp = []

#initialize some values and serial read from Arduino
ser = serial.Serial('/dev/ttyACM0', 9600)
stuff = ser.readline()
readTemp, readAirHum, readGroundHum, readAirIntense = stuff.split()
temp.insert(0,[readTemp, readAirHum, readGroundHum, readAirIntense])
z = 0

#open connection to database
try:
        mydb = mysql.connector.connect(
        host = "192.168.1.8",
        user = "grafana",
        database = "weatherstation",
        port = "3306"
        )
        print "Database Connection Successful"
except:
        print "Database Connection Failed"
mycursor = mydb.cursor()

#set up email sender and receivers, gets values from external .txt file
def getLogin():
        user = passw = ""
        with open("login.txt", "r") as f:
                file = f.readlines()
                user = file[0].strip()
                passw = file[1].strip()
        return user, passw

email, password = getLogin()

server = smtplib.SMTP_SSL("smtp.gmail.com", 465)
server.login(email, password)
server.sendmail(email,"cs131104@uniwa.gr","Weather Node Initiated")

while True:
        #reads up to 10 values, can be interupted
        for i in range(10):
                #reads from Arduino, 4 values in one String seperated by " ".
                stuff = ser.readline()
                readTemp, readAirHum, readGroundHum, readAirIntense = stuff.split()
                now = datetime.datetime.utcnow()
                weather.insert(i, [readTemp, readAirHum, readGroundHum, readAirIntense, now])

                #z is the "5 minute" or "10 uninterupted values" counter, used to check if there was a temp increase or humidity decrease every 5 mins
                if z == 0:
                        temprOld = float(weather[i][0])
                        airHumOld = float(weather[i][1])
                        z = z+1
                elif z == 9:
                        temprNow = float(weather[i][0])
                        airHumNow = float(weather[i][1])
                        if temprNow >= temprOld*1.4 or airHumNow <= airHumOld*0.5:
                                server.sendmail(email,"cs131104@uniwa.gr","Temperature or Humidity Instability")
                        z = 0
                else:
                        z = z+1

                #compares temperature with previous temperature value, if difference equal or higher to 10%, break for
                if i == 0:
                        cur = float(weather[i][0])
                        pre = float(temp[0][0])
                        if cur >= pre*1.1 or cur <= pre*0.9:
                                break
                else:
                        cur = float(weather[i][0])
                        pre = float(weather[i-1][0])
                        if cur >= pre*1.1 or cur <= pre*0.9:
                                break

        #writes as many values as the previous for-loop read, up to 10
        for j in range(i+1):
                sql = "INSERT INTO WEATHERDATA(temperature,airHumidity,groundHumidity,airIntensity,dateTime) VALUES (%s,%s,%s,%s,%s)"
                val = (weather[j][0],weather[j][1],weather[j][2],weather[j][3],weather[j][4])
                mycursor.execute(sql,val)
        mydb.commit()

        print("Data Written to Database")
        for j in range(4):
                temp[0][j] = weather[i][j]

server.quit()
