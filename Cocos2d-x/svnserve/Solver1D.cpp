#include <math.h>
#include <stdio.h>

/*
   A 1st order 1D DE solver.
   Assumes the function is not time dependent.
   Parameters
      h      - step size
      y0     - last value
      method - algorithm to use [0,5]
#define EULER    0
#define MIDPOINT 3
      fcn    - evaluate the derivative of the field
*/
double Solver1D(double h,double y0,int method,double (*fcn)(double))
{
   double ynew;
   double k1,k2,k3,k4,k5,k6;

   switch (method) {
   case 0:                          /* Euler method */
      k1 = h * (*fcn)(y0);
      ynew = y0 + k1;
      break;
   case 1:                          /* Modified Euler */
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1);
      ynew = y0 + (k1 + k2) / 2;
      break;
   case 2:                          /* Heuns method */
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + 2 * k1 / 3);
      ynew = y0 + k1 / 4 + 3 * k2 / 4;
      break;
   case 3:                          /* Midpoint */
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1 / 2);
      ynew = y0 + k2;
      break;
   case 4:                          /* 4'th order Runge-kutta */
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1/2);
      k3 = h * (*fcn)(y0 + k2/2);
      k4 = h * (*fcn)(y0 + k3);
      ynew = y0 + k1 / 6 + k2 / 3 + k3 / 3 + k4 / 6;
      break;
   case 5:                          /* England 4'th order, six stage */
      k1 = h * (*fcn)(y0);
      k2 = h * (*fcn)(y0 + k1 / 2);
      k3 = h * (*fcn)(y0 + (k1 + k2) / 4);
      k4 = h * (*fcn)(y0 - k2 + 2 * k3);
      k5 = h * (*fcn)(y0 + (7 * k1 + 10 * k2 + k4) / 27);
      k6 = h * (*fcn)(y0 + (28*k1 - 125*k2 + 546*k3 + 54*k4 - 378*k5) / 625);
      ynew = y0 + k1 / 6 + 4 * k3 / 6 + k4 / 6;
      break;
   }

   return(ynew);
}


int main(int argc, char* argv[])
{
	typedef double(*pR)(double,double,int,double(*)(double));
	pR R=Solver1D;
	double t;
	double dt=0.1;    /* Step size            */
	double T=100;     /* Simulation duration  */
	double y = 1;     /* Initial value        */
	typedef double(*pF)(double);	
	pF func[]={[](double y)->double{return -0.05;},[](double y)->double{return -0.05 * y;}};
	pF func1[]={[](double x)->double{return -0.05*x+1;},[](double x)->double{return exp(-0.05*x);}};	
	const char *szName[]={"y'=-0.05","y'=-0.05y"};
	for(int i=0;i<2;i++)
	{
		y=1;
		printf("输出一阶常微分方程%s的特解y(x)的采样值:\n",szName[i]);
		for (t=0;t<5;t+=dt)
		{
			printf("x=%g,y=%g,y的理论值=%g\n",t,y,func1[i](t));
			y=R(dt,y,3,func[i]);
		}
	}
	return 0;
}

