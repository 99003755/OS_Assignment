#include<unistd.h>
#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/mman.h>
#include<stdlib.h>

#define max_size 100

int stack[max_size];
int top=-1;
int  *stackptr;

void producer();
void consumer();

int main()
{
	int ret,i,max=10,status;
	sem_t *ps,*qs;
    void *ptr;
	ps=sem_open("/s1",O_CREAT, 0666, 1);
	qs=sem_open("/s2",O_CREAT, 0666, 0);
	ptr=mmap(0,4096, PROT_WRITE|PROT_READ, MAP_SHARED|MAP_ANONYMOUS,-1,0);
	
	if(stackptr==MAP_FAILED)
	{
		printf("\nmap failed");
		return -1;
	}
	ret=fork();
	if(ret==0)
	{
		sem_wait(ps);
		for(i=1;i<=max;i++)
		{
			producer();
		}
		sem_post(ps);
		sem_post(qs);
		exit(0);
	}
	else	//ret>0
	{
        sem_wait(qs);
	    sem_wait(ps);	
        for(i=1;i<=max;i++)
		{
			consumer();
		}
		sem_post(ps);
		waitpid(-1,&status,0);
		sem_unlink("s1");
		sem_unlink("s2");
	}
	return 0;
}
void producer()
{
    top++;
	int i=0;
	int data[]={1,2,3,4,5,6,7,8,9,10};
	stackptr=data[i];

    printf("The producer element is %d\n",*stackptr);  
	i++; 
}
void consumer()
{
    printf("The consumer element is %d\n",(*stackptr));
    top--;
}
/** TODO:- locate named semaphore in /dev/shm before unlinking */
