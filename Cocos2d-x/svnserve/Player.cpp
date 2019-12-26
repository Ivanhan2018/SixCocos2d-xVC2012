#include <iostream>
using namespace std;

// C++也允许私有静态的成员函数，它只能被该类的其它成员函数调用，不能在类外被调用。
class Player
{
  static Player P;
  int m_nID;
  Player(int nID):m_nID(nID){}
public:
  static Player* instance()
  {
    return &P;
  }
  //静态公有的函数
  static void SetID(int nID);
  int GetID()const
  {
   return m_nID;
  }
};
//静态数据成员的初始化
Player Player::P(100);

// 静态函数
void Player::SetID(int nID)
{
 P.m_nID=nID;
} 

int main()
{
//Player x(1); //Error: 不能调用私有的构造函数
//因此，不能创建新的对象
cout<<Player::instance()->GetID()<<endl;

// 通过类名调用SetID成员函数 
Player::SetID(200); 
cout<<Player::instance()->GetID()<<endl;

//通过对象调用SetID成员函数
Player::instance()->SetID(300); 
cout<<Player::instance()->GetID()<<endl;
return 0;
}
