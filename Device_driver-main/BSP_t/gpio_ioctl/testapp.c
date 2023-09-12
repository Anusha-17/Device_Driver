#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>

//#define MAX_SIZE 1024
//int8_t write_buf[MAX_SIZE];
//int8_t read_buf[MAX_SIZE];

#define set_clear_VALUE _IOW('a','a',int*)
 
//#define RD_VALUE _IOR('a','b',int*)


int main()
{
	int fd;
	char option;
	int number = 0, value = 0;
	fd = open("/dev/my_gpio_driver",O_RDWR);
	if(fd <0)
	{
		perror("can not open device:: ");
		return 0;
	}
	
	while(1)
	{
		printf("****Please Enter the Option******\n"); 
		printf("        1. Write               \n");
		printf("        2. Read                 \n");
		printf("		3. IOCTL				\n");
		printf("        4. Exit                 \n");
		printf("*********************************\n");
		scanf(" %c", &option);
		printf("Your Option = %c\n", option);
		
		switch(option)
		{
			case '1':
				write(fd, NULL, 0);
				printf("Write part Done!\n");
				break;
			case '2':
			   printf("Data Reading ...");
			   read(fd, NULL, 0);
			   printf("Read part Done !\n\n");
			   break;
			case '3':
				printf("Enter Value 0 to clear and 1 to set the pin\n"); 
				scanf("%d",&number);
				printf("Writing Value to Driver\n");
				ioctl(fd, set_clear_VALUE , (int32_t*) &number); 
				break;
		   	case '4':
				   close(fd);
				   exit(1);
				   break;
		   	default:
				   printf("Enter Valid option = %c\n",option);
				   break;
		}
	
	}
	close(fd);
}
