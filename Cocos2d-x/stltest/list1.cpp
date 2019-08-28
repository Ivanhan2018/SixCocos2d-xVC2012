#include<list>
#include<functional>
using namespace std;

typedef struct subscribeitem
{
   char *cig_code;
   char *cig_name;
   int cig_quantity;  //以此作为排序
public:
 bool operator > (const subscribeitem& b1) const
 {
  return cig_quantity>b1.cig_quantity;
 }
}Subitem;

//定义函数对象用来排序
class sort_Subitem
{
//函数对象的最大好处是可以内联，效率极高
public:
	sort_Subitem(){}
	bool operator()(Subitem X,Subitem Y)const
	{
	   //return X.cig_quantity<Y.cig_quantity;//升序排
	   return X.cig_quantity>Y.cig_quantity;//降序排
	}
};

int main()
{
 list <Subitem> ::iterator iter;
#if 1
 list <Subitem> m_plist={{"027","wuhan",3},{"020","guangzhou",1},{"028","chendu",2}};
#else
 list <Subitem> m_plist;
 Subitem item1;
 //item1 = new subscribeitem;
 item1.cig_code="027";
 item1.cig_name="wuhan";
 item1.cig_quantity=3;
 m_plist.push_back(item1);

 Subitem item2;
 //item2 = new subscribeitem;
 item2.cig_code="020";
 item2.cig_name="guangzhou";
 item2.cig_quantity=1;
 m_plist.push_back(item2);

 Subitem item3;
 //item3 = new subscribeitem;
 item3.cig_code="028";
 item3.cig_name="chendu";
 item3.cig_quantity=2;
 m_plist.push_back(item3);
#endif
 for(iter=m_plist.begin();iter!=m_plist.end();iter++)
 printf("%d,%s\n",iter->cig_quantity,iter->cig_name);
 //m_plist.sort(greater<Subitem>());//从大到小排序
 m_plist.sort(sort_Subitem());
 for(iter=m_plist.begin();iter!=m_plist.end();iter++)
 printf("%d,%s\n",iter->cig_quantity,iter->cig_name);
 getchar();
 return 0;
}