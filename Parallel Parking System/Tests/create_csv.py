import re
file_r=open("Ultrasonic Sensor Readouts.txt","r")
file_w=open("Statistics.csv","w")
file_w.write("SensorA,SensorB,SensorC\n")
count=1
string=""
for line in file_r:
		if count is not 3:
			line = line.rstrip('\n')
			string += line
			string += ","
		if count is 3:
			line = line.rstrip('\n')
			string += line
			string += "\n"
			count = 0
		count += 1
file_w.write(string)
	#if map(int, re.findall(r'\d+', line)) is not 0:
	#	print line
	#	line.rstrip('\n')
	#	string+=line
	#	string+=","
	#	count += 1
	#if count is 4:
#		count = 1
#		string.rstrip('\n')
#		file_w.write(string)
#		string=""
