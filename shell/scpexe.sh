#!/bin/sh

taruser="root"
tfile=$4
tupasswd=$3
tarpath=$2
tarip=$1

expect << EOF
spawn ssh -o StrictHostKeyChecking=no $taruser@$tarip "mkdir $tarpath -p"
expect "password:"
send "$tupasswd\n"
expect eof

spawn scp ./${tfile} $taruser@$tarip:$tarpath
expect "password:"
send "$tupasswd\n"
expect eof

spawn ssh -o StrictHostKeyChecking=no $taruser@$tarip "cd $tarpath; tar -xvf ${tfile}; cd fts; ./fdsmsetup"
expect "password:"
send "$tupasswd\n"
expect "input:"
send "s\n"
expect eof

EOF
