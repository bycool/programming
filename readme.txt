qemu-system-x86_64 -kernel ./bzImage -initrd initrd.img -smp 2 -gdb tcp::12345 -S   //start kernel by qemu with bzImage

gdb vmlinux  //gdb kernel with vmlinux which has debug info.
target remote : 12345   //connect to qemu through port 12345
