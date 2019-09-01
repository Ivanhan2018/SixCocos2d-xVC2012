#include <iostream>
#include <vector>
#include <string>
using namespace std;

// c++大数乘法
void multiply(const vector<int> &a, const vector<int> &b, vector<int> &result)
{
	int i, j, k;
	int tmp;

	for (i = 0; i < a.size(); ++i)
	{
		k = i;
		for (j = 0; j < b.size(); ++j)
		{
			result[k++] += a[i] * b[j];
		}
	}

	for (k = result.size() - 1;   k >= 0; --k)
	{
		if (result[k] > 9)
		{
			if (k != 0)
			{

				result[k - 1] += result[k] / 10;
				result[k] %= 10;
			}
			else   //如果是第一项大于9则添加一项于头部
			{
				tmp = result[k] / 10;
				result[k] %= 10;
				result.insert(result.begin(), tmp);
			}
		}
	}
} 

int main()
{
	int i;
	//use string to store the user input
	//user vector to store the integer
	string s;
	vector<int> a, b;
	cout << "please input two bignums: \n";
	cin >> s;
	//reserve places to avoid vector frequent expending
	a.reserve(s.size());
	//get the integer from string
	for (i = 0; i < s.size(); ++i)
	{
		a.push_back(s[i] - '0');
	}

	cin >> s;
	b.reserve(s.size());
	for (i = 0; i < s.size(); ++i)
	{
		b.push_back(s[i] - '0');
	}
	//create the result vector and initialize it with 0
	vector<int> c(a.size() + b.size() - 1, 0);

	multiply(a, b, c);
	//print the result
	for (i = 0; i < c.size(); ++i)
	{
		cout << c[i];
	}
	cout << endl;

#ifdef _MSC_VER
	system("pause");
#endif
	return 0;
}
