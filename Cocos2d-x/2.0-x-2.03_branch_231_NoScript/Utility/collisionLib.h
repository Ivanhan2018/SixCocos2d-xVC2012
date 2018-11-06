#ifndef __COLLISION_LIB_H__
#define __COLLISION_LIB_H__

#include <cocos2d.h>

#include<math.h>


// ����ֱ�߽���
// ֱ�� 1 �ϵ����㣺(ax1, ay1), (ax2, ay2)
// ֱ�� 2 �ϵ����㣺(bx1, by1), (bx2, by2)
// ����ֵ��true: �н��㣬������ (ix, iy) ��
//    ��false: ��ֱ��ƽ��
bool Intersection(float ax1, float ay1, float ax2, float ay2, float bx1, float by1, float bx2, float by2, float *ix, float *iy)
{
 float d = (ay2-ay1) * (bx2-bx1) - (by2-by1) * (ax2-ax1);
#if 1
 if (fabs(d)<0.01)
#else
 if (d==0)
#endif
  return false; // ��ֱ��ƽ�о��˳����������Ϊ 0 �����

 *ix = (  (ax2-ax1)*(bx2-bx1)*(by1-ay1)+(ay2-ay1)*(bx2-bx1)*ax1-(by2-by1)*(ax2-ax1)*bx1  ) / d;
 *iy = (  (ay2-ay1)*(by2-by1)*(bx1-ax1)+(ax2-ax1)*(by2-by1)*ay1-(bx2-bx1)*(ay2-ay1)*by1  ) / -d;

 return true;
}

//���߶�AB���߶�CD�Ľ���
bool segment_cross_segment(CCPoint& a,CCPoint& b,CCPoint& c,CCPoint& d,CCPoint& cross_point)
{
	CCPoint retpt;
	if (Intersection(a.x,a.y,b.x,b.y,c.x,c.y,d.x,d.y,&retpt.x,&retpt.y) )
	{
        //�����~AB���ɵıȣ�����һ������B���غ�
		float k=(retpt.x-a.x)/(b.x-retpt.x);
		if(k>0)
		{
		   cross_point=retpt;
		   return true;
		}
		else
			return false;
	}
	else
		return false;
}

//��������������߶�pt1,pt2(�ڵ�pt1�п����ھ��α���)�����pt[4](������Ϊ01,12,23,30)��Ψһ����
CCPoint segment_cross_Rect(CCPoint pt[4],CCPoint pt1,CCPoint pt2)
{   
	CCPoint cross_point[4];
	bool ret[4]={false,false,false,false};
    ret[0]=segment_cross_segment(pt1,pt2,pt[0],pt[1],cross_point[0]);  
    ret[1]=segment_cross_segment(pt1,pt2,pt[1],pt[2],cross_point[1]); 
    ret[2]=segment_cross_segment(pt1,pt2,pt[2],pt[3],cross_point[2]);  
    ret[3]=segment_cross_segment(pt1,pt2,pt[3],pt[0],cross_point[3]); 
	for(int i=0;i<4;i++)
	{
		if(ret[i] && (cross_point[i].x!=pt1.x ||cross_point[i].y!=pt1.y) )
		{
			return cross_point[i];
		}
	}
	return CCPoint(-1,-1);//����ֵ
}


bool IsEqual(CCPoint& pt1,CCPoint& pt2,float error)
{
	if(fabs(pt1.x-pt2.x)<error && fabs(pt1.y-pt2.y)<error)
		return true;
	else
		return false;
}

