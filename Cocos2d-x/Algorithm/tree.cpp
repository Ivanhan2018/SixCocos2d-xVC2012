#include<iostream>
using namespace std;

template<class T>
class Node//一个节点类
{
public:
Node * left,*right,*next,*before;//左右子树指针和链表中的向前向后指针
T data;
public:
Node():left(NULL),right(NULL),next(NULL),before(NULL){}
Node(T d):data(d),left(NULL),right(NULL),next(NULL),before(NULL){}
void setnext(Node<T>* node)//在当前节点前增添一节点---在链表中有顺序关系
{
   Node<T>*p=next;
   next=node;
   node->before=this;
   node->next=p;
   if(p!=NULL)
    p->before=node;
}
void setbefore(Node<T>* node)//在当前节点后增加一节点
{
   Node<T>* p=before;
   before=node;
   node->before=p;
   node->next=this;
   if(p!=NULL)
    p->next=node;
}
};

template<class T>
class tree
{
private:
Node<T>*root,*head;
public:
tree():root(NULL),head(NULL){}
void settree(const T data)   //往树中增加节点 同时使之按次序排列
{
   if(root==NULL)
    head=root=new Node<T>(data);
   else
   {
    Node<T>*p=root,*q=root;
    while(p!=NULL)
    {
     q=p;
     if(data<=p->data)
      p=p->left;
     else
      p=p->right;
    }
    if(data<=q->data)
    {
     q->left=new Node<T>(data);
     q->setbefore(q->left);
     if(q->left->before==NULL)
      head=q->left;
    }
    else
    {
     q->right=new Node<T>(data);
     q->setnext(q->right);
    }
   }
}
friend ostream& operator << (ostream& out,const tree<T>& t)
{
   Node<T>*p=t.head;
   while(p!=NULL)
   {
    cout<<p->data<<" ";
    p=p->next;
   }
   return out;
}
};

int main()
{
// 二叉树排序
//2 6 9 18 27 34 35 43 51 100
int a[10]={18,27,2,34,100,51,6,9,43,35};
int n=sizeof(a) / sizeof(a[0]);
tree<int> tr;
for(int i = 0; i < n; i++)
tr.settree(a[i]);
cout<<'\n'<<tr<<'\n'<<endl;

#ifdef _MSC_VER
	system("pause");
#endif
return 0;
}
