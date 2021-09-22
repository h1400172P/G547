        #include <linux/kernel.h> /* We're doing kernel work */
	#include <linux/module.h> /* Specifically, a module */
	#include <linux/fs.h>
	#include <linux/uaccess.h>
	#include <linux/time.h>
	#include<linux/init.h>
	#include <linux/cdev.h>
	#include<linux/types.h>
	#include <linux/kdev_t.h>
	#include <linux/device.h>
	#include <linux/random.h>
	#include "imu_dev.h"
	#define SUCCESS 0
	#define DEVICE_NAME "imu"
	
	static dev_t first; // variable for device number
	static struct cdev c_dev; // variable for the character device structure
	static struct class *cls; // variable for the device class
	
	
	/*
	* Is the device open right now? Used to prevent
	* concurent access into the same device
	*/
	static int Device_Open = 0;
	
	  static int ch_no;
	  static int data_x,data_y,data_z;
	
	uint16_t imu_reading,i ;
	
	
	//file open //
	static int imu_open(struct inode *inode, struct file *file)
	{
	//#ifdef DEBUG
	printk(KERN_INFO "device_open(%p)\n", file);
	//#endif
	
	
	/*To avoid intantiating two process simultaneously*/
	if (Device_Open)
	return -EBUSY;
	
	Device_Open++;
	try_module_get(THIS_MODULE);
	return SUCCESS;
	}
	
	static int imu_close(struct inode *inode, struct file *file)
	{
	//#ifdef DEBUG
	printk(KERN_INFO "device_release(%p,%p)\n", inode, file);
	//#endif
	
	
	Device_Open--;
	
	module_put(THIS_MODULE);
	return SUCCESS;
	}
	
	/*
	* This function is called whenever a process which has already opened the
	* device file attempts to read from it.
	*/
	static ssize_t imu_read(struct file *file, 
	char __user * buffer,
	size_t length, 
	loff_t * offset)
	{
	int bytes_read,retval ;
	
        bytes_read=0;
	get_random_bytes(&i,sizeof(i));
	
	
	imu_reading= 64*(i%1024);
	printk("IMU_READING IS : %d ",imu_reading);
	
        

	retval= copy_to_user(buffer, &imu_reading , sizeof(imu_reading));
	
	return retval;
	
	
	return bytes_read;
	}
	
	
	
	/*
	* This function is called whenever a process tries to do an ioctl on our
	* device file.
	*/
	long imu_ioctl(struct file *file, /* ditto */
	unsigned int ioctl_num, /* number and param for ioctl */
	unsigned long ioctl_param)
	{
	//int *temp_ch_no;
	int *temp_imu_reading;
        int *temp_pressure;
        int *temp_gyro_x;
        int *temp_gyro_y;
        int *temp_gyro_z;
        int *temp_comp_x;
        int *temp_comp_y;
        int *temp_comp_z;
        int *temp_acc_x;
        int *temp_acc_y;
        int *temp_acc_z;
	
	/*
	* Switch according to the ioctl called
	*/
	switch (ioctl_num) {
	case IOCTL_GET_BAROMETER:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_pressure);
	printk(KERN_INFO "BAROMETRIC PRESSURE MEASURED is - %d \n",imu_reading);
	
	
	break;
	
	case IOCTL_GET_GYROX:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_gyro_x);
	printk(KERN_INFO "GYROSCOPE data in x direction is - %d \n",imu_reading);
	
	
	break;


        case IOCTL_GET_GYROY:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_gyro_y);
	printk(KERN_INFO "GYROSCOPE data in y direction is - %d \n",imu_reading);
	
	
	break;


        case IOCTL_GET_GYROZ:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_gyro_z);
	printk(KERN_INFO "GYROSCOPE data in z direction is - %d \n",imu_reading);
	
	
	break;


        case IOCTL_GET_COMPASSX:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_comp_x);
	printk(KERN_INFO "COMPASS data in x direction is - %d \n",imu_reading);
	
	
	break;


        case IOCTL_GET_COMPASSY:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_comp_y);
	printk(KERN_INFO "COMPASS data in y direction is - %d \n\n",imu_reading);
	
	
	break;


        case IOCTL_GET_COMPASSZ:
	temp_imu_reading = (int *)ioctl_param;
	get_user(ch_no,&temp_comp_z);
	printk(KERN_INFO "COMPASS data in z direction is - %d \n\n",imu_reading);
	
	
	break;

        case IOCTL_GET_ACCELEROMETERX:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_acc_x);
	printk(KERN_INFO "ACCELEROMETER data in x direction is - %d \n",imu_reading);
	
	
	break;

        case IOCTL_GET_ACCELEROMETERY:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_acc_y);
	printk(KERN_INFO "ACCELEROMETER data in y direction is - %d \n",imu_reading);
	break;


        case IOCTL_GET_ACCELEROMETERZ:
	temp_imu_reading = (int *)ioctl_param;
	get_user(imu_reading,&temp_acc_z);
	printk(KERN_INFO "ACCELEROMETER data in z direction is - %d \n",imu_reading);
	
	
	break;
	
	}
	
	return SUCCESS;
	}
	
	/* Module Declarations */
	
	/*
	*flie operations mapping to system calls
	*/
	struct file_operations fops = {
	.read = imu_read,
	.unlocked_ioctl = imu_ioctl,
	.open = imu_open,
	.release = imu_close, /* close */
	};


        int imu_init(void)
	{
	// reserve <major, minor>
	if (alloc_chrdev_region(&first, 0, 1, "imu") < 0)
	{
	return -1;
	}
	
	// dynamically create device node in /dev directory
	if ((cls = class_create(THIS_MODULE, "IMU")) == NULL)
	{
	unregister_chrdev_region(first, 1);
	return -1;
	}
	if (device_create(cls, NULL, first, NULL, DEVICE_NAME ) == NULL)
	{
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	return -1;
	}
	
	// Link fops and cdev to device node
	cdev_init(&c_dev, &fops);
	if (cdev_add(&c_dev, first, 1) == -1)
	{
	device_destroy(cls, first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	return -1;
	}
	
	printk(KERN_INFO "IMU device registered successfully\n");
	
	
	return 0;
	}
	
	/*
	* Cleanup - unregister the appropriate file from /proc
	*/
	int imu_exit(void)
	{
	
	cdev_del(&c_dev);
	device_destroy(cls, first);
	class_destroy(cls);
	unregister_chrdev_region(first, 1);
	printk(KERN_INFO "IMU device unregistered\n\n");
	
	return 0;
	
	}
	
	
	module_init(imu_init);
	module_exit(imu_exit);
	MODULE_LICENSE("GPL");
	
	
