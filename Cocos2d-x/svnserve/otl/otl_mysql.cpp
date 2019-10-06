#define	OTL_ODBC			// Compile MySQL
//#define	OTL_ORA10G		// Compile OTL 4/OCI10G
#ifndef WIN32
#define OTL_ODBC_UNIX // uncomment this line if UnixODBC is used
#endif
#include "otlv4.h"		// include the OTL 4 header file
#include <iostream>
using namespace std;

otl_connect db;			// connect object

void insert()			// insert rows into table
{ 
	otl_stream wr
		(50,	// buffer size
		"insert into test_tab values(:f1<int>, :f2<char[7]>)", // SQL statement
		db		// connect object
		);

	char tmp[7];

	for (int i=1; i<=20; ++i)
	{
		sprintf(tmp, "Name%d", i);
		wr << i << tmp;
	}
}

void select()
{ 
	otl_stream rd
		(50,	 // buffer size
		"select * from test_tab where f1>=:n1<int> and f1<=:n2<int>",	// SELECT statement
		db		 // connect object
		); 

	rd << 8 << 16;

	int f1;
	char f2[7];

	while (!rd.eof())	// while not end-of-data
	{ 
		rd >> f1 >> f2;
		cout << "f1 = " << f1 << ", f2 = " << f2 << endl;
	}
}

int main()
{
	otl_connect::otl_initialize();		// initialize OTL environment

	try
	{
	//db.rlogon("root/123456@127.0.0.1:3306/test"); // 用户/密码@数据库名
        db.rlogon("root/123456@MySql");

		otl_cursor::direct_exec
			(db,
			"drop table test_tab",
			otl_exception::disabled			// disable OTL exceptions
			); // drop table

		otl_cursor::direct_exec
			(
			db,
			"create table test_tab(f1 int, f2 varchar(6))"
			);  // create table

		insert(); // insert records into table
		select(); // select records from table

	}
	catch (otl_exception& e)	    // intercept OTL exceptions
	{
		cerr << "ERROR: code[" <<e.code<<"]\n";
		cerr << e.msg << endl;		// print out error message
		cerr << e.stm_text << endl; // print out SQL that caused the error
		cerr << e.var_info << endl; // print out the variable that caused the error
	}
	db.logoff();				    // disconnect from Oracle

	return 0;
}
