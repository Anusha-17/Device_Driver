obj-m+= Second_device_driver.o

# it refer the kernel build scripts form below path and build  the driver
KDIR = /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR)  M=$(shell pwd) modules
clean:
	make -C $(KDIR)  M=$(shell pwd) clean
