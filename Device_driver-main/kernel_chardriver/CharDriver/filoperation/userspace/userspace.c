
#include"shared.h"
 
#define WR_VALUE _IOW('a','a',int32_t*)
#define RD_VALUE _IOR('a','b',int32_t*)

int8_t write_buf[1024];
int8_t read_buf[100];

int main()
{
        int fd;
        char option;
        printf("*********************************\n");
        printf("*******userspace application*******\n");

        fd = user_open("/dev/char_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
		 printf("       3. IoctlRead             \n");
		 printf("       4. IoctlWrite             \n");
                printf("        5. Exit                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                
                switch(option) {
                        case '1':
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                user_write(fd, write_buf, strlen(write_buf)+1);
                                break;
                        case '2':
                                printf("Data Reading ...");
                                user_read(fd, read_buf, 100);
                                printf("Read data from kernel =  %s\n", read_buf);
                                break;
			case '3':
                                printf("Data Reading ...");
                                ioctl(fd, RD_VALUE, (int32_t*)read_buf);
                                printf("Read data from kernel =  %s\n", read_buf);
                                break;

 			case '4':
                                printf("Enter the string to write into driver :");
                                scanf("  %[^\t\n]s", write_buf);
                                ioctl(fd, WR_VALUE, (int32_t*) write_buf); 
                                break;

                        case '5':
                                user_close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}
