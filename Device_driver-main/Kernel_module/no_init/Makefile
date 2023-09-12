obj-m += no_init.o

KDIR:= /lib/modules/$(shell uname -r)/build/

PWD:= $(pwd)

all:
        make -C $(KDIR) M=$(PWD) modules
clean:
        make -C $(KDIR) M=$(PWD) clean
