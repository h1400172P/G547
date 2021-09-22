obj-m := imu_char.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	gcc -o ioctlusr user_app.c



