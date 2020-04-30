package main
 
import (
    "fmt"
)

func conv(x,h *[]float32)[]float32{
    ret := []float32{}
	var sum float32
	lx:=len(*x)
	lh:=len(*h)
	for i := 0; i < lx + lh - 1; i++{
		sum = 0.0
		if( i < lh - 1 ){
			for j := 0; j < i+1; j++{
				sum += (*x)[j] * (*h)[i-j]
			}
		}else if(i > lx - 1){
			for j := lh -1; j > i - lx; j--{
				sum += (*x)[i-j] * (*h)[j]
			}
		}else{
			for j := 0; j < lh; j++{
				sum += (*x)[i-j] * (*h)[j]
			}
		}
		ret = append(ret,sum)
	} 
	return ret
} 

func main() {
{
var a []float32=[]float32{2,2,2}
var b []float32=[]float32{1,4,9}
c:=conv(&a,&b)
fmt.Println("a=",a,"b=",b,"a和b的线性卷积=",c)
}
{
var a []float32=[]float32{0,1,2}
var b []float32=[]float32{3,1}
c:=conv(&a,&b)
fmt.Println("a=",a,"b=",b,"a和b的线性卷积=",c)
}
{
var a []float32=[]float32{2,1,0}
var b []float32=[]float32{1,3}
c:=conv(&a,&b)
fmt.Println("a=",a,"b=",b,"a和b的线性卷积=",c)
}
}