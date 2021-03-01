#include<stdio.h>
#include<unistd.h>
int main()
{
    int ret;
    
    char *c="gcc";
    char *c2="test.c";
    char *c3="test.o";
    char *c4="-o p2.out";
    
    ret=fork();
    if(ret<0)
    {
        printf("error in creating child process\n");
        exit(0);
    }

    if(ret==0)
    {
        int k=execlp(c,c,c2,"-c",NULL);
        if(k<0)
        {
            printf("error in exec\n");
        }
    }
    else
    {
        int status=waitpid(-1,&status,NULL);
        printf("in main");
        int ret2=fork();
        if(ret2==0)
        {
            int k=execlp(c,c,c3,c4,NULL);
              if(k<0)
        {
            printf("error in exec\n");
        }
        }
        else
        {

        }
    }
}