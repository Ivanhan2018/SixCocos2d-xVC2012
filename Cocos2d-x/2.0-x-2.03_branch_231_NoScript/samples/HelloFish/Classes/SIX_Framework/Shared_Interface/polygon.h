/*  
���㼸��Ŀ¼----�Ѳ����㷨ģ��   
�� ��Ļ�������   
1. ƽ��������֮����� 1   
2. �ж������Ƿ��غ� 1   
3. ʸ����� 1   
4. ʸ����� 2   
5. �жϵ��Ƿ����߶��� 2   
6. ��һ����ĳ����ת������� 2   
7. ��ʸ���н� 2   

�� �߶μ�ֱ�ߵĻ�������   
1. �����߶εĹ�ϵ 3   
2. ��㵽�߶�����ֱ�ߴ��ߵĴ��� 4   
3. �㵽�߶ε������ 4   
4. �㵽�߶�����ֱ�ߵľ��� 4   
5. �㵽���߼���������� 4   
6. �ж�Բ�Ƿ��ڶ������ 5   
7. ��ʸ���н����� 5   
8. ���߶�֮��ļн� 5   
9. �ж��߶��Ƿ��ཻ 6   
10.�ж��߶��Ƿ��ཻ�������ڶ˵㴦 6   
11.���߶�����ֱ�ߵķ��� 6   
12.��ֱ�ߵ�б�� 7   
13.��ֱ�ߵ���б�� 7   
14.������ĳֱ�ߵĶԳƵ� 7   
15.�ж�����ֱ���Ƿ��ཻ����ֱ�߽��� 7   
16.�ж��߶��Ƿ��ཻ������ཻ���ؽ��� 7   

�� ����γ����㷨ģ��   
1. �ж϶�����Ƿ�򵥶����----issimple��FPOINT polygon[]���Ϊһ��ȷ���Ķ���ζ��������Ķ��㼯�����Graham_scan����ʹ�ã�  
2. ������ζ����͹���� 9   
3. �ж϶�����Ƿ�͹�����----isconvex��FPOINT polygon[]���Ϊһ��ȷ���Ķ���ζ��������Ķ��㼯�����Graham_scan����ʹ�ã���isconvexEx��FPOINT polygon[]���Ϊһ��ȷ���ļ򵥶���ζ��������Ķ��㼯��   
4. ��������� 9   
5. �ж϶���ζ�������з��򣬷���һ 10   
6. �ж϶���ζ�������з��򣬷����� 10   
7. ���߷��жϵ��Ƿ��ڶ������ 10   
8. �жϵ��Ƿ���͹�������----InsideConvexPolygon
8a.�жϵ��Ƿ���ƽ������(�����ǷǼ򵥶���Σ������Ƿ�͹�����)��----InsidePolygon
9. Ѱ�ҵ㼯��graham�㷨----Graham_scan
10.Ѱ�ҵ㼯͹���ľ������ 13   
11.�ж��߶��Ƿ��ڶ������ 14   
12.��򵥶���ε����� 15   
13.��͹����ε����� 17   
14.��϶��ڸ���������ڵ�һ���� 17   
15.��Ӷ������һ��������ö���ε����� 18   
16.�ж϶���εĺ��Ƿ���� 19   

�� Բ�Ļ�������   
1 .���Ƿ���Բ�� 20   
2 .�󲻹��ߵ�������ȷ����Բ 21   

�� ���εĻ�������   
1.��֪�����������꣬���4������ 22   

�� �����㷨������ 22   

�� ����   
1����Բ��ϵ�� 24   
2���ж�Բ�Ƿ��ھ����ڣ� 24   
3���㵽ƽ��ľ��룺 25   
4�����Ƿ���ֱ��ͬ�ࣺ 25   
5�����淴���ߣ� 25   
6�����ΰ����� 26   
7����Բ���㣺 27   
8����Բ��������� 28   
9. Բ��ֱ�߹�ϵ�� 29   
10. ����Բ�� 30   
11. ���е㣺 31   
12. �߶ε��������� 31   
13����ʽ�� 32

(��)����ͻ���Ҫ�õ��Ķ������ײ�㷨ģ�飬add by Ivan_han 20130603
1.�ж�Բ�Ƿ��������ཻ----CircleCrossPolygon
2.�ж�ֱ���Ƿ���򵥶�����ཻ----LineCrossPolygon
*/ 
#pragma once
//#include<cmath>
//#include<xutility>
//using namespace std;

/* ���õĳ������� */    
const float    INF     = 1E20f;//�����       
const float    EP      = 1E-10f;//����С    
const int       MAXV    = 300;    
const float    PI      = 3.14159265f;  

//float max(float x, float y)    
//{    
//	return (x > y ? x : y);    
//}    
//
//float min(float x, float y)    
//{    
//	return (x < y ? x : y);    
//}
   
/* �������νṹ */    
//struct FPOINT    
//{    
//    float x;    
//    float y;    
//    FPOINT(float a=0, float b=0) { x=a; y=b;} //constructor     
//};
struct FPOINT
{
	float x, y;
	FPOINT() : x(0), y(0) {}
	FPOINT(float _x, float _y) : x(_x), y(_y) {}
	FPOINT& operator= (const FPOINT& point) {x = point.x; y = point.y; return *this;}
};

//typedef FPOINT TPoint;
//typedef FPOINT POINT;
//typedef FPOINT CPoint;

struct LINESEG    
{    
    FPOINT s;    
    FPOINT e;    
    LINESEG(FPOINT a, FPOINT b) { s=a; e=b;}    
    LINESEG() { }    
};    
struct LINE           // ֱ�ߵĽ������� a*x+b*y+c=0  Ϊͳһ��ʾ��Լ�� a >= 0     
{    
   float a;    
   float b;    
   float c;    
   LINE(float d1=1, float d2=-1, float d3=0) {a=d1; b=d2; c=d3;}    
};    
   
/**********************  
 *                    *   
 *   ��Ļ�������     *   
 *                    *   
 **********************/    
   
float dist(FPOINT p1,FPOINT p2)                // ��������֮��ŷ�Ͼ���     
{    
    return( sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) ) );    
}    
bool equal_point(FPOINT p1,FPOINT p2)           // �ж��������Ƿ��غ�      
{    
    return ( (fabs(p1.x-p2.x)<EP)&&(fabs(p1.y-p2.y)<EP) );    
}    
/******************************************************************************   
r=multiply(sp,ep,op),�õ�(sp-op)��(ep-op)�Ĳ��   
r>0��ep��ʸ��opsp����ʱ�뷽��   
r=0��opspep���㹲�ߣ�   
r<0��ep��ʸ��opsp��˳ʱ�뷽��   
*******************************************************************************/    
float multiply(FPOINT sp,FPOINT ep,FPOINT op)    
{    
    return((sp.x-op.x)*(ep.y-op.y)-(ep.x-op.x)*(sp.y-op.y));    
}    
/*   
r=dotmultiply(p1,p2,op),�õ�ʸ��(p1-op)��(p2-op)�ĵ�����������ʸ��������ʸ��   
r<0����ʸ���н�Ϊ��ǣ�  
r=0����ʸ���н�Ϊֱ�ǣ�  
r>0����ʸ���н�Ϊ�۽�   
*******************************************************************************/    
float dotmultiply(FPOINT p1,FPOINT p2,FPOINT p0)    
{    
    return ((p1.x-p0.x)*(p2.x-p0.x)+(p1.y-p0.y)*(p2.y-p0.y));    
}    
/******************************************************************************   
�жϵ�p�Ƿ����߶�l��  
������(p���߶�l���ڵ�ֱ����) && (��p�����߶�lΪ�Խ��ߵľ�����)  
*******************************************************************************/    
bool online(LINESEG l,FPOINT p)    
{    
    return( (multiply(l.e,p,l.s)==0) &&( ( (p.x-l.s.x)*(p.x-l.e.x)<=0 )&&( (p.y-l.s.y)*(p.y-l.e.y)<=0 ) ) );    
}    
// ���ص�p�Ե�oΪԲ����ʱ����תalpha(��λ������)�����ڵ�λ��     
FPOINT rotate(FPOINT o,float alpha,FPOINT p)    
{    
    FPOINT tp;    
    p.x-=o.x;    
    p.y-=o.y;    
    tp.x=p.x*cos(alpha)-p.y*sin(alpha)+o.x;    
    tp.y=p.y*cos(alpha)+p.x*sin(alpha)+o.y;    
    return tp;    
}    
/* ���ض�����o�㣬��ʼ��Ϊos����ֹ��Ϊoe�ļн�(��λ������)   
    �Ƕ�С��pi��������ֵ   
    �Ƕȴ���pi�����ظ�ֵ   
    �����������߶�֮��ļн�   
ԭ��  
    r = dotmultiply(s,e,o) / (dist(o,s)*dist(o,e))  
    r'= multiply(s,e,o)  
  
    r >= 1   angle = 0;  
    r <= -1  angle = -PI  
    -1<r<1 && r'>0 angle = arccos(r)  
    -1<r<1 && r'<=0    angle = -arccos(r)  
*/    
float angle(FPOINT o,FPOINT s,FPOINT e)    
{    
    float cosfi,fi,norm;    
    float dsx = s.x - o.x;    
    float dsy = s.y - o.y;    
    float dex = e.x - o.x;    
    float dey = e.y - o.y;    
   
    cosfi=dsx*dex+dsy*dey;    
    norm=(dsx*dsx+dsy*dsy)*(dex*dex+dey*dey);    
    cosfi /= sqrt( norm );    
   
    if (cosfi >=  1.0 ) return 0;    
    if (cosfi <= -1.0 ) return -3.1415926f;    
   
    fi=acos(cosfi);    
    if (dsx*dey-dsy*dex>0) return fi;      // ˵��ʸ��os ��ʸ�� oe��˳ʱ�뷽��     
    return -fi;    
}    
  /*****************************\   
  *                             *   
  *      �߶μ�ֱ�ߵĻ�������   *   
  *                             *   
  \*****************************/    
   