//��������������߶�pt1,pt2(�ڵ�pt1�п����ھ��α���)�����pt[4](������Ϊ��߽�01,�ϱ߽�12,�ұ߽�23,�±߽�30)��Ψһ����
CCPoint segment_cross_Rect(CCPoint pt[4],CCPoint pt1,CCPoint pt2,float error,int& z0)
{   
	CCPoint cross_point[4];
	bool ret[4]={false,false,false,false};
    ret[0]=segment_cross_segment(pt1,pt2,pt[0],pt[1],cross_point[0]);  
    ret[1]=segment_cross_segment(pt1,pt2,pt[1],pt[2],cross_point[1]); 
    ret[2]=segment_cross_segment(pt1,pt2,pt[2],pt[3],cross_point[2]);  
    ret[3]=segment_cross_segment(pt1,pt2,pt[3],pt[0],cross_point[3]);
	/*
		��������z0��ȡֵ��
		0246�ֱ������£����ϣ����ϣ����£�1���ϱ߽磬3���ұ߽磬5���±߽磬7����߽�
		0=4,2=6,3=7,1=5
	*/
	//int w=pt[3].x-pt[3].x;
	//int h=pt[1].y-pt[0].y;
    CCPoint retpt;
	for(int i=0;i<4;i++)
	{
#if 1
		//if(ret[i] && ((pow(cross_point[i].x-pt1.x,2)+pow(cross_point[i].y-pt1.y,2))>0.01) )
        if(ret[i] && (fabs(cross_point[i].x-pt1.x)>0.01 || fabs(cross_point[i].y-pt1.y)>0.01) )
#else
		if(ret[i] && (cross_point[i].x!=pt1.x ||cross_point[i].y!=pt1.y) )
#endif
		{
			retpt=cross_point[i];
			break;
		}
	}
	int num=0;
	for(int i=0;i<4;i++)
	if(ret[i])num++;
	if(num==1)//z0=1,3
	{
		bool isCorner=false;
		for(int i=0;i<4;i++)
		if(IsEqual(retpt,pt[i],error))
		{
		    num=2;
			retpt=pt[i];
			isCorner=true;
			break;
		}
		if(!isCorner)
		{
			if(fabs(retpt.x-pt[0].x)<error)
			{
						 z0=3;
						 retpt.x=pt[0].x;
						 return retpt;
			}
			if(fabs(retpt.x-pt[3].x)<error)
			{
						  z0=3;
						  retpt.x=pt[3].x;
						 return retpt;
			}
			if(fabs(retpt.y-pt[0].y)<error)
			{
					   z0=1;
					   retpt.y=pt[0].y;
					  return retpt;
			}
			if(fabs(retpt.y-pt[1].y)<error)
			{
					   z0=1;
					   retpt.y=pt[1].y;
					  return retpt;
			}
		}
	}
	if(num==2)//z_0=0,2
	{
		int retz0[4]={0,2,0,2};
		for(int i=0;i<4;i++)
		if(IsEqual(retpt,pt[i],error))
		{
		   z0=retz0[i];
		   return pt[i];
		}
	}
	z0=-1;//����ֵ
	return CCPoint(-1,-1);//����ֵ
}

/*
��������������tolua++����C++<->LUA�����ӿ�
*/
CCPoint segment_cross_Rect(CCPoint pt[4],CCPoint pt1,CCPoint pt2,float error)
{
    int z0=-1;
	return segment_cross_Rect(pt,pt1,pt2,error,z0);
}

CCPoint getReflex(CCPoint pt[4],CCPoint pt1,CCPoint pt2,float error)
{
	int z0=-1;
	static CCPoint Reflexs[4]={CCPoint(1,-1),CCPoint(1,0),CCPoint(1,1),CCPoint(0,1)};
	segment_cross_Rect(pt,pt1,pt2,error,z0);
	if(z0==-1)
		return CCPoint(0,0);//����ֵ
	else
		return Reflexs[z0];
}

//int _tmain(int argc, _TCHAR* argv[])
//{
//	/*
//	CCPoint pt[4]={CCPoint(0,0),CCPoint(1000,0),CCPoint(1000,600),CCPoint(0,600)};
//	CCPoint pt1=CCPoint(200,300);
//	CCPoint pt2=CCPoint(1200,1300);
//	//�������꣺x=1000.000000,y=1100.000000
//    */
//
//	//CCPoint pt[4]={CCPoint(0,0),CCPoint(0,650),CCPoint(1024,650),CCPoint(1024,0)};
//	//CCPoint pt1=CCPoint(775,616);
//	//CCPoint pt2=CCPoint(1067,389);
//	//CCPoint ptret=segment_cross_Rect(pt,pt1,pt2);
//	//printf("�������꣺x=%f,y=%f\n",ptret.x,ptret.y);//�������꣺x=1024.000000,y=422.428070
//	//CCPoint ptz0[4]={CCPoint(1,-1),CCPoint(1,0),CCPoint(1,1),CCPoint(0,1)};
//	//char *sz[4]={"���»�����","���±߽�","���ϻ�����","���ұ߽�"};
//	//int z0=-1;
//	//CCPoint ptret1=segment_cross_Rect(pt,pt1,pt2,10,z0);
//	//printf("�������꣺x=%f,y=%f,��������=%d(%s)\n",ptret1.x,ptret1.y,z0,sz[z0]);//�������꣺x=1024.000000,y=422.428070,��������=3(���ұ߽�)
//	return 0;
//}

CCPoint segment_cross_Rect(CCPoint v1,CCPoint v2,CCPoint v3,CCPoint v4,CCPoint pt1,CCPoint pt2,float error)
{
	CCPoint ptArray[4]={v1, v2, v3, v4};
	return segment_cross_Rect(ptArray, pt1, pt2, error);
}

CCPoint getReflex(CCPoint v1,CCPoint v2,CCPoint v3,CCPoint v4,CCPoint pt1,CCPoint pt2,float error)
{
	CCPoint ptArray[4]={v1, v2, v3, v4};
	return getReflex(ptArray, pt1, pt2,error);
}
#endif