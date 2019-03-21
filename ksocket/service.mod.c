#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x14522340, "module_layout" },
	{ 0xd691cba2, "malloc_sizes" },
	{ 0xaed2f3f9, "sock_release" },
	{ 0xf69f552f, "sock_recvmsg" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xea147363, "printk" },
	{ 0x42224298, "sscanf" },
	{ 0xf6d94413, "sock_sendmsg" },
	{ 0xb4390f9a, "mcount" },
	{ 0x2044fa9e, "kmem_cache_alloc_trace" },
	{ 0x17084894, "sock_create" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "D33BF02567192A09EAA9785");

static const struct rheldata _rheldata __used
__attribute__((section(".rheldata"))) = {
	.rhel_major = 6,
	.rhel_minor = 9,
	.rhel_release = 695,
};
