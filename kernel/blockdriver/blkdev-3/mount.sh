#!/sbin/sh

insmod bb.ko

mkfs.ext2 /dev/blkmdev
mount -t ext2 /dev/blkmdev /mnt/

mkdir /sda
mkfs.ext2 /dev/sda
mount -t ext2 /dev/sda /sda
