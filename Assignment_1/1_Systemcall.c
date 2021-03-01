#include <fcntl.h> 
#include<string.h>
int main(int arg,char* argc[]) 
{ 
  int fd, sz; 
  char *c = (char *) calloc(100, sizeof(char)); 
  printf("\n%s\n%s",argc[1],argc[2]);
  fd = open(argc[1], O_RDONLY); 
  if (fd < 0) { 
    perror("r1"); 
  exit(1); 
  }
  
  sz = read(fd, c, 100); 
  c[sz] = '\0'; 
  printf("file data: % s\n", c); 
   
  int fd1 = open(argc[2], O_WRONLY | O_CREAT | O_TRUNC, 0644); 
  printf("file created\n");

   int k=write(fd1,c,strlen(c));

  // printf("data written\n");
  free(c);
   close(fd);
}

