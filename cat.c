#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];


void
line_by_line(int fd)
{
  int n;
  int counter=1;
  while((n = read(fd, buf, sizeof(buf))) > 0) {
    printf("%d ",counter);
    for (int i=0;i<n;i++) //read all the character in buffer upto n
    { 
      printf("%c",buf[i]);  //printing what inside buf
      if(buf[i]=='\n')
      {//here is new line
        counter+=1;   
        if(i<n-1)//to avoid printing last /n
        printf("%d ",counter);        
      }
    }
}
}

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    
    if (write(1, buf, n) != n) {
      fprintf(2, "cat: write error\n");
      exit(1);
    }
  }
  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;

  int check=1;
  if(argc <= 1){
    cat(0);
    exit(0);
  }
  int n=strcmp(argv[1],"-n")//if n=0 mean -n entered
  if(argc>1)
	{
	if(!n)
	{
	check++;}
	}

  for(i = check; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    if(check==2)
    {
      line_by_line(fd);
    }
    else
    {
      cat(fd);
    }
    close(fd);
  }
  exit(0);
}
