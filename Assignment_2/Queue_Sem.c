#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>
sem_t s1;
sem_t s2;
  
int rear=-1;
int front=-1;  
const int size=10;
int *arr;

void enQueue(int value);
int deQueue();
  
void* tentry_fun1(void* pv)	//pull
{
	int i;
	printf("A--welcome\n");
	sem_wait(&s2);
	sem_wait(&s1);

	enQueue(5);

	sem_post(&s1);
	//pthread_exit(NULL);
}


void* tentry_fun2(void* pv)	//push
{
	int i;
	printf("B--welcome\n");
	sem_wait(&s1);
	
	int data=deQueue();
    printf("\nData %d:",data);
	
    sem_post(&s1);
	sem_post(&s2);
	//pthread_exit(NULL);
}

int main()
{
    arr=malloc(sizeof(int)*5);

	pthread_t pt1,pt2;
	sem_init(&s1,0,1);
	sem_init(&s2,0,0);	//thread handle

	pthread_create(&pt1,NULL,tentry_fun1,NULL);
	pthread_create(&pt2,NULL,tentry_fun2,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	sem_destroy(&s1);
	return 0;	//exit(0);
}

void enQueue(int value) 
{ 
    if ((front == 0 && rear == size-1) || 
            (rear == (front-1)%(size-1))) 
    { 
        printf("\nQueue is Full"); 
        return; 
    } 
  
    else if (front == -1) /* Insert First Element */
    { 
        front = rear = 0; 
        arr[rear] = value; 
    } 
  
    else if (rear == size-1 && front != 0) 
    { 
        rear = 0; 
        arr[rear] = value; 
    } 
  
    else
    { 
        rear++;
        arr[rear] = value; 
    } 
} 
  
// Function to delete element from Circular Queue 
int deQueue() 
{ 
    if (front == -1) 
    { 
        printf("\nQueue is Empty"); 
        return -1; 
    } 
  
    int data = arr[front]; 
    arr[front] = -1; 
    if (front == rear) 
    { 
        front = -1; 
        rear = -1; 
    } 
    else if (front == size-1) 
        front = 0; 
    else
        front++; 
  
    return data; 
}
