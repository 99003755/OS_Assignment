#include<unistd.h>
#include<stdio.h>

int main()
{
	pid_t ret;
	printf("welcome...pid=%d\n",getpid());
    char c1[100]="ls",c2[100],c3[100]="-l",c4[100],c5[100];
     printf("enter one command\n");
       gets(c1);
       gets(c3);
	   gets(c4);
	   gets(c5);
	   	ret=fork();
	if(ret<0)
	{
		perror("fork");
		exit(1);
	}
	if(ret==0)
	{
		printf("child-1-hello,pid=%d,ppid=%d\n",
				getpid(),getppid());
		int k=execlp(strcpy(c2,c1), strcpy(c2,c1),NULL);
		if(k<0)
		{
            printf("\nerror\n");
			perror("execv");
			exit(1);
		}
	}
	else		//ret>0
	{
		printf("parent--hello,pid=%d,ppid=%d\n",
				getpid(),getppid());
				int ret1=fork();
		if(ret1==0)
		{
		printf("child-2-hello,pid=%d,ppid=%d\n",
				getpid(),getppid());
		int k=execlp(strcpy(c2,c3), strcpy(c2,c3),NULL);
		if(k<0)
		{
            printf("\nerror\n");
			perror("execv");
			exit(1);
			}
		}
		else
		{
			if(fork()==0)
			{
				int k=execlp(strcpy(c2,c4), strcpy(c2,c4),NULL);
				if(k<0)
				{
            		printf("\nerror\n");
					perror("execv");
					exit(1);
				}
			}
			else{
				if(fork()==0)
				{
					int k=execlp(strcpy(c2,c5), strcpy(c2,c5),NULL);
				if(k<0)
				{
            		printf("\nerror\n");
					perror("execv");
					exit(1);
				}
				}
				else{
					printf("\n4th ccommand\n");
				}
				printf("\n3rd command\n");
			}
		}
		}
	printf("Thank you..pid=%d\n",getpid());
	return 0;
}