/* �жϵ����߶εĹ�ϵ,��;�ܹ㷺   
�������Ǹ�������Ĺ�ʽд�ģ�P�ǵ�C���߶�AB����ֱ�ߵĴ���   
  
                AC dot AB   
        r =     ---------   
                 ||AB||^2   
             (Cx-Ax)(Bx-Ax) + (Cy-Ay)(By-Ay)   
          = -------------------------------   
                          L^2   
  
    r has the following meaning:   
  
        r=0      P = A   
        r=1      P = B   
        r<0       P is on the backward extension of AB   
        r>1      P is on the forward extension of AB   
        0<r<1  P is interior to AB   
*/    
float relation(FPOINT p,LINESEG l)    
{    
    LINESEG tl;    
    tl.s=l.s;    
    tl.e=p;    
    return dotmultiply(tl.e,l.e,l.s)/(dist(l.s,l.e)*dist(l.s,l.e));    
}    
// ���C���߶�AB����ֱ�ߵĴ��� P     
FPOINT perpendicular(FPOINT p,LINESEG l)    
{    
    float r=relation(p,l);    
    FPOINT tp;    
    tp.x=l.s.x+r*(l.e.x-l.s.x);    
    tp.y=l.s.y+r*(l.e.y-l.s.y);    
    return tp;    
}    
/* ���p���߶�l����̾���,�������߶��Ͼ�õ�����ĵ�np   
ע�⣺np���߶�l�ϵ���p����ĵ㣬��һ���Ǵ��� */    
float ptolinesegdist(FPOINT p,LINESEG l,FPOINT &np)    
{    
    float r=relation(p,l);    
    if(r<0)    
    {    
        np=l.s;    
        return dist(p,l.s);    
    }    
    if(r>1)    
    {    
        np=l.e;    
        return dist(p,l.e);    
    }    
    np=perpendicular(p,l);    
    return dist(p,np);    
}    
// ���p���߶�l����ֱ�ߵľ���,��ע�Ȿ�������ϸ�����������      
float ptoldist(FPOINT p,LINESEG l)    
{    
    return fabs(multiply(p,l.e,l.s))/dist(l.s,l.e);    
}    
/* ����㵽���߼����������,�����������.   
ע�⣺���õ���ptolineseg()���� */    
float ptopointset(int vcount,FPOINT pointset[],FPOINT p,FPOINT &q)    
{    
    int i;    
    float cd=float(INF),td;    
    LINESEG l;    
    FPOINT tq,cq;    
   
    for(i=0;i<vcount-1;i++)    
    {    
        l.s=pointset[i];    
   
        l.e=pointset[i+1];    
        td=ptolinesegdist(p,l,tq);    
        if(td<cd)    
        {    
            cd=td;    
            cq=tq;    
        }    
    }    
    q=cq;    
    return cd;    
}    
/* �ж�Բ�Ƿ��ڶ������.ptolineseg()������Ӧ��2 */    
bool CircleInsidePolygon(int vcount,FPOINT center,float radius,FPOINT polygon[])    
{    
    FPOINT q;    
    float d;    
    q.x=0;    
    q.y=0;    
    d=ptopointset(vcount,polygon,center,q);    
    if(d<radius||fabs(d-radius)<EP)    
        return true;    
    else    
        return false;    
}    
/* ��������ʸ��l1��l2�ļнǵ�����(-1 --- 1)ע�⣺������������нǵĻ���ע�ⷴ���Һ����Ķ������Ǵ� 0��pi */    
float cosine(LINESEG l1,LINESEG l2)    
{    
    return (((l1.e.x-l1.s.x)*(l2.e.x-l2.s.x) +(l1.e.y-l1.s.y)*(l2.e.y-l2.s.y))/(dist(l1.e,l1.s)*dist(l2.e,l2.s)));    
}    
// �����߶�l1��l2֮��ļн� ��λ������ ��Χ(-pi��pi)     
float lsangle(LINESEG l1,LINESEG l2)    
{    
    FPOINT o,s,e;    
    o.x=o.y=0;    
    s.x=l1.e.x-l1.s.x;    
    s.y=l1.e.y-l1.s.y;    
    e.x=l2.e.x-l2.s.x;    
    e.y=l2.e.y-l2.s.y;    
    return angle(o,s,e);    
}    
// ����߶�u��v�ཻ(�����ཻ�ڶ˵㴦)ʱ������true     
//    
//�ж�P1P2����Q1Q2�������ǣ�( P1 - Q1 ) �� ( Q2 - Q1 ) * ( Q2 - Q1 ) �� ( P2 - Q1 ) >= 0��    
//�ж�Q1Q2����P1P2�������ǣ�( Q1 - P1 ) �� ( P2 - P1 ) * ( P2 - P1 ) �� ( Q2 - P1 ) >= 0��    
bool intersect(LINESEG u,LINESEG v)    
{    
    return( (max(u.s.x,u.e.x)>=min(v.s.x,v.e.x))&&                     //�ų�ʵ��     
            (max(v.s.x,v.e.x)>=min(u.s.x,u.e.x))&&    
            (max(u.s.y,u.e.y)>=min(v.s.y,v.e.y))&&    
            (max(v.s.y,v.e.y)>=min(u.s.y,u.e.y))&&    
            (multiply(v.s,u.e,u.s)*multiply(u.e,v.e,u.s)>=0)&&         //����ʵ��     
            (multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0));    
}    
//  (�߶�u��v�ཻ)&&(���㲻��˫���Ķ˵�) ʱ����true        
bool intersect_A(LINESEG u,LINESEG v)    
{    
    return  ((intersect(u,v))&&    
            (!online(u,v.s))&&    
            (!online(u,v.e))&&    
            (!online(v,u.e))&&    
            (!online(v,u.s)));    
}    
// �߶�v����ֱ�����߶�u�ཻʱ����true���������ж��߶�u�Ƿ�����߶�v      
bool intersect_l(LINESEG u,LINESEG v)    
{    
    return multiply(u.s,v.e,v.s)*multiply(v.e,u.e,v.s)>=0;    
}    
// ������֪�������꣬����������ֱ�߽������̣� a*x+b*y+c = 0  (a >= 0)      
LINE makeline(FPOINT p1,FPOINT p2)    
{    
    LINE tl;    
    int sign = 1;    
    tl.a=p2.y-p1.y;    
    if(tl.a<0)    
    {    
        sign = -1;    
        tl.a=sign*tl.a;    
    }    
    tl.b=sign*(p1.x-p2.x);    
    tl.c=sign*(p1.y*p2.x-p1.x*p2.y);    
    return tl;    
}    
// ����ֱ�߽������̷���ֱ�ߵ�б��k,ˮƽ�߷��� 0,��ֱ�߷��� 1e200     
float slope(LINE l)    
{    
    if(fabs(l.a) < 1e-20)   
        return 0;    
    if(fabs(l.b) < 1e-20)   
        return INF;    
    return -(l.a/l.b);    
}    
// ����ֱ�ߵ���б��alpha ( 0 - pi)     
float alpha(LINE l)    
{    
    if(fabs(l.a)< EP)   
        return 0;    
    if(fabs(l.b)< EP)   
        return PI/2;    
    float k=slope(l);    
    if(k>0)    
        return atan(k);    
    else    
        return PI+atan(k);    
}    
// ���p����ֱ��l�ĶԳƵ�      
FPOINT symmetry(LINE l,FPOINT p)    
{    
   FPOINT tp;    
   tp.x=((l.b*l.b-l.a*l.a)*p.x-2*l.a*l.b*p.y-2*l.a*l.c)/(l.a*l.a+l.b*l.b);    
   tp.y=((l.a*l.a-l.b*l.b)*p.y-2*l.a*l.b*p.x-2*l.b*l.c)/(l.a*l.a+l.b*l.b);    
   return tp;    
}    
// �������ֱ�� l1(a1*x+b1*y+c1 = 0), l2(a2*x+b2*y+c2 = 0)�ཻ������true���ҷ��ؽ���p      
bool lineintersect(LINE l1,LINE l2,FPOINT &p) // �� L1��L2     
{    
    float d=l1.a*l2.b-l2.a*l1.b;    
    if(fabs(d)<EP) // ���ཻ     
        return false;    
    p.x = (l2.c*l1.b-l1.c*l2.b)/d;    
    p.y = (l2.a*l1.c-l1.a*l2.c)/d;    
    return true;    
}    
// ����߶�l1��l2�ཻ������true�ҽ�����(inter)���أ����򷵻�false     
bool intersection(LINESEG l1,LINESEG l2,FPOINT &inter)    
{    
    LINE ll1,ll2;    
    ll1=makeline(l1.s,l1.e);    
    ll2=makeline(l2.s,l2.e);    
    if(lineintersect(ll1,ll2,inter))    
        return online(l1,inter);    
    else    
        return false;    
}    
   
