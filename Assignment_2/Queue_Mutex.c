#include<pthread.h>
#include<stdio.h>
#include<semaphore.h>
#include<stdlib.h>

int rear=-1;
int front=-1;  
const int size=10;
int *arr;
pthread_mutex_t m1=PTHREAD_MUTEX_INITIALIZER;
sem_t s1;

void enQueue(int value);
int deQueue();

void* mfun1(void* pv)		//producer
{
	int i;
	
	printf("A--welcome\n");
	pthread_mutex_lock(&m1);

    enQueue(15);

	pthread_mutex_unlock(&m1);
	sem_post(&s1);
	//pthread_exit(NULL);
}

void* mfun2(void* pv)		//consumer
{
	int i;
	printf("B--welcome\n");
	sem_wait(&s1);			//changing sequence lead to deadlock
	pthread_mutex_lock(&m1);
	
    int data=deQueue();
    printf("\nData %d:",data);
	

	pthread_mutex_unlock(&m1);
	//pthread_exit(NULL);
}

int main()
{
	printf("main--Welcome\n");
	pthread_t pt1,pt2;	//thread handles
	sem_init(&s1,0,0);
	pthread_create(&pt1,NULL,mfun1,NULL);
	pthread_create(&pt2,NULL,mfun2,NULL);
	pthread_join(pt1,NULL);
	pthread_join(pt2,NULL);
	sem_destroy(&s1);
	pthread_mutex_destroy(&m1);
	printf("\nmain--Thank you\n");
	return 0;
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
