#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)
 
int main()
{
        int fd;
        int32_t value, number;
        printf("*******Userspace application*******\n");
 
        printf("\nOpening Driver....\n");
        fd = open("/dev/ts_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }
 
		while(1)
		{
			printf("--------------------------------------------\n");
			printf(" 1.Read\n 2.Write\n 3.Exit\n");
			printf("Enter the IOCTL operation to perform:");
			scanf("%d",&number);
			
			switch(number)
			{
				case 1:
					printf("Reading Value from Driver\n");
					ioctl(fd, RD_VALUE, (int32_t*) &value);
					printf("Value is %d\n", value);
					break;
				case 2:
					printf("Enter the Value to send\n");
					scanf("%d",&value);
					printf("Writing Value to Driver\n");
					ioctl(fd, WR_VALUE, (int32_t*) &value); 
					break;
				case 3:
					printf("Closing Driver\n");
					close(fd);
					return 0;
				default:
					printf("Enter between 1-3 \n");
				
			}
		}
        return 0;
}