/******************************\   
*                             *   
* ����γ����㷨ģ��       *   
*                             *   
\******************************/  
// ������ر�˵�����������ζ���Ҫ����ʱ������     
   
/*   
����ֵ������Ķ�����Ǽ򵥶���Σ�����true   
Ҫ �����붥�����а���ʱ������   
˵ �����򵥶���ζ��壺   
1��ѭ�������������߶ζԵĽ�������֮�乲�еĵ�����   
2�������ڵ��߶β��ཻ   
������Ĭ�ϵ�һ�������Ѿ�����
//issimple��
//�����ܹ���͹���ε��ĸ��㣬pt[0],pt[1],pt[2],pt[3]����һ���򵥶���ξͷ���true������ͷ���false�����ǲ����ж϶���˳������ʱ�룬����˳ʱ��
//���ڲ��ܹ���͹���ε��ĸ��㣬pt[0],pt[1],pt[2],pt[3]����һ���򵥶���ξͷ���true������ͷ���false�����ǲ����ж϶���˳������ʱ�룬����˳ʱ��
*/    
bool issimple(int vcount,FPOINT polygon[])    
{    
    int i,cn;    
    LINESEG l1,l2;    
    for(i=0;i<vcount;i++)    
    {    
        l1.s=polygon[i];    
        l1.e=polygon[(i+1)%vcount];    
        cn=vcount-3;    
        while(cn)    
        {    
            l2.s=polygon[(i+2)%vcount];    
            l2.e=polygon[(i+3)%vcount];    
            if(intersect(l1,l2))    
                break;    
            cn--;    
        }    
        if(cn)    
            return false;    
    }    
    return true;    
}    
// ����ֵ��������˳�򷵻ض���ζ����͹�����жϣ�bc[i]=1,iff:��i��������͹����     
void checkconvex(int vcount,FPOINT polygon[],bool bc[])    
{    
    int i,index=0;    
    FPOINT tp=polygon[0];    
    for(i=1;i<vcount;i++) // Ѱ�ҵ�һ��͹����     
    {    
        if(polygon[i].y<tp.y||(polygon[i].y == tp.y&&polygon[i].x<tp.x))    
        {    
            tp=polygon[i];    
            index=i;    
        }    
    }    
    int count=vcount-1;    
    bc[index]=1;    
    while(count) // �ж�͹����     
    {    
        if(multiply(polygon[(index+1)%vcount],polygon[(index+2)%vcount],polygon[index])>=0 )    
            bc[(index+1)%vcount]=1;    
        else    
            bc[(index+1)%vcount]=0;    
        index++;    
        count--;    
    }    
}   
// ����ֵ�������polygon��͹�����ʱ������true      
bool isconvex(int vcount,FPOINT polygon[])    
{    
    bool bc[MAXV];    
    checkconvex(vcount,polygon,bc);    
    for(int i=0;i<vcount;i++) // ��һ��鶥�㣬�Ƿ�ȫ����͹����     
        if(!bc[i])    
            return false;    
    return true;    
}

int tt(float p[][2],int a,int b,int N) //aΪ�±꣬����Ϊfloat 
{  
	//int temp[N],k=0;
	int temp[MAXV],k=0;
	float t;  
	for(int i=0;i<N;i++) 
	{  
		if(i==a||i==b)
		{ 
			continue; 
		} 
		t=p[i][0]*(p[b][1]-p[a][1])+(p[a][0]-p[b][0])*p[i][1]-p[a][0]*p[b][1]+p[b][0]*p[a][1]; 
		if(t==0)  
			return 0; 
		else 
			if(t>0)  
				temp[k++]=1; 
			else  
				temp[k++]=-1; 
	}  
	for(int j=1;j<k;j++) 
	{  
		if(temp[0]!=temp[j]) return 0; 
	}  
	return 1; 
}

//����N���������,�ж��ܷ񹹳�һ��͹�����
//��isconvex��ͬ���ǣ�isconvexEx�������ڶ���˳��
int isconvexEx(float p[][2],int N) 
{  
	//int flag[N],m=0;
	int flag[MAXV],m=0;
	for(int i=0;i<N;i++) 
	{  
		flag[i]=0; 
	}  
	for(int i=0;i<N;i++) 
	{  
		for(int j=1;j<N;j++) 
		{  

			if(flag[j]) continue; 
			if(tt(p,m,j,N)) 
			{  

				flag[m]=1;  
				m=j; 
				break; 
			}
		} 
	}  
	flag[m]=1;  
	for(int i=0;i<N;i++) 
	{  
		if(flag[i]==0) 
			return 0; 
	}  
	if(tt(p,0,m,N)) return 1; 
	return 0; 
}

