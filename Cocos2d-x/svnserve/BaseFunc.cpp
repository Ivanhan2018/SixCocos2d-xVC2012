#include <stdarg.h>
#include "BaseFunc.h"

int CBaseFunc::ston( const string& s )
{
	int n;
	ston( s, n );
	return n;
}

void CBaseFunc::stovs( const string& s, const string& sp, vector<string>& sa )
{
	sa.clear();
	if (sp.length() == 0) return;
	if (s.length() == 0)
	{
		/*sa.push_back("");*/
		return;
	}

	size_t szsp = sp.length();
	string tmps = s + sp;
	size_t start = 0;
	while( true )
	{
		if( tmps.length() < sp.length() )
		{
			break;
		}
		if( tmps.length() < start + sp.length() )
		{
			break;
		}

		size_t idx = tmps.find_first_of( sp[0], start );
		string sub = tmps.substr( idx, szsp );
		if( sub == sp )
		{
			string item = tmps.substr( 0, idx );
			sa.push_back( item );
			start = 0;
			tmps = tmps.substr( idx + szsp, tmps.length() - ( idx + szsp ) );
		}
		else
		{
			start += idx;
		}
	}
}

void CBaseFunc::vstos( const vector<string>& vs, const string& sp, string& s )
{
	s = "";
	if( vs.size() == 0 ) return ;
	s += vs[0];
	for ( size_t i = 1; i < vs.size(); i++ )
	{
		s += sp;
		s += vs[i];
	}
}

void CBaseFunc::md_stovs( const string& s, vector<string>& vs )
{
	if ( s == "" ) return;
	string sp = s.substr( 0, 1 );
	string tmp = s.substr( 1, s.length() - 1 );
	stovs( tmp, sp, vs );
}

void CBaseFunc::md_vstos( const vector<string>& vs, const string& sp, string& s )
{
	vstos( vs, sp, s );
	s = sp + s;
}

std::string   CBaseFunc::replace(std::string   &str,   const   char   *string_to_replace,   const   char   *new_string)
{
    //   Find   the   first   string   to   replace
    int   index   =   str.find(string_to_replace);
    //   while   there   is   one
    while(index   !=   std::string::npos)
    {
        //   Replace   it
        str.replace(index,   strlen(string_to_replace),   new_string);
        //   Find   the   next   one
        index   =   str.find(string_to_replace,   index   +   strlen(new_string));
    }
    return   str;
}
