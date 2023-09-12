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
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xb44ad4b3, "_copy_to_user" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0x26c2e0b5, "kmem_cache_alloc_trace" },
	{ 0x8537dfba, "kmalloc_caches" },
	{ 0xc5850110, "printk" },
	{ 0x37a0cba, "kfree" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "0A1ED604DDB78C4AD05481D");
