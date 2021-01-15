#!/bin/sh

mkdir -p /mnt/sdb
mkfs.ext4 /dev/sdb1
mount -t ext4 /dev/sdb1 /mnt/sdb
