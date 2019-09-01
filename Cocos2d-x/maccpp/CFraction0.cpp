//#include "stdafx.h"
#include <stdlib.h>
#include "CFraction.h"

int main(int argc, char* argv[])
{
	CFraction a(7, 32);
	CFraction b(13, 32);
	a.Show();
	b.Show();
	CFraction c=a+b;
	c.Show();
	c=a-b;
	c.Show();
	c=a*b;
	c.Show();
	c=a/b;
	c.Show();

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}

