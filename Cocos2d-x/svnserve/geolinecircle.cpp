// ��ʾ��̳�������̳�
#include <iostream>
using namespace std;

class geo
{
public:
    //��Щpublic�ӿڶ���Ӧ������������г���˽�г�Ա��Ҳ����ֱ�ӳ������ݳ�Ա��
    //����posx,posyֻ����ʱ����ʽ������
    void virtual init(int posx,int posy);
    //x��y�����ϵ�ƫ����
    void virtual move(int corx,int cory);

private:
    //˽�г�Աֻ���Լ�����Ԫ�á�
    int x,y;
}; //ע�⣬��Ϊһ������������������class����struct,����Ҫ�����λ�ü���ð�š�

void geo::init(int posx,int posy)
{
    //ֻ���ڶ����У����ܳ���˽�г�Ա���ڶ���geo��class�ӿ�ʱ��Ӧ���֡�
    x=posx;
    y=posy;
} //����Ͳ���Ҫ����ð���ˡ�

void geo::move(int corx,int cory)
{
    x+=corx;
    y+=cory;

}

//��������һ����geo������ʽ������line class

class line : public geo
{
    //��д(Override)������(Overload)
public:
    //��Ϊ���ڲ�ͬ��class�����У�����posx,posy��������ʱ�������Ի��á�
    void init(int posx,int posy)override;
    void move(int corx,int cory)override;

};

//������ʵ����

void line::init(int posx,int posy)
{
    cout<<"call from line::init()"<<endl;
    cout<<"now my (i am line) posx,posy are"<<posx<<posy<<endl;
    //��Ȼ���㻹���Լ����������߼�

}

void line::move(int corx,int cory)
{
    //��initһ�������line�����Լ���ͬ�ڻ���geo��move��Ϊ�������������������Լ����߼���
}

//�ٶ���һ������������geo�����࣬�����۶�̳е��ص�

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


//����һ��ͨ�ú���������geoΪ������������ʾ���������ʲô������Ϊ
//��������initx,inity��geo,line,circle��init()��������һ�£�����ʵ���岻ͬ
//��������������class�ڵ�public�ӿڵĲ������������ȫ����mycommoninit�Ĳ�����
//һ����˵��class�ڵĽӿ�Ҫ�������ò���ʱ����Сְ��ԭ��
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

