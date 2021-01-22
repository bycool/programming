#!/bin/sh

mkdir -p /mnt/sdb
mkfs.ext4 /dev/sdb3
mount -t ext4 /dev/sdb3 /mnt/sdb

mkdir -p /mnt/sdc
mkfs.ext4 /dev/sdc1
mount -t ext4 /dev/sdc1 /mnt/sdc
