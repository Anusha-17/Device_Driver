#include "shared.h"
#include<stdio.h>
int user_open(const char *path, int flag)
{
        return(open(path,flag));
}
ssize_t user_read(int fd,void *buf,size_t count)
{
	return (read(fd,buf,count));
}
ssize_t user_write(int fd, const void *buf, size_t nbytes)
{
	return(write(fd,buf,nbytes));
}
int user_close(int filedes)
{
	return(close(filedes));
}

