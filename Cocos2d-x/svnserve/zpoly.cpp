//g++ -std=c++11 -o zpoly zpoly.cpp
#include <stdlib.h>
#include <stdarg.h>
#include <string.h> 
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

class StringUtil
{
public:
	static std::vector<string> split( const std::string& str, const std::string& delims = "\t\n ", unsigned int maxSplits = 0);//根据所给字符对字符串进行分割
};


/** Returns a std::stringVector that contains all the substd::strings delimited
   by the characters in the passed <code>delims</code> argument.
   @param 
   delims A list of delimiter characters to split by
   @param 
   maxSplits The maximum number of splits to perform (0 for unlimited splits). If this
   parameters is > 0, the splitting process will stop after this many splits, left to right.
   */
std::vector<string> StringUtil::split( const std::string& str, const std::string& delims/* = "\t\n "*/, unsigned int maxSplits/* = 0*/)
{
	std::vector<string> ret;
	unsigned int numSplits = 0;

	// Use STL methods 
	size_t start, pos;
	start = 0;
	do 
	{
		pos = str.find_first_of(delims, start);
		if (pos == start)
		{
			// Do nothing
			start = pos + 1;
		}
		else if (pos == std::string::npos || (maxSplits && numSplits == maxSplits))
		{
			// Copy the rest of the std::string
			ret.push_back( str.substr(start) );
			break;
		}
		else
		{
			// Copy up to delimiter
			ret.push_back( str.substr(start, pos - start) );
			start = pos + 1;
		}
		// parse up to next real data
		start = str.find_first_not_of(delims, start);
		++numSplits;

	} while (pos != std::string::npos);
	return ret;
}

typedef double Int;

typedef struct 
{        
 int power;        
 Int * coef;
} poly_t, *poly; 
#define E(x, i) (x)->coef[i] 

poly p_New(vector<int>& v)
{
	int power=v.size()-1;
	 int i, zeroed = 0;                
	 if (power < 0) 
	 {                
	  power = -power;                
	  zeroed = 1;        
	 }         
	 poly p = (poly)malloc(sizeof(poly_t));        
	 p->power = power;        
	 p->coef = (Int *)malloc(sizeof(Int) * ++power);         
	 if (zeroed)                
	  for (i = 0; i < power; i++) 
	   p->coef[i] = 0;        
	 else 
	 {                              
	  for (i = 0; i < power; i++)                        
	   E(p, i) = v[i];                  
	 }         
	 return p;
}

/* passing in negative power to have a zeroed poly */
poly p_new(int power, ...)
{        
 int i, zeroed = 0;        
    va_list ap;         
 if (power < 0) 
 {                
  power = -power;                
  zeroed = 1;        
 }         
 poly p = (poly)malloc(sizeof(poly_t));        
 p->power = power;        
 p->coef = (Int *)malloc(sizeof(Int) * ++power);         
 if (zeroed)                
  for (i = 0; i < power; i++) 
   p->coef[i] = 0;        
 else 
 {                
  va_start(ap, power);                
  for (i = 0; i < power; i++)                        
   E(p, i) = va_arg(ap, Int);                
  va_end(ap);        
 }         
 return p;
} 

void p_del(poly p)
{
 free(p->coef);        
 free(p);
} 

void p_print(poly p)
{        
 for (int i = 0; i <= p->power; i++)
 {             
	cout<<(int)E(p, i)<<"x^"<<i; 
	if(i < p->power) 
	cout<<"+"; 
 }
 cout<<"="; 
 cout<<"[";   
 for (int i = 0; i <= p->power; i++)
 {             
	cout<<(int)E(p, i); 
	if(i < p->power) 
	cout<<",";	 
 }
 cout<<"]"<<endl; 
} 

poly p_copy(poly p)
{        
 poly q = p_new(-p->power);        
 memcpy(q->coef, p->coef, sizeof(Int) * (1 + p->power));        
 return q;
} 
/* p: poly;  d: divisor;  r: remainder; returns quotient */
poly p_div(poly p, poly d, poly* r)
{        
 poly q;        
 int i, j;        
 int power = p->power - d->power;        
 Int ratio;         
 if (power < 0) 
  return 0;         
 q = p_new(-power);        
 *r= p_copy(p);         
 for (i = p->power; i >= d->power; i--) 
 {                
  E(q, i - d->power) = ratio = E(*r, i) / E(d, d->power);                
  E(*r ,i) = 0;                 
  for (j = 0; j < d->power; j++)                        
   E(*r, i - d->power + j) -= E(d, j) * ratio;        
 }        
 while (! E(*r, --(*r)->power));         
 return q;
} 

vector<int> conv(Int * coefx, Int * coefh, int lx, int lh)
{
    vector<int> xout(lx+lh-1);
	Int sum;
	for (int i = 0; i < lx + lh - 1; i++)
	{
		sum = 0.0;
		if( i < lh - 1 )
		{
			for(int j = 0; j < i+1; j++)
			sum += coefx[j] * coefh[i-j];
				xout[i] = (int)sum;
		}
		else if(i > lx - 1)
		{
			for(int j = lh -1; j > i - lx; j--)
			sum += coefx[i-j] * coefh[j];
				xout[i]= (int)sum;
		}
		else
		{
			for(int j = 0; j < lh; j++)
			sum += coefx[i-j] * coefh[j];
				xout[i]= (int)sum;
		}
	} 
	return xout;
} 

int main(int argc, char* argv[])
{   
	if( argc < 3 )
	{
		cout<<"Usage:  zploy arg1 arg2"<<endl;
		return 0;
	}
    vector<string> str1=StringUtil::split(argv[1],",");
    vector<string> str2=StringUtil::split(argv[2],",");
	vector<int> poly1;
	vector<int> poly2;
	for(auto it=str1.begin();it!=str1.end();it++)
	{
		poly1.push_back(atoi((*it).c_str()));
	}
	for(auto it=str2.begin();it!=str2.end();it++)
	{
		poly2.push_back(atoi((*it).c_str()));
	}	
     
	poly p = p_New(poly1);        
	poly d = p_New(poly2);        
	poly r;        
	poly q = p_div(p, d, &r);         
	cout<<"poly: "; 
	p_print(p);        
	cout<<"div:  "; 
	p_print(d);        
	cout<<"quot: "; 
	p_print(q);        
	cout<<"rem:  "; 
	p_print(r); 
	vector<int> poly3=conv(d->coef,q->coef,d->power+1,q->power+1);
	poly dq = p_New(poly3);
	cout<<"div*quot:  "; 	
	p_print(dq); 	
	p_del(dq);
	p_del(p);        
	p_del(q);        
	p_del(r);        
	p_del(d); 

	return 0;
}