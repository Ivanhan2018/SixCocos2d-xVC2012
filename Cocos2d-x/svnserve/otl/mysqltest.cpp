#include <stdio.h>
#include <mysql.h>
 
int main(int argc,char *argv[])
{
     MYSQL conn;
     int res;
     mysql_init(&conn);
     if(mysql_real_connect(&conn,"192.168.199.144","root","123456","test",0,NULL,CLIENT_FOUND_ROWS))
     {
     printf("connect success!\n");
     res=mysql_query(&conn,"insert into test values('user','123456')");
     if(res)
     {
        printf("error\n");
     }
     else
     {
        printf("OK\n");
     }
     mysql_close(&conn);
     }
     return 0;
}