package main
 
import (
    "fmt"
)

func main() {
    var retVec02 []int=FindrootInFp(Polygon2,3,0,2);//1,2，即x^2+2=0在F_3中有两根：x_1=1,x_2=2
	fmt.Println("retVec02=",retVec02)
	var retVec00_01 []int=FindrootInFp(Polygon2,2,0,1);//1，即x^2+1=0在F_2中有一根：x_1=1
	fmt.Println("retVec00_01=",retVec00_01)	
}

func Polygon2(x,a1,a0 int)int{
	return x*x+a1*x+a0
}

func Mod(ret,n int)int {
	if(ret<0){
		var ret1 int=ret+(-ret+1)*n
		return ret1%n
	}
	return ret%n
}

func FindrootInFp(fun func(int,int,int)int,p,a1,a0 int)[]int {
	ret := []int{}
	for i:=0;i<p;i++{
		if(Mod(fun(i,a1,a0),p)==0){
			ret = append(ret,i)
		}
	}
	return ret
}
