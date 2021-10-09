#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<errno.h>
#include<termios.h>
#include<unistd.h>

#define IMU_PORT "/dev/imu"    

void parse_imu_data(unsigned char arr[]);

int main(void)
{
    unsigned char read_buf [2000];
    struct termios imu_port_settings;
    int imu_port;
    imu_port = open(IMU_PORT, O_RDWR | O_NOCTTY);

    if (imu_port < 0)
    {
        printf("Error %i from open: %s, IMU port closed\n", errno, strerror(errno));
        close(imu_port);
        return -1;
    }
    else
    {
        printf("IMU Port opened Successfully\n");
    }

    if (tcgetattr(imu_port, &imu_port_settings) != 0)
    {
        printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
        return -1;
    }

    cfsetispeed(&imu_port_settings, B2000000);
    cfsetospeed(&imu_port_settings, B2000000);

    imu_port_settings.c_cflag &= ~PARENB;
    imu_port_settings.c_cflag |=  CSTOPB;
    imu_port_settings.c_cflag &= ~CSIZE;
    imu_port_settings.c_cflag |=  CS8;    

    if (tcsetattr(imu_port, TCSANOW, &imu_port_settings) != 0)
    {
        printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
        return -1;
    }
  
   while (1)
        {
            int n = read(imu_port, &read_buf, sizeof(read_buf) - 1);
	
	        if (n >= 0) {
	        read_buf[n] = '\0';
    	}
	
	else
        {
            printf("Error reading data from the port\n");
            return -1;
        }
        parse_imu_data(read_buf);
    }

    return 0;
}


void parse_imu_data(unsigned char imu_data[])
{
    char *str = imu_data;
    char* strmem;
    char* accX = strtok_r(imu_data, " ,;AGMEQR:", &strmem);
    char* accY = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* accZ = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* gyroX = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* gyroY = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* gyroZ = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* magX = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* magY = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* magZ = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* eulerX = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* eulerY = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* eulerZ = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* QuaternionX = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* QuaternionY = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* QuaternionZ = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* QuaternionW = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* yaw = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* pitch = strtok_r(NULL, " ,;AGMEQR:", &strmem);
    char* roll = strtok_r(NULL, " ,;AGMEQR:", &strmem);

    if (accX != NULL && accY != NULL && accZ != NULL && gyroX != NULL && 
	gyroY != NULL && gyroZ != NULL && magX != NULL && magY != NULL && 
	magZ != NULL && eulerX != NULL && eulerY != NULL && eulerZ != NULL
	&& QuaternionX != NULL && QuaternionY != NULL && QuaternionZ != NULL &&
	QuaternionW != NULL && yaw != NULL && pitch != NULL && roll != NULL){
        
        printf("accX = %s\n", accX); 
	    printf("accX = %s\n", accX);
        printf("accY = %s\n", accY);
        printf("accZ = %s\n", accZ);
        printf("gyroX = %s\n", gyroX);
        printf("gyroY = %s\n", gyroY);
        printf("gyroZ = %s\n", gyroZ);
        printf("magX = %s\n", magX);
        printf("magY = %s\n", magY);
        printf("magZ = %s\n", magZ);
        printf("eulerX = %s\n", eulerX);
        printf("eulerY = %s\n", eulerY);
        printf("eulerZ = %s\n", eulerZ);
        printf("QuaternionX = %s\n", QuaternionX);
        printf("QuaternionY = %s\n", QuaternionY);
        printf("QuaternionZ = %s\n", QuaternionZ);
        printf("QuaternionW = %s\n", QuaternionW);
        printf("yaw = %s\n", yaw);
        printf("pitch = %s\n", pitch);
        printf("roll = %s\n", roll);
     }
}