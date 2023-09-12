obj-m += interrupt.o
obj-m += softirqs.o
obj-m += tasklets.o
obj-m += threadedirq.o
obj-m += workqueues.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean