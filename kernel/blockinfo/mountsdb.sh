#!/bin/sh

mkdir -p /mnt/sdd1
mkfs.ext4 /dev/sdd1
mount -t ext4 /dev/sdd1 /mnt/sdd1

#mkdir -p /mnt/sdd2
#mkfs.ext4 /dev/sdd2
#mount -t ext4 /dev/sdd2 /mnt/sdd2
