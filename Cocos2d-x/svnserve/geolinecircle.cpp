// 演示多继承与虚拟继承
#include <iostream>
using namespace std;

class geo
{
public:
    //这些public接口都不应该在其参数表中出现私有成员，也不该直接出现数据成员。
    //所以posx,posy只是临时的形式参数。
    void virtual init(int posx,int posy);
    //x和y方向上的偏移量
    void virtual move(int corx,int cory);

private:
    //私有成员只有自己和友元用。
    int x,y;
}; //注意，作为一个声明，无论是声明class还是struct,都需要在这个位置加入冒号。

void geo::init(int posx,int posy)
{
    //只有在定现中，才能出现私有成员，在定义geo的class接口时不应出现。
    x=posx;
    y=posy;
} //定义就不需要加入冒号了。

void geo::move(int corx,int cory)
{
    x+=corx;
    y+=cory;

}

//再来定义一个从geo公共方式派生的line class

class line : public geo
{
    //重写(Override)与重载(Overload)
public:
    //因为处在不同的class声明中，所以posx,posy这样的临时参量可以混用。
    void init(int posx,int posy)override;
    void move(int corx,int cory)override;

};

//下面来实现它

void line::init(int posx,int posy)
{
    cout<<"call from line::init()"<<endl;
    cout<<"now my (i am line) posx,posy are"<<posx<<posy<<endl;
    //当然，你还可以加入其它的逻辑

}

void line::move(int corx,int cory)
{
    //跟init一样，如果line有它自己不同于基类geo的move行为，你可以在这里加入你自己的逻辑。
}

//再定义一个公共派生自geo的子类，以讨论多继承的特点

class circle : public geo
{
public:
    void init(int posx,int posy)override;
    void move(int corx,int cory)override;
};

void circle::init(int posx,int posy)
{
    cout<<"call from circle::init()"<<endl;
    cout<<"now my (i am circle) posx,posy are"<<posx<<posy<<endl;
}

void circle::move(int corx,int cory)
{

}


//定义一个通用函数，它以geo为操作对象，以演示其子类会有什么样的行为
//看到了吗，initx,inity跟geo,line,circle的init()参数几乎一致，但其实含义不同
//后三者是声明的class内的public接口的参数，而这里的全域函数mycommoninit的参数。
//一般来说，class内的接口要做到设置参数时的最小职责原则。
void mycommoninit(geo& _geo,int initx,int inity)
{
    _geo.init(initx,inity);
}

//void mycommonmove

int main()
{
    line myline;
    circle mycircle[5];

    mycommoninit(myline,10,10);

    for (int i=0;i<5;i++)
    {
        mycommoninit(mycircle[i],20,20);
    }

#ifdef _MSC_VER
    system("pause");
#endif
    return 0;
}

