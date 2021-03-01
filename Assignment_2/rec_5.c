#include<mqueue.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(char argc,char *argv[])
{
 pid_t ret;
 pid_t cpid;
 int max_size =100;
 char cmd[max_size];
 	int ret1,nbytes;
	struct mq_attr attr;
	attr.mq_msgsize=256;
	attr.mq_maxmsg=10;
	mqd_t mqid;
	mqd_t mqid1;
	mqid=mq_open("/mque",O_RDONLY|O_CREAT,0666,&attr);
	
		if(mqid<0)
	{
		perror("mq_open");
		exit(1);
	}
	char buf[8192];
	char send[8192];
	int maxlen=256,prio;
	nbytes=mq_receive(mqid,buf,maxlen,&prio);
	printf("nbytes %d\n",nbytes);
	if(nbytes<0)
	{
		perror("mq_recv");
		exit(2);
	}
	buf[nbytes]='\0';
	printf("receive msg:%s,nbytes=%d,prio=%d\n",buf,nbytes,prio);
	
 ret=fork();
  if(ret==0)
 {
printf("receive msg:%s,nbytes=%d,prio=%d\n",buf,nbytes,prio);
int k;
 argv[0]=buf;
 k=execlp(buf, argv,NULL);
 if(k<0)
 {
 perror("execl");
 exit(1);
 }
 
 }
 if(ret>0)
 {
 pid_t status;
 cpid=waitpid(-1,&status,NULL);
 printf("\nExit status %d",status);
 exit(0);
 }
 else
 {
 perror("Process doesn't exist");
 exit(3);
 }
 }
 
