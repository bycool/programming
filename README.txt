qemu-system-x86_64 -kernel ./bzImage -initrd initrd.img -smp 2 -gdb tcp::12345 -S   //start kernel by qemu with bzImage

gdb vmlinux  //gdb kernel with vmlinux which has debug info.
target remote : 12345   //connect to qemu through port 12345


qemu-system-x86_64 -smp 2 -m 1024M -nographic -kernel linux-2.6.32.12/arch/x86_64/boot/bzImage -initrd ./initramfs.img -append "root=/dev/ram0 rw rootfstype=ext4 console=ttyS0 init=/linux" -gdb tcp::12345

