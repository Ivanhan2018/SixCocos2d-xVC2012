package main
 
import (
    "fmt"
    "math"	
)

// 正弦积分
func lsinn(x float64)float64{
	var m,i,j int
	var s,p,ep,h,aa,bb,w,xx,g float64
	var t [5]float64=[5]float64{-0.9061798459,-0.5384693101,0.0,0.5384693101,0.9061798459}
	var c [5]float64=[5]float64{0.2369268851,0.4786286705,0.5688888889,0.4786286705,0.2369268851}
	m=1
	if (x==0){return(0.0)}
    h=math.Abs(x)
	s=math.Abs(0.0001*h);
    p=1.0e+35
	ep=0.000001
	g=0.0
    for{ 
		if ((ep<0.0000001)||(math.Abs(h)<=s)) { 
			break
        }
        g=0.0
        for i=1;i<=m;i++{ 
		    aa=(float64(i)-1.0)*h
			bb=float64(i)*h//通过 T(v)可以将 v 的值转换为 T 类型
            w=0.0
            for j=0;j<=4;j++{ 
			    xx=((bb-aa)*t[j]+(bb+aa))/2.0
                w=w+math.Sin(xx)/xx*c[j]
              }
            g=g+w
          }
        g=g*h/2.0
        ep=math.Abs(g-p)/(1.0+math.Abs(g))
        p=g
		m=m+1
		h=math.Abs(x)/float64(m)		
    }
    return g
}

func main() {
	var a []float64=[]float64{0.0,1.0,1000.0}
	for i:=0;i<len(a);i++ {
		fmt.Printf("Si(%4.2f)=%12.7f\n",a[i],lsinn(a[i]))
	}
} 