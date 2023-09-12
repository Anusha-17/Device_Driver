
#include<stdio.h>
#include<unistd.h>

int main()
{

	int p_id = getpid();
	printf("pid = %d\n",p_id);
	
	while(1);
	
}