// ���ض�������(signed)�����붥�㰴��ʱ������ʱ��������ֵ�����򷵻ظ�ֵ     
float area_of_polygon(int vcount,FPOINT polygon[])    
{    
    int i;    
    float s;    
    if (vcount<3)    
        return 0;    
    s=polygon[0].y*(polygon[vcount-1].x-polygon[1].x);    
    for (i=1;i<vcount;i++)    
        s+=polygon[i].y*(polygon[(i-1)].x-polygon[(i+1)%vcount].x);    
    return s/2;    
}    
// ������붥�㰴��ʱ�����У�����true     
bool isconterclock(int vcount,FPOINT polygon[])    
{    
    return area_of_polygon(vcount,polygon)>0;    
}    
// ��һ���ж϶���ζ������з���ķ���      
bool isccwize(int vcount,FPOINT polygon[])    
{    
    int i,index;    
    FPOINT a,b,v;    
    v=polygon[0];    
    index=0;    
    for(i=1;i<vcount;i++) // �ҵ���������󶥵㣬�϶���͹����     
    {    
        if(polygon[i].y<v.y||polygon[i].y == v.y && polygon[i].x<v.x)    
        {    
            index=i;    
        }    
    }    
    a=polygon[(index-1+vcount)%vcount]; // ����v��ǰһ����     
    b=polygon[(index+1)%vcount]; // ����v�ĺ�һ����     
    return multiply(v,b,a)>0;    
}    
/********************************************************************************************     
���߷��жϵ�q������polygon��λ�ù�ϵ��Ҫ��polygonΪ�򵥶���Σ�������ʱ������   
   ������ڶ�����ڣ�   ����0   
   ������ڶ���α��ϣ� ����1   
   ������ڶ�����⣺    ����2   
*********************************************************************************************/    
int insidepolygon(int vcount,FPOINT Polygon[],FPOINT q)    
{    
    int c=0,i,n;    
    LINESEG l1,l2;    
    bool bintersect_a,bonline1,bonline2,bonline3;    
    float r1,r2;    
   
    l1.s=q;    
    l1.e=q;    
    l1.e.x=float(INF);    
    n=vcount;    
    for (i=0;i<vcount;i++)    
    {    
        l2.s=Polygon[i];    
        l2.e=Polygon[(i+1)%n];    
        if(online(l2,q))   
            return 1; // ������ڱ��ϣ�����1     
        if ( (bintersect_a=intersect_A(l1,l2))|| // �ཻ�Ҳ��ڶ˵�     
        ( (bonline1=online(l1,Polygon[(i+1)%n]))&& // �ڶ����˵���������     
        ( (!(bonline2=online(l1,Polygon[(i+2)%n])))&& /* ǰһ���˵�ͺ�һ���˵����������� */    
        ((r1=multiply(Polygon[i],Polygon[(i+1)%n],l1.s)*multiply(Polygon[(i+1)%n],Polygon[(i+2)%n],l1.s))>0) ||       
        (bonline3=online(l1,Polygon[(i+2)%n]))&&     /* ��һ������ˮƽ�ߣ�ǰһ���˵�ͺ�һ���˵�����������  */    
            ((r2=multiply(Polygon[i],Polygon[(i+2)%n],l1.s)*multiply(Polygon[(i+2)%n],    
        Polygon[(i+3)%n],l1.s))>0)    
                )    
            )    
        ) c++;    
    }    
    if(c%2 == 1)    
        return 0;    
    else    
        return 2;    
}    
//��q��͹�����polygon��ʱ������true��ע�⣺�����polygonһ��Ҫ��͹�����      
bool InsideConvexPolygon(int vcount,FPOINT polygon[],FPOINT q) // �����������Σ�     
{    
    FPOINT p;    
    LINESEG l;    
    int i;    
    p.x=0;p.y=0;    
    for(i=0;i<vcount;i++) // Ѱ��һ���϶��ڶ����polygon�ڵĵ�p������ζ���ƽ��ֵ     
    {    
        p.x+=polygon[i].x;    
        p.y+=polygon[i].y;    
    }    
    p.x /= vcount;    
    p.y /= vcount;    
   
    for(i=0;i<vcount;i++)    
    {    
        l.s=polygon[i];l.e=polygon[(i+1)%vcount];    
        if(multiply(p,l.e,l.s)*multiply(q,l.e,l.s)<0) /* ��p�͵�q�ڱ�l�����࣬˵����q�϶��ڶ������ */    
        break;    
    }    
    return (i==vcount);    
}

//�жϵ��ڶ�����ڣ�����ο��Բ��Ǽ򵥶���Σ����Բ���͹�����     
bool InsidePolygon(int n,FPOINT polygon[], FPOINT point)      
{         
	if(n==1)
	{      
		return   ((fabs(polygon[0].x-point.x)<EP)   &&   (fabs(polygon[0].y-point.y)<EP));      
	}   
	else if(n==2)
	{      
		LINESEG side;      
		side.s=polygon[0];      
		side.e=polygon[1];      
		return   online(side,point);      
	}      

	int   count=0;      
	LINESEG line;      
	line.s=point;      
	line.e.y=point.y;      
	line.e.x=-INF;      
	for(int i=0;i<n;i++)
	{      
		//   �õ�����ε�һ����       
		LINESEG   side;      
		side.s=polygon[i];      
		side.e=polygon[(i+1)%n];      

		if(online(side,point)   )   {      
			return   true;      
		}      

		//���sideƽ��x����������       
		if(fabs(side.s.y-side.e.y)<EP)
		{      
			continue;      
		}      

		if(online(line,side.s)   )   {      
			if(   side.s.y   >   side.e.y   )   count++;      
		}   else   if(online(line,side.e)   )   {      
			if(   side.e.y   >   side.s.y   )   count++;      
		}   else   if(intersect(line,side)   )   {      
			count++;      
		}      
	}      

	return (count%2==1);   
}

/* �ж�Բ�Ƿ��������ཻ*/    
bool CircleCrossPolygon(int vcount,FPOINT center,float radius,FPOINT polygon[])
{    
	FPOINT P_0=FPOINT(center.x+radius,center.y);
	int N=10;
	for(int i=0;i<N;i++)
	{
		FPOINT P_i=rotate(center,i*2*PI/N,P_0);
		//bool ret=InsideConvexPolygon(vcount,polygon,P_i);
		bool ret=InsidePolygon(vcount,polygon,P_i);
		if(ret)
			return true;
	}
	P_0=rotate(center,PI/N,P_0);
	for(int i=0;i<N;i++)
	{
		FPOINT P_i=rotate(center,i*2*PI/N,P_0);
		//bool ret=InsideConvexPolygon(vcount,polygon,P_i);
		bool ret=InsidePolygon(vcount,polygon,P_i);
		if(ret)
			return true;
	} 
	return false;  
}

/* �ж��߶�LINESEG laser����ֱ��LINE laser�Ƿ���򵥶����polygon�ཻ*/
bool LineCrossPolygon(int vcount,LINESEG laser,FPOINT polygon[])
{ 
	LINESEG u[MAXV];
	for(int i=0;i<vcount-1;i++)
		u[i]=LINESEG(polygon[i],polygon[i+1]);
	if(vcount>2)
		u[vcount-1]=LINESEG(polygon[vcount-1],polygon[0]);
	for(int i=0;i<vcount;i++)
	{
		bool ret=intersect_l(u[i],laser);
		if(ret)
			return true;
	}
	return false;
}

