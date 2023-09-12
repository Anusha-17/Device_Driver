#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include<sys/ioctl.h>
extern int user_open(const char *path, int oflag);
extern ssize_t user_read(int fd,void *buf,size_t count);
extern ssize_t user_write(int fd, const void *buf, size_t nbytes);
extern int user_close(int filedes);
