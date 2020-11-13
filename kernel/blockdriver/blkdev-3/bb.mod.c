#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x14522340, "module_layout" },
	{ 0x3e14d8d6, "blk_init_queue" },
	{ 0x573939cb, "alloc_disk" },
	{ 0xe5a6404e, "blk_cleanup_queue" },
	{ 0xea147363, "printk" },
	{ 0xce4db10e, "del_gendisk" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xb4390f9a, "mcount" },
	{ 0x8aa14eee, "put_disk" },
	{ 0xbc2262ee, "blk_fetch_request" },
	{ 0x12884d17, "__blk_end_request_all" },
	{ 0x236c8c64, "memcpy" },
	{ 0xd7936fb1, "add_disk" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "BC1258E64A92B3C3BFBF316");

static const struct rheldata _rheldata __used
__attribute__((section(".rheldata"))) = {
	.rhel_major = 6,
	.rhel_minor = 9,
	.rhel_release = 695,
};