/*  
Ѱ��͹����Grahamɨ�跨��͹������,���Ǹ���һЩ�������,Ȼ������Χס������Щ�����С�ܳ���
PointSetΪ����ĵ㼯----PointSet�������������������ĵ㼯�ǰ�����ʱ�뷽�����еġ�  
chΪ�����͹���ϵĵ㼯----<del:������ʱ�뷽������> ����������еĵ�������ظ��ġ�  
nΪPointSet�еĵ����Ŀ  
lenΪ�����͹���ϵĵ�ĸ���----len����С��n
��PointSet����ǰʱ�Ѿ���һ����ʱ�����еļ򵥶����ʱ�����������ʱ�����еļ򵥶�����п��ܶ���˳��ı��ˣ��п���û��
*/
void Graham_scan(FPOINT PointSet[],FPOINT ch[],int n,int &len)    
{    
    int i,j,k=0,top=2;    
    FPOINT tmp;    
    // ѡȡPointSet��y������С�ĵ�PointSet[k]����������ĵ��ж������ȡ����ߵ�һ��     
    for(i=1;i<n;i++)    
        if ( PointSet[i].y<PointSet[k].y || (PointSet[i].y==PointSet[k].y) && (PointSet[i].x<PointSet[k].x) )    
            k=i;    
    tmp=PointSet[0];    
    PointSet[0]=PointSet[k];    
    PointSet[k]=tmp; // ����PointSet��y������С�ĵ���PointSet[0]     
    for (i=1;i<n-1;i++) /* �Զ��㰴�����PointSet[0]�ļ��Ǵ�С����������򣬼�����ͬ�İ��վ���PointSet[0]�ӽ���Զ�������� */    
    {    
        k=i;    
        for (j=i+1;j<n;j++)    
            if ( multiply(PointSet[j],PointSet[k],PointSet[0])>0 ||  // ���Ǹ�С        
                (multiply(PointSet[j],PointSet[k],PointSet[0])==0) && /* ������ȣ�������� */           
                dist(PointSet[0],PointSet[j])<dist(PointSet[0],PointSet[k])   
               )    
                k=j;    
        tmp=PointSet[i];    
        PointSet[i]=PointSet[k];    
        PointSet[k]=tmp;    
    }    
    ch[0]=PointSet[0];    
    ch[1]=PointSet[1];    
    ch[2]=PointSet[2];    
    for (i=3;i<n;i++)    
    {    
        while (multiply(PointSet[i],ch[top],ch[top-1])>=0)    
            top--;    
        ch[++top]=PointSet[i];    
    }    
    len=top+1;    
}    
// ���������㼯͹�ǣ�����˵��ͬgraham�㷨        
void ConvexClosure(FPOINT PointSet[],FPOINT ch[],int n,int &len)    
{    
    int top=0,i,index,first;    
    float curmax,curcos,curdis;    
    FPOINT tmp;    
    LINESEG l1,l2;    
    bool use[MAXV];    
    tmp=PointSet[0];    
    index=0;    
    // ѡȡy��С�㣬�������һ������ѡȡ�����     
    for(i=1;i<n;i++)    
    {    
        if(PointSet[i].y<tmp.y||PointSet[i].y == tmp.y&&PointSet[i].x<tmp.x)    
        {    
            index=i;    
        }    
        use[i]=false;    
    }    
    tmp=PointSet[index];    
    first=index;    
    use[index]=true;    
   
    index=-1;    
    ch[top++]=tmp;    
    tmp.x-=100;    
    l1.s=tmp;    
    l1.e=ch[0];    
    l2.s=ch[0];    
   
    while(index!=first)    
    {    
        curmax=-100;    
        curdis=0;    
        // ѡȡ�����һ��ȷ���߼н���С�ĵ㣬������ֵ�����     
        for(i=0;i<n;i++)    
        {    
            if(use[i])continue;    
            l2.e=PointSet[i];    
            curcos=cosine(l1,l2); // ����cosֵ��н����ң���Χ�� ��-1 -- 1 ��     
            if(curcos>curmax || fabs(curcos-curmax)<1e-6 && dist(l2.s,l2.e)>curdis)    
            {    
                curmax=curcos;    
                index=i;    
                curdis=dist(l2.s,l2.e);    
            }    
        }    
        use[first]=false;            //��յ�first�������־��ʹ������γɷ�յ�hull     
        use[index]=true;    
        ch[top++]=PointSet[index];    
        l1.s=ch[top-2];    
        l1.e=ch[top-1];    
        l2.s=ch[top-1];    
    }    
    len=top-1;    
}    
/*********************************************************************************************    
    �ж��߶��Ƿ��ڼ򵥶������(ע�⣺����������͹����Σ�������㷨���Ի���)   
    ��Ҫ����һ���߶ε������˵㶼�ڶ�����ڣ�   
    ��Ҫ���������߶κͶ���ε����б߶����ڽ���   
    ��;�� 1. �ж������Ƿ��ڼ򵥶������   
            2. �жϼ򵥶�����Ƿ�����һ���򵥶������   
**********************************************************************************************/    
bool LinesegInsidePolygon(int vcount,FPOINT polygon[],LINESEG l)    
{    
    // �ж��߶�l�Ķ˵��Ƿ񲻶��ڶ������     
    if(!insidepolygon(vcount,polygon,l.s)||!insidepolygon(vcount,polygon,l.e))    
        return false;    
    int top=0,i,j;    
    FPOINT PointSet[MAXV],tmp;    
    LINESEG s;    
   
    for(i=0;i<vcount;i++)    
    {    
        s.s=polygon[i];    
        s.e=polygon[(i+1)%vcount];    
        if(online(s,l.s)) //�߶�l����ʼ�˵����߶�s��     
            PointSet[top++]=l.s;    
        else if(online(s,l.e)) //�߶�l����ֹ�˵����߶�s��     
            PointSet[top++]=l.e;    
        else    
        {    
            if(online(l,s.s)) //�߶�s����ʼ�˵����߶�l��     
                PointSet[top++]=s.s;    
            else if(online(l,s.e)) // �߶�s����ֹ�˵����߶�l��     
                PointSet[top++]=s.e;    
            else    
            {    
                if(intersect(l,s)) // ���ʱ������ཻ���϶����ڽ�������false     
                return false;    
            }    
        }    
    }    
   
    for(i=0;i<top-1;i++) /* ð������x����С������ǰ�棻x������ͬ�ߣ�y����С������ǰ�� */    
    {    
        for(j=i+1;j<top;j++)    
        {    
            if( PointSet[i].x>PointSet[j].x || fabs(PointSet[i].x-PointSet[j].x)<EP && PointSet[i].y>PointSet[j].y )    
            {    
                tmp=PointSet[i];    
                PointSet[i]=PointSet[j];    
                PointSet[j]=tmp;    
            }    
        }    
    }    
   
    for(i=0;i<top-1;i++)    
    {    
        tmp.x=(PointSet[i].x+PointSet[i+1].x)/2; //�õ��������ڽ�����е�     
        tmp.y=(PointSet[i].y+PointSet[i+1].y)/2;    
        if(!insidepolygon(vcount,polygon,tmp))    
            return false;    
    }    
    return true;    
}    
/*********************************************************************************************    
������򵥶����polygon������   
��Ҫ�������漸��������   
    void AddPosPart(); �����ұ���������   
    void AddNegPart(); ���������������   
    void AddRegion(); �����������   
��ʹ�øó���ʱ�������xtr,ytr,wtr,xtl,ytl,wtl���ȫ�ֱ����Ϳ���ʹ��Щ��������ʽ�õ�����,  
��Ҫע�⺯���������͵���Ҫ����Ӧ�仯   
**********************************************************************************************/    
void AddPosPart(float x, float y, float w, float &xtr, float &ytr, float &wtr)    
{    
    if (fabs(wtr + w)<1e-10 ) return; // detect zero regions     
    xtr = ( wtr*xtr + w*x ) / ( wtr + w );    
    ytr = ( wtr*ytr + w*y ) / ( wtr + w );    
    wtr = w + wtr;    
    return;    
}    
void AddNegPart(float x, float y, float w, float &xtl, float &ytl, float &wtl)    
{    
    if ( fabs(wtl + w)<1e-10 )    
        return; // detect zero regions     
   
    xtl = ( wtl*xtl + w*x ) / ( wtl + w );    
    ytl = ( wtl*ytl + w*y ) / ( wtl + w );    
    wtl = w + wtl;    
    return;    
}    
void AddRegion ( float x1, float y1, float x2, float y2, float &xtr, float &ytr,    
        float &wtr, float &xtl, float &ytl, float &wtl )    
{    
    if ( fabs (x1 - x2)< 1e-10 )    
        return;    
   
    if ( x2 > x1 )    
    {    
        AddPosPart ((x2+x1)/2, y1/2, (x2-x1) * y1,xtr,ytr,wtr); /* rectangle ȫ�ֱ����仯�� */    
        AddPosPart ((x1+x2+x2)/3, (y1+y1+y2)/3, (x2-x1)*(y2-y1)/2,xtr,ytr,wtr);       
        // triangle ȫ�ֱ����仯��     
    }    
    else    
    {    
        AddNegPart ((x2+x1)/2, y1/2, (x2-x1) * y1,xtl,ytl,wtl);     
        // rectangle ȫ�ֱ����仯��     
        AddNegPart ((x1+x2+x2)/3, (y1+y1+y2)/3, (x2-x1)*(y2-y1)/2,xtl,ytl,wtl);     
        // triangle  ȫ�ֱ����仯��     
    }    
}    
FPOINT cg_simple(int vcount,FPOINT polygon[])    
{    
    float xtr,ytr,wtr,xtl,ytl,wtl;           
    //ע�⣺ �����xtr,ytr,wtr,xtl,ytl,wtl�ĳ�ȫ�ֱ���������Ҫɾȥ     
    FPOINT p1,p2,tp;    
    xtr = ytr = wtr = 0.0;    
    xtl = ytl = wtl = 0.0;    
    for(int i=0;i<vcount;i++)    
    {    
        p1=polygon[i];    
        p2=polygon[(i+1)%vcount];    
        AddRegion(p1.x,p1.y,p2.x,p2.y,xtr,ytr,wtr,xtl,ytl,wtl); //ȫ�ֱ����仯��     
    }    
    tp.x = (wtr*xtr + wtl*xtl) / (wtr + wtl);    
    tp.y = (wtr*ytr + wtl*ytl) / (wtr + wtl);    
    return tp;    
}    
// ��͹����ε�����,Ҫ���������ΰ���ʱ������     
FPOINT gravitycenter(int vcount,FPOINT polygon[])    
{    
    FPOINT tp;    
    float x,y,s,x0,y0,cs,k;    
    x=0;y=0;s=0;    
    for(int i=1;i<vcount-1;i++)    
    {    
        x0=(polygon[0].x+polygon[i].x+polygon[i+1].x)/3;    
        y0=(polygon[0].y+polygon[i].y+polygon[i+1].y)/3; //��ǰ�����ε�����     
        cs=multiply(polygon[i],polygon[i+1],polygon[0])/2;    
        //�������������ֱ�����øù�ʽ���     
        if(fabs(s)<1e-20)    
        {    
            x=x0;y=y0;s+=cs;continue;    
        }    
        k=cs/s; //���������     
        x=(x+k*x0)/(1+k);    
        y=(y+k*y0)/(1+k);    
        s += cs;    
    }    
    tp.x=x;    
    tp.y=y;    
    return tp;    
}    
   
