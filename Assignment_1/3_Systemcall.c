#include<stdio.h>
#include<signal.h>
#include <unistd.h>

void sig_handler(int signum)
{
    printf("inside signal handler\t%d\n",signum);
}

int main()
{
    pid_t pid;
    signal(SIGUSR1,sig_handler);
    printf("registered the signal\n");
    pid=getpid();
    int c=kill(pid,SIGUSR1);
    printf("\nafter sending the signal %d\n",c);
    return 0;
}




/*#include<stdio.h>
#include<signal.h>

void sig_handler(int signum){
  printf("Inside handler function\n");
}

int main(){
  signal(SIGUSR1,sig_handler); // Register signal handler
  printf("Inside main function\n");
  raise(SIGUSR1);
  printf("Inside main function\n");
  return 0;
}*/