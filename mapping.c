#include "user/user.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"


int main()
{
    int fd = 0;
    struct stat *myStat = 0;
    fstat(fd, myStat);
    fd = open("README.txt", O_RDWR);
    printf("The starting address is %d\n" , mmap(0,myStat->size , 2,1,fd, 0));
    return 0;
}