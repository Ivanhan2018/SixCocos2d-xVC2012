#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void)
{
#if 1
	vector<int> num={3,1,4,5,2};
#else
	vector<int> num;		// STL中的vector容器
	int element;
	// 从标准输入设备读入整数，
	// 直到输入的是非整型数据为止
	while (cin >> element)
		num.push_back(element);
#endif
	// STL中的排序算法
	sort(num.begin(), num.end());

#if 1
	typedef ostream_iterator<int> ostream_itr;
	// 将排序结果输出到标准输出设备
	copy(num.begin(), num.end(), ostream_itr(cout, "\n"));
#else
	// 将排序结果输出到标准输出设备
	for (int i = 0; i < num.size(); i ++)
		cout << num[i] << "\n";
#endif

        return 0;
}