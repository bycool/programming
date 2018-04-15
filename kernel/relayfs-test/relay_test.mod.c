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
	{ 0x3eba92, "debugfs_create_dir" },
	{ 0xc623f1f, "relay_file_operations" },
	{ 0xced11b05, "debugfs_create_file" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0x1151e376, "relay_switch_subbuf" },
	{ 0x9629486a, "per_cpu__cpu_number" },
	{ 0x3d0951f7, "relay_close" },
	{ 0xea147363, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0xe8049993, "debugfs_remove" },
	{ 0x99d2b25f, "relay_buf_full" },
	{ 0x78764f4e, "pv_irq_ops" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0x4925d54e, "relay_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "75550659E2D2AB1B915AC70");

static const struct rheldata _rheldata __used
__attribute__((section(".rheldata"))) = {
	.rhel_major = 6,
	.rhel_minor = 9,
	.rhel_release = 695,
};
