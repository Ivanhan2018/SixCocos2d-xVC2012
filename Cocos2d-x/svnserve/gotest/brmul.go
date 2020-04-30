package main
 
import (
    "fmt"	
)

// 实矩阵相乘
func brmul(a,b,c *[]float64,m,n,k int){
var i,j,l,u int
for i=0; i<=m-1; i++{
for j=0; j<=k-1; j++{
u=i*k+j
(*c)[u]=0.0
for l=0; l<=n-1; l++{
  (*c)[u]=(*c)[u]+(*a)[i*n+l]*(*b)[l*k+j]
}
}
}
return
}

func Arr1_2(a *[]float64,m,n int)[][]float64{
res := [][]float64{}
for i:=0;i<m;i++ {
            t := []float64{}
            for j:=0;j<n;j++ {
                r := (*a)[i*n+j]
                t = append(t, r)
            }
            res = append(res,t)
        }
return res
}

func Arr2_1(a [][]float64)[]float64{
	res := []float64{}
	var m,n int
	m=len(a)
	n=len(a[0])
	for i:=0;i<m*n;i++ {
		t := a[i/n][i%n]
		res = append(res,t)
	}
	return res
}

func main() {
var a []float64=[]float64{
1.0,3.0,-2.0,0.0,4.0,
-2.0,-1.0,5.0,-7.0,2.0,
0.0,8.0,4.0,1.0,-5.0,
3.0,-3.0,2.0,-4.0,1.0}
var b []float64=[]float64{
4.0,5.0,-1.0,
2.0,-2.0,6.0,
7.0,8.0,1.0,
0.0,3.0,-5.0,
9.0,8.0,-6.0}
var b2 [][]float64=[][]float64{
{4.0,5.0,-1.0},
{2.0,-2.0,6.0},
{7.0,8.0,1.0},
{0.0,3.0,-5.0},
{9.0,8.0,-6.0}}
fmt.Println("b2=",b2)
var b21 []float64=Arr2_1(b2)
fmt.Println("b21=",b21)
var c []float64=[]float64{0,0,0,0,0,0,0,0,0,0,0,0}
brmul(&a,&b,&c,4,5,3)
fmt.Println("c=",c)
var c2 [][]float64=Arr1_2(&c,4,3)
fmt.Println("len(c2)=",len(c2))
fmt.Println("len(c2[0])=",len(c2[0]))
fmt.Println("c2=",c2)
var a2 [][]float64=Arr1_2(&a,4,5)
fmt.Println("a2=",a2)	
} 