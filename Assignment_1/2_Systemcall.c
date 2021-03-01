#include <fcntl.h> 
#include<stdio.h>
int main() 
{ 
  int fd, sz; 
  char *c = (char *) calloc(100, sizeof(char)); 
  
  fd = open("foo.txt", O_RDONLY); 
  if (fd < 0) { perror("r1"); exit(1); } 
  
  sz = read(fd, c, 100); 
  c[sz] = '\0'; 
 //printf("file data: % s\n", c); 
 int words_count=0,line_count=0,i=0;
 int inword;
 for(i=0;i<strlen(c);i++)
 {
         if(c == ' ' || c == '\t' || c == '\n' || c == '\0')
        {
            if(inword)
            {
                inword=0;
                words_count++;
            }
        }
     if(c[i]=='\n')
        line_count++;
    else 
        inword=1;


 }
    printf("\ntotal no lines %d\ntotal no of words %d\ntotal no of characters: %d\n",line_count,words_count,i);
    close(fd);
}