#!/usr/bin/sh

srcdir="./test"
tardir="./target"

for((i=0;i<10000;i++));
do
	srcmd5=`md5sum $srcdir/$i.txt|cut -d ' ' -f1`
#	tarmd5=`md5sum $tardir/$i.txt|cut -d ' ' -f1`

#	if [ $srcmd5 != $tarmd5 ];then
#		echo $i.txt   . $srcmd5  :  $tarmd5
#	fi
	echo $srcmd5
done
	
