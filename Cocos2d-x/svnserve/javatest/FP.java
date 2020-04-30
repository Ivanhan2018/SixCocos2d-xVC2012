public class FP
{

     public static double Func(double x) 
     {
         double y; 
         y=Math.exp(x*x); 
         return(y); 
     }
 
    /* 
       变步长辛普生法
       a为积分下限;b为积分上限;eps为精度要求
    */
    public static double bcsimp(FP bcsimpf,double a,double b,double eps){
            int n,k; 
            double h,t1,t2,s1,s2,ep,p,x;
            s2=0; 
            n=1;
            h=b-a;
            t1=h*(bcsimpf.Func(a)+bcsimpf.Func(b))/2.0; 
            s1=t1; 
            ep=eps+1.0; 
            while(ep>=eps) 
            { 
               p=0.0; 
               for(k=0;k<=n-1;k++) 
               {
                 x=a+(k+0.5)*h; 
                 p=p+bcsimpf.Func(x); 
               } 
               t2=(t1+h*p)/2.0; 
               s2=(4.0*t2-t1)/3.0; 
               ep=Math.abs(s2-s1); 
               t1=t2;
               s1=s2;
               n=n+n;
               h=h/2.0; 
            } 
            return(s2);
    }

    public static void main(String[] args) {      
             FP bcsimpf = new FP();
             double a,b,eps,t; 
             a=0.0;
             b=1.0;
             eps=0.000001; 
             t=bcsimp(bcsimpf,a,b,eps); 
             System.out.printf("t=%e\n",t);
    }

}