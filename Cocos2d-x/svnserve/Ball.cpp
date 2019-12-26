#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "BaseFunc.h"

class Ball
{
public:
     virtual void play()=0;
};

class BasketBall : public Ball
{
public:
     virtual void play();
};

void BasketBall::play()
{
   cout<<"BasketBall::play()"<<endl;
}

class TennisBall : public Ball
{
public:
     virtual void play();
};

void TennisBall::play()
{
    cout<<"TennisBall::play()"<<endl;
}

int main(int argc, char* argv[])
{
#if 1
    if(argc>1)
	{
		vector<string> vecGroup;
		CBaseFunc::stovs(argv[1], ":", vecGroup);
		if (vecGroup[0] == "t")
		{
			int tableId = atoi(vecGroup[1].c_str());
			cout<<"tableId="<<tableId<<endl;
		}
	}
#endif

     Ball* b = new BasketBall();
     b->play();

     vector<Ball*> ball_collector;
     for(int i = 0 ; i<10; i++)
           ball_collector.push_back(new BasketBall());

     for(int i = 0 ; i<10; i++)
           ball_collector.push_back(new TennisBall());

     for(vector<Ball*>::iterator i = ball_collector.begin(); i != ball_collector.end() ; i++)
     {
           cout<<i-ball_collector.begin()<<" ";
           (*i)->play();
     }

     //system("pause");
     return 0;
}