#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0xc79d2779, "module_layout" },
	{ 0x8b66e8a1, "cdev_del" },
	{ 0xf4bb4b0f, "device_destroy" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x8296b546, "class_destroy" },
	{ 0xdb7d6e97, "device_create" },
	{ 0x689c90fe, "__class_create" },
	{ 0x406681dd, "cdev_add" },
	{ 0xb8c2987b, "cdev_init" },
	{ 0xb37061b3, "cdev_alloc" },
	{ 0x3fd78f3b, "register_chrdev_region" },
	{ 0x26948d96, "copy_user_enhanced_fast_string" },
	{ 0xafb8c6ff, "copy_user_generic_string" },
	{ 0x72a98fdb, "copy_user_generic_unrolled" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "253B02E677E271F6A37E5BE");
