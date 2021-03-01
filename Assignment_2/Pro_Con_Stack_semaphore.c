#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>

const int max=10;
int stack[10];
int top=-1;
int item=1;
sem_t s1;
sem_t s2;

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

void* tentry_fun1(void* pv)	//consumer
{
	int i;
	printf("A--welcome\n");
	sem_wait(&s2);
	sem_wait(&s1);
	pop();
	sem_post(&s1);
	//pthread_exit(NULL);
}
void* tentry_fun2(void* pv)	//producer
{
	int i;
	printf("B--welcome\n");
	sem_wait(&s1);
	
    for(i=1;i<=max;i++)
	{
		push();
	}
    
	sem_post(&s1);
	sem_post(&s2);
	//pthread_exit(NULL);
}
int main()
{
	pthread_t pt1,pt2;	//thread handle
	sem_init(&s1,0,1);
	sem_init(&s2,0,0);
	pthread_create(&pt1,NULL,tentry_fun1,NULL);
	pthread_create(&pt2,NULL,tentry_fun2,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	sem_destroy(&s1);
	sem_destroy(&s2);
	printf("main--thank you\n");
	return 0;	//exit(0);
}

