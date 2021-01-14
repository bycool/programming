#!/sbin/sh
cd /lib/
ln -s libc-2.12.so /lib/libc.so.6
ln -s ld-2.12.so /lib64/ld-linux-x86-64.so.2

cd /lib64/
ln -s libc-2.12.so /lib64/libc.so.6
