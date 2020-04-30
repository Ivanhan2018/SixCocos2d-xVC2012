package main
 
import (
    "fmt"
    "math"	
)

// 计算m*n阶实矩阵的秩
func brank(a *[]float64,m,n int) int{
var i,j,k,nn,is,js,l,ll,u,v int
var q,d float64
nn=m
if(m>=n){nn=n}
k=0

for l=0;l<=nn-1;l++{ 
q=0.0
for i=l;i<=m-1;i++{
for j=l;j<=n-1;j++{
ll=i*n+j
d=math.Abs((*a)[ll])
if(d>q){
q=d
is=i
js=j
}
}//end for j

if (q+1.0==1.0){
return(k)
}
k=k+1

if (is!=l){
for j=l;j<=n-1;j++{
u=l*n+j
v=is*n+j
d=(*a)[u]
(*a)[u]=(*a)[v]
(*a)[v]=d
}
}
if (js!=l){ 
for i=l;i<=m-1;i++{
u=i*n+js
v=i*n+l
d=(*a)[u]
(*a)[u]=(*a)[v]
(*a)[v]=d
}
}
ll=l*n+l
for i=l+1;i<=n-1;i++{
d=(*a)[i*n+l]/(*a)[ll]
for j=l+1;j<=n-1;j++{
u=i*n+j
(*a)[u]=(*a)[u]-d*(*a)[l*n+j]
}
}
}//end for j
}//end for l
return(k)
}

func main() {
var a []float64=[]float64{
1.0,2.0,3.0,4.0,
5.0,6.0,7.0,8.0,
9.0,10.0,11.0,12.0,
13.0,14.0,15.0,16.0,
17.0,18.0,19.0,20.0}
/*
var a2 [][4]float64=[][4]float64{
{1.0,2.0,3.0,4.0},
{5.0,6.0,7.0,8.0},
{9.0,10.0,11.0,12.0},
{13.0,14.0,15.0,16.0},
{17.0,18.0,19.0,20.0}}
*/
rank := brank(&a,5,4)
fmt.Printf("rank(a)=%d\n",rank) 
} 