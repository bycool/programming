#!/bin/sh
while read line
do
#	echo $line
	#echo "-----------------------------------------------" >> etcfile.txt
	#echo $line |awk '{print $2":"$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15}'  >> etcfile.txt
	package=$(echo $line |awk '{print $2}')
	dpkg -S $package |grep "$package:" |grep "/etc/" >>etcfile.txt
done < hello.txt
