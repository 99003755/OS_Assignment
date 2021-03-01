#include<pthread.h>
#include<semaphore.h>
#include<stdio.h>

const int max=10;
int stack[10];
int top=-1;
int item=1;
pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
sem_t s1;

void push()
{
	top++;
	printf("\n%d Added to stack",item);
	stack[top]=item;
	item++;
}

void pop()
{
	if(top==-1)
	{
		printf("EMPTY");
	}
	printf("\nITEM POPPED %d", stack[top]);
	top--;
}

void* efun1(void* pv)		//producer
{
	int i;
	
	printf("A--welcome\n");
	pthread_mutex_lock(&m1);
	for(i=1;i<=max;i++)
	{
    	push();
	}
	pthread_mutex_unlock(&m1);
	sem_post(&s1);
	//pthread_exit(NULL);
}
void* efun2(void* pv)		//consumer
{
	int i;
	printf("B--welcome,waiting for semaphore\n");
	sem_wait(&s1);			//changing sequence lead to deadlock
	pthread_mutex_lock(&m1);
	pop();
	pthread_mutex_unlock(&m1);
	//pthread_exit(NULL);
}





int main()
{
	printf("main--Welcome\n");
	pthread_t pt1,pt2;	//thread handles
	sem_init(&s1,0,0);
	pthread_create(&pt1,NULL,efun1,NULL);
	pthread_create(&pt2,NULL,efun2,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	sem_destroy(&s1);
	pthread_mutex_destroy(&m1);
	printf("\nmain--Thank you\n");
	return 0;
}





