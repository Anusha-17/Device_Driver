Below are the steps to execute

1) sudo su

2) insmod module_parameter.ko value=14 name="Hello" arr_value=1,2,3,4

3) dmesg

4) to check module_param_cb() is whether calling that handler function or not. For that, I need to change the variable in sysfs. You can write that variable in two ways.

echo 1 > /sys/module/module_parameter/parameters/cb_value

5) now do, dmesg

6) rmmod module_parameter
