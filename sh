qemu-system-x86_64 -smp 2 -m 1024M -kernel linux-4.10/arch/x86_64/boot/bzImage -nographic -append "root=/dev/ram0 rw rootfstype=ext4 console=ttyS0 init=/linuxrc -initrd" ./ramdisk.gz
qemu-system-i386 -m 4096M -kernel linux-2.6.32.12.x86/arch/x86/boot/bzImage -nographic -append "root=/dev/ram0 rw rootfstype=ext4  noapic console=ttyS0 init=/linuxrc" -initrd ./ramdisk.x86.gz

find . | cpio -H newc -o > ../initrd_cpio.img

make x86_64_defconfig
make menuconfig

General setup  --->
    ----> [*] Initial RAM filesystem and RAM disk (initramfs/initrd) support
Device Drivers  --->
    [*] Block devices  --->
            <*>   RAM block device support
            (65536) Default RAM disk size (kbytes)

ext4打开

make bzImage -j 4
