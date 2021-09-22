	#include <stdio.h>
	#include <stdlib.h>
	#include <fcntl.h> /* open */
	#include <unistd.h> /* exit */
	#include <sys/ioctl.h> /* ioctl */
	#include<stdint.h>
        #include "imu_dev.h" 


	int ioctl_get_barometer(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_BAROMETER, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	
	return 0;
	}
	
	int ioctl_get_gyrox(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_GYROX, out);
	
	if (ret_val < 0) {
        printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	
	return 0;
	}

        int ioctl_get_gyroy(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_GYROY, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	
	return 0;
	}

        int ioctl_get_gyroz(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_GYROZ, out);
	
	if (ret_val < 0) {
       printf("ioctl got no data:%d\n", ret_val);

	exit(-1);
	}
	
	return 0;
	}

        int ioctl_get_compassx(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_COMPASSX, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	
	return 0;
	}

        int ioctl_get_compassy(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_COMPASSY, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	
	return 0;
	}

        int ioctl_get_compassz(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_COMPASSZ, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	
	return 0;
	}
	
        int ioctl_get_accelerometerx(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_ACCELEROMETERX, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	return 0;
	}

        int ioctl_get_accelerometery(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_ACCELEROMETERY, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	return 0;
	}

        int ioctl_get_accelerometerz(int file_desc, int *out)
	{
	int ret_val;
	
	ret_val = ioctl(file_desc, IOCTL_GET_ACCELEROMETERZ, out);
	
	if (ret_val < 0) {
	printf("ioctl got no data:%d\n", ret_val);
	exit(-1);
	}
	return 0;
	}
	
	
	int main()
	{
	int file_desc, ret_val;
	int param_no;
	int imu_reading;
	uint16_t IMU_out;
	
	
	
	file_desc = open(DEVICE_FILE_NAME, 0);
	if (file_desc < 0) {
	printf("Can't open device file: %s\n", DEVICE_FILE_NAME);
	exit(-1);
	}
	
	
	printf("Select a parameter to read from 1 to 10 : ");
	scanf("%d",&param_no); //SELECT PARAMETER
	
	printf("Channel selected : %d\n",param_no);
	if(param_no<1||param_no>10)
	{
	printf("invalid channel selection\n");
	return 0;
	}
	
	ioctl_get_barometer(file_desc,&param_no);
        ioctl_get_gyrox(file_desc,&param_no);
        ioctl_get_gyroy(file_desc,&param_no);
        ioctl_get_gyroz(file_desc,&param_no);
        ioctl_get_compassx(file_desc,&param_no);
        ioctl_get_compassy(file_desc,&param_no);
        ioctl_get_compassz(file_desc,&param_no);
        ioctl_get_accelerometerx(file_desc,&param_no);
        ioctl_get_accelerometery(file_desc,&param_no);
        ioctl_get_accelerometerz(file_desc,&param_no);

	read(file_desc,&IMU_out,2); //reading values from device(IMU) file
        read(file_desc,&IMU_out,3);
        read(file_desc,&IMU_out,4);
        IMU_out = IMU_out>>6;
	printf("The IMU data from parameter no. %d is = %d\n",param_no,IMU_out);
	
	
	close(file_desc);
	return 0;
	}
