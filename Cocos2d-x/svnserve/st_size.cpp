#include <cstdio>
#include <cstring>
using namespace std;

#if 1
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

int main(int argc, char **argv)
{
	char szp[100]={0};
	if(argc<2)
	{
		strcpy(szp,"/etc/hosts");
	}
	else
		strcpy(szp,argv[1]);

    struct stat buf;
    stat(szp, &buf);
    printf("%s file size = %d\n",szp, buf.st_size);

	return 0;
}