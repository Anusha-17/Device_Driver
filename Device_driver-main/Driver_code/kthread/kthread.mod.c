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
	{ 0xc1514a3b, "free_irq" },
	{ 0x7d5a7d0b, "kthread_stop" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x8296b546, "class_destroy" },
	{ 0x3129b92e, "wake_up_process" },
	{ 0x4f38cf60, "kthread_create_on_node" },
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
	{ 0x37a0cba, "kfree" },
	{ 0x344fd44f, "pv_ops" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0xb3f7646e, "kthread_should_stop" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "A07A8335BE2A87D4B837232");