/************************************************  
����һ�򵥶���Σ��ҳ�һ���϶��ڸö�����ڵĵ�   
����1 ��ÿ�������������һ��͹����   
����2 ��������>=4�ļ򵥶����������һ���Խ���   
����  �� x���������С�ĵ�϶���͹����   
    y���������С�ĵ�϶���͹����              
************************************************/    
FPOINT a_point_insidepoly(int vcount,FPOINT polygon[])    
{    
    FPOINT v,a,b,r;    
    int i,index;    
    v=polygon[0];    
    index=0;    
    for(i=1;i<vcount;i++) //Ѱ��һ��͹����     
    {    
        if(polygon[i].y<v.y)    
        {    
            v=polygon[i];    
            index=i;    
        }    
    }    
    a=polygon[(index-1+vcount)%vcount]; //�õ�v��ǰһ������     
    b=polygon[(index+1)%vcount]; //�õ�v�ĺ�һ������     
    FPOINT tri[3],q;    
    tri[0]=a;tri[1]=v;tri[2]=b;    
    float md=INF;    
    int in1=index;    
    bool bin=false;    
    for(i=0;i<vcount;i++) //Ѱ����������avb�����붥��v����Ķ���q     
    {    
        if(i == index)continue;    
        if(i == (index-1+vcount)%vcount)continue;    
        if(i == (index+1)%vcount)continue;    
        if(!InsideConvexPolygon(3,tri,polygon[i]))continue;    
        bin=true;    
        if(dist(v,polygon[i])<md)    
        {    
            q=polygon[i];    
            md=dist(v,q);    
        }    
    }    
    if(!bin) //û�ж�����������avb�ڣ������߶�ab�е�     
    {    
        r.x=(a.x+b.x)/2;    
        r.y=(a.y+b.y)/2;    
        return r;    
    }    
    r.x=(v.x+q.x)/2; //�����߶�vq���е�     
    r.y=(v.y+q.y)/2;    
    return r;    
}    
/***********************************************************************************************  
��Ӷ������һ��p������һ���򵥶���ε�����,������ڷ����е�,����rp�������е�,lp�����е�   
ע�⣺p��һ��Ҫ�ڶ������ ,���붥����������ʱ������   
ԭ ��    ������ڶ�����ڿ϶�������;͹�������Ψһ�������е�,������ξͿ����ж����������е�;   
        ���polygon��͹����Σ��е�ֻ������ֻҪ�ҵ��Ϳ���,���Ի�����㷨   
        ����ǰ�����λ���һ���㷨�������:���󰼶���ε�͹��,Ȼ����͹��������   
/***********************************************************************************************/    
void pointtangentpoly(int vcount,FPOINT polygon[],FPOINT p,FPOINT &rp,FPOINT &lp)    
{    
    LINESEG ep,en;    
    bool blp,bln;    
    rp=polygon[0];    
    lp=polygon[0];    
    for(int i=1;i<vcount;i++)    
    {    
        ep.s=polygon[(i+vcount-1)%vcount];    
        ep.e=polygon[i];    
        en.s=polygon[i];    
        en.e=polygon[(i+1)%vcount];    
        blp=multiply(ep.e,p,ep.s)>=0;                // p is to the left of pre edge     
        bln=multiply(en.e,p,en.s)>=0;                // p is to the left of next edge     
        if(!blp&&bln)    
        {    
            if(multiply(polygon[i],rp,p)>0)           // polygon[i] is above rp     
            rp=polygon[i];    
        }    
        if(blp&&!bln)    
        {    
            if(multiply(lp,polygon[i],p)>0)           // polygon[i] is below lp     
            lp=polygon[i];    
        }    
    }    
    return ;    
}    
// ��������polygon�ĺ˴��ڣ�����true�����غ��ϵ�һ��p.���㰴��ʱ�뷽������      
bool core_exist(int vcount,FPOINT polygon[],FPOINT &p)    
{    
    int i,j,k;    
    LINESEG l;    
    LINE lineset[MAXV];    
    for(i=0;i<vcount;i++)    
    {    
        lineset[i]=makeline(polygon[i],polygon[(i+1)%vcount]);    
    }    
    for(i=0;i<vcount;i++)    
    {    
        for(j=0;j<vcount;j++)    
        {    
            if(i == j)continue;    
            if(lineintersect(lineset[i],lineset[j],p))    
            {    
                for(k=0;k<vcount;k++)    
                {    
                    l.s=polygon[k];    
                    l.e=polygon[(k+1)%vcount];    
                    if(multiply(p,l.e,l.s)>0)         
                    //����ζ��㰴��ʱ�뷽�����У��˿϶���ÿ���ߵ��������     
                    break;    
                }    
                if(k == vcount)             //�ҵ���һ�����ϵĵ�     
                break;    
            }    
        }    
        if(j<vcount) break;    
    }    
    if(i<vcount)    
        return true;    
    else    
        return false;    
}    
/*************************\   
*                        *   
* Բ�Ļ�������           *   
*                        *   
\*************************/    
/******************************************************************************  
����ֵ �� ��p��Բ��(�����߽�)ʱ������true   
��;  �� ��ΪԲΪ͹���������жϵ㼯�����ߣ�������Ƿ���Բ��ʱ��  
    ֻ��Ҫ��һ�жϵ��Ƿ���Բ�ڼ��ɡ�   
*******************************************************************************/    
bool point_in_circle(FPOINT o,float r,FPOINT p)    
{    
    float d2=(p.x-o.x)*(p.x-o.x)+(p.y-o.y)*(p.y-o.y);    
    float r2=r*r;    
    return d2<r2||fabs(d2-r2)<EP;    
}    
/******************************************************************************  
�� ; ���󲻹��ߵ�����ȷ��һ��Բ   
�� �� ��������p1,p2,p3   
����ֵ ��������㹲�ߣ�����false����֮������true��Բ����q���أ��뾶��r����   
*******************************************************************************/    
bool cocircle(FPOINT p1,FPOINT p2,FPOINT p3,FPOINT &q,float &r)    
{    
    float x12=p2.x-p1.x;    
    float y12=p2.y-p1.y;    
    float x13=p3.x-p1.x;    
    float y13=p3.y-p1.y;    
    float z2=x12*(p1.x+p2.x)+y12*(p1.y+p2.y);    
    float z3=x13*(p1.x+p3.x)+y13*(p1.y+p3.y);    
    float d=2.0*(x12*(p3.y-p2.y)-y12*(p3.x-p2.x));    
    if(fabs(d)<EP) //���ߣ�Բ������     
        return false;    
    q.x=(y13*z2-y12*z3)/d;    
    q.y=(x12*z3-x13*z2)/d;    
    r=dist(p1,q);    
    return true;    
}    
int line_circle(LINE l,FPOINT o,float r,FPOINT &p1,FPOINT &p2)    
{    
    return true;    
}    
   
/**************************\   
*                         *   
* ���εĻ�������          *   
*                         *   
\**************************/    
/*   
˵������Ϊ���ε������ԣ������㷨���Ի���   
1.�жϾ����Ƿ������   
ֻҪ�жϸõ�ĺ�������������Ƿ���ھ��ε����ұߺ����±�֮�䡣   
2.�ж��߶Ρ����ߡ�������Ƿ��ھ�����   
��Ϊ�����Ǹ�͹��������ֻҪ�ж����ж˵��Ƿ��ھ����оͿ����ˡ�   
3.�ж�Բ�Ƿ��ھ�����   
Բ�ھ����еĳ�Ҫ�����ǣ�Բ���ھ�������Բ�İ뾶С�ڵ���Բ�ĵ������ıߵľ������Сֵ��   
*/    
// ��֪���ε���������(a,b,c)��������ĸ�����d������. ע�⣺��֪��������������������     
FPOINT rect4th(FPOINT a,FPOINT b,FPOINT c)    
{    
    FPOINT d;    
    if(fabs(dotmultiply(a,b,c))<EP) // ˵��c����ֱ�ǹսǴ�     
    {    
        d.x=a.x+b.x-c.x;    
        d.y=a.y+b.y-c.y;    
    }    
    if(fabs(dotmultiply(a,c,b))<EP) // ˵��b����ֱ�ǹսǴ�     
    {    
        d.x=a.x+c.x-b.x;    
        d.y=a.y+c.y-b.x;    
    }    
    if(fabs(dotmultiply(c,b,a))<EP) // ˵��a����ֱ�ǹսǴ�     
    {    
        d.x=c.x+b.x-a.x;    
        d.y=c.y+b.y-a.y;    
    }    
    return d;    
}    
   
