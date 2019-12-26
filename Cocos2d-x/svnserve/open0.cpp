#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
 int fd;
 char buf[512]={0}; 

 fd = open("open0.cpp", O_RDONLY);
 if (fd >= 0)
     read(fd, buf, sizeof(buf));
for(int i=0;i<512;i++)
    printf("%x ",buf[i]);
 return 0;
}