        #ifndef IMU_DEV_H
	#define IMU_DEV_H
	
	#include <linux/ioctl.h>
	
	
	#define MAGIC_NUM 100
	
	
	#define IOCTL_GET_BAROMETER _IOW(MAGIC_NUM, 1, int *)

        #define IOCTL_GET_GYROX _IOW(MAGIC_NUM, 2, int *)
        #define IOCTL_GET_GYROY _IOW(MAGIC_NUM, 3, int *)
        #define IOCTL_GET_GYROZ _IOW(MAGIC_NUM, 4, int *)

        #define IOCTL_GET_COMPASSX _IOW(MAGIC_NUM, 5, int *)
        #define IOCTL_GET_COMPASSY _IOW(MAGIC_NUM, 6, int *)
        #define IOCTL_GET_COMPASSZ _IOW(MAGIC_NUM, 7, int *)

        #define IOCTL_GET_ACCELEROMETERX _IOW(MAGIC_NUM, 8, int *)
        #define IOCTL_GET_ACCELEROMETERY _IOW(MAGIC_NUM, 9, int *)
        #define IOCTL_GET_ACCELEROMETERZ _IOW(MAGIC_NUM, 10, int *)
        
        

        
        
	
	#define DEVICE_FILE_NAME "/dev/imu"
	
	#endif