/*************************\   
*                       *   
* �����㷨������       *   
*                       *   
\*************************/    
/*   
��δʵ�ֵ��㷨��   
1. ������㼯����СԲ   
2. �����εĽ�   
3. �򵥶���ε������ʷ�   
4. Ѱ�Ұ����㼯����С����   
5. ���ߵĻ���   
6. �жϾ����Ƿ��ھ�����   
7. �жϾ����ܷ���ھ�����   
8. ���β���������ܳ�   
9. ���β�������   
10.���β��ıհ�   
11.���εĽ�   
12.�㼯�е�������   
13.����εĲ�   
14.Բ�Ľ��벢   
15.ֱ����Բ�Ĺ�ϵ   
16.�߶���Բ�Ĺ�ϵ   
17.�����εĺ˼��������   
18.��㼯�в��ཻ��� railwai   
*//*   
Ѱ�Ұ����㼯����С����   
ԭ���þ�������һ������㼯��͹�ǵ�ĳ���߹���   
First take the convex hull of the points. Let the resulting convex   
polygon be P. It has been known for some time that the minimum   
area rectangle enclosing P must have one rectangle side flush with   
(i.e., collinear with and overlapping) one edge of P. This geometric   
fact was used by Godfried Toussaint to develop the "rotating calipers"   
algorithm in a hard-to-find 1983 paper, "Solving Geometric Problems   
with the Rotating Calipers" (Proc. IEEE MELECON). The algorithm   
rotates a surrounding rectangle from one flush edge to the next,   
keeping track of the minimum area for each edge. It achieves O(n)   
time (after hull computation). See the "Rotating Calipers Homepage"   
http://www.cs.mcgill.ca/~orm/rotcal.frame.html for a description   
and applet.   
*//*   
���ߵĻ��� α�����£�   
Input: tol = the approximation tolerance   
L = {V0,V1,...,Vn-1} is any n-vertex polyline   
  
Set start = 0;   
Set k = 0;   
Set W0 = V0;   
for each vertex Vi (i=1,n-1)   
{   
if Vi is within tol from Vstart   
then ignore it, and continue with the next vertex   
  
Vi is further than tol away from Vstart   
so add it as a new vertex of the reduced polyline   
Increment k++;   
Set Wk = Vi;   
Set start = i; as the new initial vertex   
}   
  
Output: W = {W0,W1,...,Wk-1} = the k-vertex simplified polyline   
*/    
/********************\   
*                   *   
* ����                *   
*                   *   
\********************/    
   
