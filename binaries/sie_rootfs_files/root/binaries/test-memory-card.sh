#!/bin/sh
# Program:
#	Program trys firstly to detect if uSD card inserted and then 
#	mount data 
# History:
# Author:
# 2010-08-19	XiangFu Liu,	xiangfu@sharism.cc

if [ -b "/dev/mmcblk0" ] ; then
	echo "there is a memory card present"
else
	echo "ERROR - there is no memory card inserted"
	exit 1
fi

#make multi-layer directory
mkdir -p /tmp/card

echo "try to mount mmc card"
mount /dev/mmcblk0p1  /tmp/card/
if [ $? == 0 ] ; then
	echo "mount ok"
else
	echo "ERROR - can not do a real mount on memory card"
	exit 1
fi

echo "testing ..."
dd if=/dev/zero of=/tmp/card/testfile bs=1024 count=3096
if [ $? == 0 ] ; then
	echo "mount ok"
else
	echo "ERROR - can not do a real test for mounting memory card"
	exit 1
fi

rm -rf /tmp/card/testfile
umount /tmp/card
echo "test done"


