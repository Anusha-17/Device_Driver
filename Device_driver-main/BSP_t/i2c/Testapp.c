#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

#define MAX_SIZE 1024
//int8_t write_buf[MAX_SIZE];
int8_t read_buf[MAX_SIZE];


int main()
{
	int fd;
	char option;
	int number = 0, value = 0;
	fd = open("/dev/bmp280_device",O_RDWR);
	if(fd <0)
	{
		printf("can not open device");
		return 0;
	}
	
	while(1)
	{
		printf("****Please Enter the Option******\n"); 
		printf("        1. Read                 \n");		
		printf("        2. Exit                 \n");
		printf("*********************************\n");
		scanf(" %c", &option);
		printf("Your Option = %c\n", option);
		
		switch(option)
		{
			
			case '1':
			   printf("Data Reading ...");
			   read(fd, read_buf, MAX_SIZE);
			   printf("Done!\n\n");
			   printf("Data = %s\n\n", read_buf);
			   break;
			case '2':
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
