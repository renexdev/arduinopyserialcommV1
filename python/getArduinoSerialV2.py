#!/usr/bin/python
#reneczechdev@gmail.com
#v 1.0 rel 03/16
#Communication with arduino using serial port. Check basicoGetV1.ino

import serial
import datetime
import time

#Define your Arduino serial port: ttyUSBx,ttyACMx
s = serial.Serial('/dev/ttyACM0',9600,timeout=5)
#Output file
fileName = "measO2_160_calibrado03"
writeIt = open(fileName+".dat", "a")
writeIt.close()

setTime = 30
#number of measurements
for i in range(1,10000000): 
	s.write("a\r\n")
	a = s.readline().split()
	if (len(a) == 6):
		current_time = datetime.datetime.now().time()
		writeIt = open(fileName+".dat", "a")
		#local time|VRef|Vout|VAD590|TempAD|Oxigeno|VO2corr300k
		writeIt.write("%s\t%s\t%s\t%s\t%s\t%s\t%s\n" % ( current_time.isoformat(),a[0],a[1],a[2],a[3],a[4],a[5]))#(t,i,O,T))
		writeIt.close()
		
	time.sleep(setTime)

		




