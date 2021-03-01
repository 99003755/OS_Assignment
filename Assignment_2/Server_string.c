#include<mqueue.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
	int ret,nbytes;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	mqd_t mqid;
	mqid=mq_open("/mstr",O_RDONLY|O_CREAT,0666,&attr);
	if(mqid<0)
	{
		perror("mq_open");
		exit(1);
	}
	char buf[8192];
    char buf1[8192];
	int maxlen=256,prio;
    int re;
	nbytes=mq_receive(mqid,buf,maxlen,&prio);
	if(nbytes<0)
	{
		perror("mq_recv");
		exit(2);
	}
	buf[nbytes]='\0';
	printf("receive msg:%s,nbytes=%d,prio=%d\n",buf,nbytes,prio);
	//write(1,buf,nbytes);

    for (int i=0; buf[i]!='\0'; i++)
    {
        if (buf[i]>='A' && buf[i]<='Z')
            buf1[i] = buf[i] + 'a' - 'A';
        else if (buf[i]>='a' && buf[i]<='z')
            buf1[i] = buf[i] + 'A' - 'a';
    }
    printf("\nTOGGLE:%s",buf1);
    int len=strlen(buf1);
    re=mq_send(mqid,buf1,len+1,NULL);
	if(ret<0)
	{
		perror("mq_send");
		exit(2);
	}
	mq_close(mqid);
	return 0;
}

