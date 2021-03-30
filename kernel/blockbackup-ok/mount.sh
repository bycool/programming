#!/bin/sh

mkdir -p /mnt/debugfs/

mount -t debugfs debugfs /mnt/debugfs

mount -t ext4 /dev/sdb /mnt/sdb
mount -t ext4 /dev/sdc /mnt/sdc
