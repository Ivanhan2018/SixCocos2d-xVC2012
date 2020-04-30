package main
 
import (
    "fmt"
)

// 多项式a乘以多项式b得到多项式c，deg(a)=m-1,deg(b)=n-1,deg(c)=m+n-2=k
func polymul(a *[]int,m int,b *[]int,n int,c *[]int,k *int)int {
 var i,j int 
 if(k!=nil){
 *k=m+n-2
 }
 for i=0;i<m+n-2;i++{ 
  (*c)[i]=0
  }
 for i=0;i<m;i++{
  for j=0;j<n;j++{
   (*c)[i+j]=(*a)[i]*(*b)[j]+(*c)[i+j]
   }
   }
 return 0
} 

func pmul(a *[]int,b *[]int)[]int{
 m:=len(*a)
 n:=len(*b)
 k:=0
 c:=make([]int,m+n-1)
 polymul(a,m,b,n,&c,&k)
 return c
}

func main() {
 a:=[]int{0,1,2}//0x^0+1x^1+2x^2
 b:=[]int{3,1}//3x^0+1x^1
 c:=pmul(&a,&b)//0x^0+3x^1+7x^2+2x^3
 fmt.Println("a=",a,"b=",b,"c=a*b=",c) 
}