#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/ioctl.h>

#define GPIO_SELECT_LED _IOW('a',1,int);

int main()
{
	int fd = -1, i;
	ssize_t ret;
	int option;
	char my_buf[12]="Hello world";
	
	fd = open( "/dev/my_Char_driver", O_RDWR );
	if(fd<0)
		printf("failed acquiring file descriptor return status %d\n",fd);
	
	do{
		printf("1. getting the led status \n");
		printf("2. Setting the led status \n");
		printf("3. Close \n");
		printf("0. Exit\n");
		printf("Enter the options\n");
		scanf("%d",&option);
		getchar();
	
		switch(option)
		{
			case '0':
	 			break;
			case '1':
				/* write the contents of my buffer into the device */
				ret= read(fd,&i,1);
				if(count == -1)
					printf("operation is failed \n");
				else	
					printf("LED value %d\n",i);
				printf("\n");
				break;
			case '2':
				printf("enter your option o - off 1 - on \n");
				c = getchar();
				i = write(fd.&i,1)
				if(i==-1){
					printf("led operation write failed\n");
					break;
				}
				break;
			case '3':
				close(fd);
				fd = -1 ;
				break;
			default:
				printf("invalid opeartion\n")
				break;
		}
	}while(option!=0);
return 0;
}
	
