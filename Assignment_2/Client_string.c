#include<mqueue.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int ret;
	mqd_t mqid;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	mqid=mq_open("/mstr",O_WRONLY|O_CREAT,0666,&attr);
	//mqid=mq_open("/mque",O_WRONLY|O_CREAT,0666,NULL);
	if(mqid<0)
	{
		perror("mq_open");
		exit(1);
	}
	char str[]="HeLlO";
	int len=strlen(str);
	ret=mq_send(mqid,str,len+1,NULL);
	if(ret<0)
	{
		perror("mq_send");
		exit(2);
	}
/*    
#if 1
	char str1[]="Message with pri =10";
	len=strlen(str1);
	ret=mq_send(mqid,str1,len,10);
	if(ret<0)
	{
		perror("mq_send");
		exit(2);
	}
	#endif
    */
	mq_close(mqid);
	return 0;
}

