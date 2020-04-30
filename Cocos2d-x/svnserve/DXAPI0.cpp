#include<iostream>
#include"DXAPI.h"
using namespace std;

//欧拉角向四元数的转换
//四元数向旋转矩阵的转换
//旋转矩阵向四元数的转换

int main()
{
    {
		D3DVECTOR i,j,k;
		i=D3DVECTOR(1,0,0);
		j=D3DVECTOR(0,1,0);
		k=D3DVECTOR(0,0,1);
		//D3DVECTOR ij=i*j;
		//D3DVECTOR jk=j*k;
		//D3DVECTOR ki=k*i;			
		cout<<"i*j="<<i*j<<endl;
		cout<<"j*k="<<j*k<<endl;
		cout<<"k*i="<<k*i<<endl;
	}

	{
		D3DXQUATERNION e;
		e=D3DXQUATERNION(0,0,0,1);		
		D3DVECTOR E=GetEulerAngle(e);
		cout<<"E="<<E<<endl;
		
		D3DXQUATERNION q;
		//q=D3DXQUATERNION(0.287301,0.342528,0.694719,-0.56347);
		q=D3DXQUATERNION(-0.56347,0.287301,0.342528,0.694719);//Q=[1.32148,-0.626224,1.40921]phi = 1.32148229302237 ; omiga = 0.626224465189316 ; kappa = -1.4092143985971;
		D3DVECTOR Q=GetEulerAngle(q);
		cout<<"Q="<<Q<<endl;		
		
		D3DXQUATERNION i,j,k;
		i=D3DXQUATERNION(1,0,0,0);
		j=D3DXQUATERNION(0,1,0,0);
		k=D3DXQUATERNION(0,0,1,0);
		//D3DXQUATERNION ij=i*j;
		//D3DXQUATERNION jk=j*k;
		//D3DXQUATERNION ki=k*i;	
		cout<<"i*j="<<i*j<<endl;
		cout<<"j*k="<<j*k<<endl;
		cout<<"k*i="<<k*i<<endl;
		D3DVECTOR K=GetEulerAngle(i*j);
		D3DVECTOR I=GetEulerAngle(j*k);		
		D3DVECTOR J=GetEulerAngle(k*i);
		cout<<"K="<<K<<endl;
		cout<<"I="<<I<<endl;
		cout<<"J="<<J<<endl;
	}
	
	return 0;
}