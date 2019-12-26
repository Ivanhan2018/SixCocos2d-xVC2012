#pragma once
#ifndef _BASE_FUNC_H_
#define _BASE_FUNC_H_

#include <string>
#include <vector>
#include <map>
#if(defined(linux)||defined(ANDROID))
#include <stdlib.h>
#include <string.h>
#endif
using namespace std;

//////////////////////////////////////////////////////////////////////////
// 获取格式化字符串
extern char* GetFormatString(const char* lpFormat, ...);

class CBaseFunc
{
public:
	CBaseFunc(){}
	virtual ~CBaseFunc(){}

public:
	template<class TNUM> static void ston( const string& s, TNUM& n );
	template<class TNUM> static void ntos( TNUM n, string& s );
	static int ston( const string& s );
	template<class TNUM> static char* ntos( TNUM n );

	template<class TNUM> static void vstovn( const vector<string>& vs, vector<TNUM>& vn );
	template<class TNUM> static void vntovs( const vector<TNUM>& vn, vector<string>& vs );
	static void  stovs( const string& s, const string& sp, vector<string>& sa );
	template<class TNUM> static void stovn( const string& s, const string& sp, vector<TNUM>& sa );
	static void vstos( const vector<string>& vs, const string& sp, string& s );
	template<class TNUM> static void vntos( const vector<TNUM>& vn, const string& sp, string& s );
	
	static void md_stovs( const string& s, vector<string>& vs );
	template<class TNUM> static void md_stovn( const string& s, vector<TNUM>& vn );
	static void md_vstos( const vector<string>& vs, const string& sp, string& s );
	template<class TNUM> static void md_vntos( const vector<TNUM>& vn, const string& sp, string& s );

	template<class TNUM, class TNUM2> static void vct_arr( const vector<TNUM>& vn, TNUM arr[], TNUM2& cnt );
	template<class TNUM, class TNUM2> static void arr_vct( const TNUM arr[], TNUM2 cnt, vector<TNUM>& vn );
    
    static string replace(string &str, const char *string_to_replace, const char *new_string);
};

template<class TNUM> 
	void CBaseFunc::ston( const string& s, TNUM& n )
{
	if ( s == "" )
	{
		n = 0;
	}
	n = atoi( s.c_str() );
}

template<class TNUM> 
	void CBaseFunc::ntos( TNUM n, string& s )
{
	s = ntos( n );
}

template<class TNUM> 
	char* CBaseFunc::ntos( TNUM n )
{
	return GetFormatString( "%d", n );
}

template<class TNUM>
void	CBaseFunc::stovn( const string& s, const string& sp, vector<TNUM>& sa )
{
	sa.clear();
	vector<string> tmpsa;
	stovs( s, sp, tmpsa );

	for( size_t i = 0; i < tmpsa.size(); i++ )
	{
		sa.push_back( atoi( tmpsa[i].c_str() ) );
	}
}

template<class TNUM>
void CBaseFunc::vstovn( const vector<string>& vs, vector<TNUM>& vn )
{
	vn.clear();
	for ( size_t i = 0; i < vs.size(); i++ )
	{
		vn.push_back( atoi( vs[i].c_str() ) );
	}
}

template<class TNUM>
	void CBaseFunc::vntovs( const vector<TNUM>& vn, vector<string>& vs )
{
	vs.clear();
	static char tmp[64];
	for ( size_t i = 0; i < vn.size(); i++ )
	{
		sprintf( tmp, "%d", vn[i] );
		vs.push_back( tmp );	
	}
}

template<class TNUM> 
	void CBaseFunc::vntos( const vector<TNUM>& vn, const string& sp, string& s )
{
	vector<string> vs;
	vntovs( vn, vs );
	vstos( vs, sp, s );
}

template<class TNUM> 
	void CBaseFunc::md_stovn( const string& s, vector<TNUM>& vn )
{
	vector<string> vs;
	md_stovs( s, vs );
	vstovn( vs, vn );
}

template<class TNUM> 
	void CBaseFunc::md_vntos( const vector<TNUM>& vn, const string& sp, string& s )
{
	vntos( vn, sp, s );
	s = sp + s;
}

template<class TNUM, class TNUM2> 
	void CBaseFunc::vct_arr( const vector<TNUM>& vn, TNUM arr[], TNUM2& cnt )
{
	for ( size_t i = 0; i < vn.size(); i++ )
	{
		arr[i] = vn[i];
	}
	cnt = (TNUM2)vn.size();
}

template<class TNUM, class TNUM2>
void CBaseFunc::arr_vct( const TNUM arr[], TNUM2 cnt, vector<TNUM>& vn )
{
	vn.clear();
	for ( TNUM2 i = 0; i < cnt; i++ )
	{
		vn.push_back( arr[i] );
	}
}

#endif

