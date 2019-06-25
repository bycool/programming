#!/bin/sh

osinfo=`cat /etc/issue | grep "Red"`

os=$?
echo $osinfo
echo $os