//��Բ��ϵ��     
/* ��Բ��   
���룺 return 1��   
���У� return 2��   
�ཻ�� return 3��   
���У� return 4��   
�ں��� return 5��   
*/    
int CircleRelation(FPOINT p1, float r1, FPOINT p2, float r2)    
{    
    float d = sqrt( (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y) );    
   
    if( fabs(d-r1-r2) < EP ) // ���뱣֤ǰ����if�ȱ��ж���     
        return 2;    
    if( fabs(d-fabs(r1-r2)) < EP )    
        return 4;    
    if( d > r1+r2 )    
        return 1;    
    if( d < fabs(r1-r2) )    
        return 5;    
    if( fabs(r1-r2) < d && d < r1+r2 )    
        return 3;    
    return 0; // indicate an error!     
}    
//�ж�Բ�Ƿ��ھ����ڣ�    
// �ж�Բ�Ƿ��ھ����ڣ��Ǿͷ���true�������ˮƽ�������ĸ����������Ͽ�ʼ��˳ʱ�����У�     
// ����ptoldist�������ڵ�4ҳ     
bool CircleRecRelation(FPOINT pc, float r, FPOINT pr1, FPOINT pr2, FPOINT pr3, FPOINT pr4)    
{    
    if( pr1.x < pc.x && pc.x < pr2.x && pr3.y < pc.y && pc.y < pr2.y )    
    {    
        LINESEG line1(pr1, pr2);    
        LINESEG line2(pr2, pr3);    
        LINESEG line3(pr3, pr4);    
        LINESEG line4(pr4, pr1);    
        if( r<ptoldist(pc,line1) && r<ptoldist(pc,line2) &&   r<ptoldist(pc,line3) && r<ptoldist(pc,line4) )    
            return true;    
    }    
    return false;    
}    
//�㵽ƽ��ľ��룺     
//�㵽ƽ��ľ���,ƽ����һ��ʽ��ʾax+by+cz+d=0     
float P2planeDist(float x, float y, float z, float a, float b, float c, float d)    
{    
    return fabs(a*x+b*y+c*z+d) / sqrt(a*a+b*b+c*c);    
}    
//���Ƿ���ֱ��ͬ�ࣺ    
//�������Ƿ���ֱ��ͬ�࣬���򷵻�true     
bool SameSide(FPOINT p1, FPOINT p2, LINE line)    
{    
    return (line.a * p1.x + line.b * p1.y + line.c) *    
    (line.a * p2.x + line.b * p2.y + line.c) > 0;    
}   
//���淴���ߣ�    
// ��֪�����ߡ����棬�����ߡ�     
// a1,b1,c1Ϊ����ֱ�߷���(a1 x + b1 y + c1 = 0 ,��ͬ)ϵ��;      
//a2,b2,c2Ϊ�����ֱ�߷���ϵ��;      
//a,b,cΪ�����ֱ�߷���ϵ��.     
// �����з���ģ�ʹ��ʱע�⣺���������:<-b2,a2>�����������:<b,-a>.     
// ��Ҫ���ǽ���п��ܻ���"negative zeros"     
void reflect(float a1,float b1,float c1,float a2,float b2,float c2,float &a,float &b,float &c)    
{    
    float n,m;    
    float tpb,tpa;    
    tpb=b1*b2+a1*a2;    
    tpa=a2*b1-a1*b2;    
    m=(tpb*b1+tpa*a1)/(b1*b1+a1*a1);    
    n=(tpa*b1-tpb*a1)/(b1*b1+a1*a1);    
    if(fabs(a1*b2-a2*b1)<1e-20)    
    {    
        a=a2;b=b2;c=c2;    
        return;    
    }    
    float xx,yy; //(xx,yy)���������뾵��Ľ��㡣     
    xx=(b1*c2-b2*c1)/(a1*b2-a2*b1);    
    yy=(a2*c1-a1*c2)/(a1*b2-a2*b1);    
    a=n;    
    b=-m;    
    c=m*yy-xx*n;    
}    
//���ΰ�����     
// ����2��C��D���Ƿ���1��A��B����    
bool r2inr1(float A,float B,float C,float D)     
{    
    float X,Y,L,K,DMax;    
    if (A < B)    
    {    
        float tmp = A;    
        A = B;    
        B = tmp;    
    }    
    if (C < D)    
    {    
        float tmp = C;    
        C = D;    
        D = tmp;    
    }    
    if (A > C && B > D)                 // trivial case      
        return true;    
    else    
        if (D >= B)    
            return false;    
        else    
        {    
            X = sqrt(A * A + B * B);         // outer rectangle's diagonal      
            Y = sqrt(C * C + D * D);         // inner rectangle's diagonal      
            if (Y < B) // check for marginal conditions     
                return true; // the inner rectangle can freely rotate inside     
            else    
                if (Y > X)    
                    return false;    
                else    
                {    
                    L = (B - sqrt(Y * Y - A * A)) / 2;    
                    K = (A - sqrt(Y * Y - B * B)) / 2;    
                    DMax = sqrt(L * L + K * K);    
                    if (D >= DMax)    
                    return false;    
                    else    
                    return true;    
                }    
        }    
}    
//��Բ���㣺     
// ��Բ�Ѿ��ཻ�����У�     
void  c2point(FPOINT p1,float r1,FPOINT p2,float r2,FPOINT &rp1,FPOINT &rp2)    
{    
    float a,b,r;    
    a=p2.x-p1.x;    
    b=p2.y-p1.y;    
    r=(a*a+b*b+r1*r1-r2*r2)/2;    
    if(a==0&&b!=0)    
    {    
        rp1.y=rp2.y=r/b;    
        rp1.x=sqrt(r1*r1-rp1.y*rp1.y);    
        rp2.x=-rp1.x;    
    }    
    else if(a!=0&&b==0)    
    {    
        rp1.x=rp2.x=r/a;    
        rp1.y=sqrt(r1*r1-rp1.x*rp2.x);    
        rp2.y=-rp1.y;    
    }    
    else if(a!=0&&b!=0)    
    {    
        float delta;    
        delta=b*b*r*r-(a*a+b*b)*(r*r-r1*r1*a*a);    
        rp1.y=(b*r+sqrt(delta))/(a*a+b*b);    
        rp2.y=(b*r-sqrt(delta))/(a*a+b*b);    
        rp1.x=(r-b*rp1.y)/a;    
        rp2.x=(r-b*rp2.y)/a;    
    }    
   
    rp1.x+=p1.x;    
    rp1.y+=p1.y;    
    rp2.x+=p1.x;    
    rp2.y+=p1.y;    
}    
//��Բ���������    
// ���뱣֤�ཻ     
float c2area(FPOINT p1,float r1,FPOINT p2,float r2)    
{    
    FPOINT rp1,rp2;    
    c2point(p1,r1,p2,r2,rp1,rp2);    
   
    if(r1>r2) //��֤r2>r1     
    {    
        swap(p1,p2);    
        swap(r1,r2);    
    }    
    float a,b,rr;    
    a=p1.x-p2.x;    
    b=p1.y-p2.y;    
    rr=sqrt(a*a+b*b);    
   
    float dx1,dy1,dx2,dy2;    
    float sita1,sita2;    
    dx1=rp1.x-p1.x;    
    dy1=rp1.y-p1.y;    
    dx2=rp2.x-p1.x;    
    dy2=rp2.y-p1.y;    
    sita1=acos((dx1*dx2+dy1*dy2)/r1/r1);    
   
    dx1=rp1.x-p2.x;    
    dy1=rp1.y-p2.y;    
    dx2=rp2.x-p2.x;    
    dy2=rp2.y-p2.y;    
    sita2=acos((dx1*dx2+dy1*dy2)/r2/r2);    
    float s=0;    
    if(rr<r2)//�ཻ��Ϊ�Ż�     
        s=r1*r1*(PI-sita1/2+sin(sita1)/2)+r2*r2*(sita2-sin(sita2))/2;    
    else//�ཻ��Ϊ�ӻ�     
        s=(r1*r1*(sita1-sin(sita1))+r2*r2*(sita2-sin(sita2)))/2;    
   
    return s;    
}    
//Բ��ֱ�߹�ϵ��     
//0----���� 1----���� 2----�ཻ     
int clpoint(FPOINT p,float r,float a,float b,float c,FPOINT &rp1,FPOINT &rp2)    
{    
    int res=0;    
   
    c=c+a*p.x+b*p.y;    
    float tmp;    
    if(a==0&&b!=0)    
    {    
        tmp=-c/b;    
        if(r*r<tmp*tmp)    
            res=0;    
        else if(r*r==tmp*tmp)    
        {    
            res=1;    
            rp1.y=tmp;    
            rp1.x=0;    
        }    
        else    
        {    
            res=2;    
            rp1.y=rp2.y=tmp;    
            rp1.x=sqrt(r*r-tmp*tmp);    
            rp2.x=-rp1.x;    
        }    
    }    
    else if(a!=0&&b==0)    
    {    
        tmp=-c/a;    
        if(r*r<tmp*tmp)    
            res=0;    
        else if(r*r==tmp*tmp)    
        {    
            res=1;    
            rp1.x=tmp;    
            rp1.y=0;    
        }    
        else    
        {    
            res=2;    
            rp1.x=rp2.x=tmp;    
            rp1.y=sqrt(r*r-tmp*tmp);    
            rp2.y=-rp1.y;    
        }    
    }    
    else if(a!=0&&b!=0)    
    {    
        float delta;    
        delta=b*b*c*c-(a*a+b*b)*(c*c-a*a*r*r);    
        if(delta<0)    
            res=0;    
        else if(delta==0)    
        {    
            res=1;    
            rp1.y=-b*c/(a*a+b*b);    
            rp1.x=(-c-b*rp1.y)/a;    
        }    
        else    
        {    
            res=2;    
            rp1.y=(-b*c+sqrt(delta))/(a*a+b*b);    
            rp2.y=(-b*c-sqrt(delta))/(a*a+b*b);    
            rp1.x=(-c-b*rp1.y)/a;    
            rp2.x=(-c-b*rp2.y)/a;    
        }    
    }    
    rp1.x+=p.x;    
    rp1.y+=p.y;    
    rp2.x+=p.x;    
    rp2.y+=p.y;    
    return res;    
}    
//����Բ��     
void incircle(FPOINT p1,FPOINT p2,FPOINT p3,FPOINT &rp,float &r)    
{    
    float dx31,dy31,dx21,dy21,d31,d21,a1,b1,c1;    
    dx31=p3.x-p1.x;    
    dy31=p3.y-p1.y;    
    dx21=p2.x-p1.x;    
    dy21=p2.y-p1.y;    
   
    d31=sqrt(dx31*dx31+dy31*dy31);    
    d21=sqrt(dx21*dx21+dy21*dy21);    
    a1=dx31*d21-dx21*d31;    
    b1=dy31*d21-dy21*d31;    
    c1=a1*p1.x+b1*p1.y;    
   
    float dx32,dy32,dx12,dy12,d32,d12,a2,b2,c2;    
    dx32=p3.x-p2.x;    
    dy32=p3.y-p2.y;    
    dx12=-dx21;    
    dy12=-dy21;    
   
    d32=sqrt(dx32*dx32+dy32*dy32);    
    d12=d21;    
    a2=dx12*d32-dx32*d12;    
    b2=dy12*d32-dy32*d12;    
    c2=a2*p2.x+b2*p2.y;    
   
    rp.x=(c1*b2-c2*b1)/(a1*b2-a2*b1);    
    rp.y=(c2*a1-c1*a2)/(a1*b2-a2*b1);    
    r=fabs(dy21*rp.x-dx21*rp.y+dx21*p1.y-dy21*p1.x)/d21;    
}    
//���е㣺     
// p---Բ�����꣬ r---Բ�뾶�� sp---Բ��һ�㣬 rp1,rp2---�е�����     
void cutpoint(FPOINT p,float r,FPOINT sp,FPOINT &rp1,FPOINT &rp2)    
{    
    FPOINT p2;    
    p2.x=(p.x+sp.x)/2;    
    p2.y=(p.y+sp.y)/2;    
   
    float dx2,dy2,r2;    
    dx2=p2.x-p.x;    
    dy2=p2.y-p.y;    
    r2=sqrt(dx2*dx2+dy2*dy2);    
    c2point(p,r,p2,r2,rp1,rp2);    
}    
//�߶ε���������     
/* l2��l1����/�ҷ���l1Ϊ��׼�ߣ�   
����  0   �� �غϣ�   
����  1   �� ������   
����  �C1 �� ������   
*/    
int rotat(LINESEG l1,LINESEG l2)    
{    
    float dx1,dx2,dy1,dy2;    
    dx1=l1.s.x-l1.e.x;    
    dy1=l1.s.y-l1.e.y;    
    dx2=l2.s.x-l2.e.x;    
    dy2=l2.s.y-l2.e.y;    
   
    float d;    
    d=dx1*dy2-dx2*dy1;    
    if(d==0)    
        return 0;    
    else if(d>0)    
        return -1;    
    else    
        return 1;    
}    
/*  
��ʽ��   
  
�����깫ʽ��   
ֱ������Ϊ P(x, y, z) ʱ����Ӧ����������(rsin��cos��, rsin��sin��, rcos��),���Ц�������OP��Z��ļнǣ���Χ[0����]����OP��XOY���ϵ�ͶӰ��X������ǣ���Χ[0��2��]    
  
ֱ�ߵ�һ�㷽��ת�����������̣�   
ax+by+c=0   
x-x0     y-y0   
   ------ = ------- // (x0,y0)Ϊֱ����һ�㣬m,nΪ����   
m        n   
ת����ϵ��   
a=n��b=-m��c=m��y0-n��x0��   
m=-b; n=a;   
  
����ƽ�淽�̣�   
����ΪP1��P2��P3   
������  M1=P2-P1; M2=P3-P1;   
ƽ�淨������  M=M1 x M2 ����   
ƽ�淽�̣�    M.i(x-P1.x)+M.j(y-P1.y)+M.k(z-P1.z)=0   
*/ 