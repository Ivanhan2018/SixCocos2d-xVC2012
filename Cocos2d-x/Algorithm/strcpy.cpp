#include <stdio.h>
#include <stdlib.h> 
#include <assert.h>

//abcdefghi
char* strcpy(char *dest, const char *src)
{
    assert((dest!=NULL)&&(src!=NULL));
    char* p = dest;
    while ((*dest++=*src++)!='\0') ;
    return p;
}

int main(void) 
{ 
    char string[10]; 
    char *str1 = "abcdefghi"; 

    strcpy(string, str1); 
    printf("%s\n", string);
	
#ifdef _MSC_VER
    system("pause");
#endif
    return 0; 
}



