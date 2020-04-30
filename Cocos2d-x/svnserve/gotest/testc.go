package main
 
/*
#cgo CFLAGS: -I.
#cgo LDFLAGS: -L. -lhi -ldl
#include "hi.h"
*/    
import "C"    // 注意这个地方与上面注释的地方不能有空行，并且不能使用括号如import ("C" "fmt")
import "fmt"

const (
	SORT_BUB    = 1 //冒泡排序
	SORT_QCK    = 2 //快速排序
	SORT_SHL    = 3 //希尔排序
	SORT_HAP    = 4 //堆排序
)

func BubbleSort(arr *[]int){
    //fmt.Println("排序前arr=",(*arr))
    temp := 0
    for i := 0;i < len(*arr) - 1;i++{
        for j := 0 ;j<len(*arr) -1 - i;j++{
            if((*arr)[j] > (*arr)[j+1]){
                temp = (*arr)[j]
                (*arr)[j] = (*arr)[j+1]
                (*arr)[j+1] = temp
            }
        }
    }
    //fmt.Println("排序后arr=",(*arr))
}

// ascending=1表示升序,0表示降序
func pisort(arr *[]int,ascending int,t int){
		var p1 []C.int		
		var n int=len(*arr)
		p1=make([]C.int,n)
		for i:=0;i<n;i++{ 
			p1[i]=C.int((*arr)[i])
		}
		switch t {
			case SORT_BUB://冒泡排序
				C.pibub(&p1[0],C.int(n))
			case SORT_QCK://快速排序
				C.piqck(&p1[0],C.int(n))
			case SORT_SHL://希尔排序
				C.pishl(&p1[0],C.int(n))
			case SORT_HAP://堆排序
				C.pihap(&p1[0],C.int(n))				
			default:
				C.piqck(&p1[0],C.int(n))
		}		
		if(ascending==0){
		   for i,j:=0,n-1;i<j;i,j=i+1,j-1{
			  p1[i],p1[j]=p1[j],p1[i]
		   }
		}
		for i:=0;i<n;i++{ 
			(*arr)[i]=int(p1[i])
		}		
}

// ascending=1表示升序,0表示降序
func prsort(arr *[]float64,ascending int,t int){
		var p1 []C.double		
		var n int=len(*arr)
		p1=make([]C.double,n)
		for i:=0;i<n;i++{ 
			p1[i]=C.double((*arr)[i])
		}
		switch t {
			case SORT_BUB://冒泡排序
				C.prbub(&p1[0],C.int(n))
			case SORT_QCK://快速排序
				C.prqck(&p1[0],C.int(n))
			case SORT_SHL://希尔排序
				C.prshl(&p1[0],C.int(n))
			case SORT_HAP://堆排序
				C.prhap(&p1[0],C.int(n))				
			default:
				C.prqck(&p1[0],C.int(n))
		}		
		if(ascending==0){
		   for i,j:=0,n-1;i<j;i,j=i+1,j-1{
			  p1[i],p1[j]=p1[j],p1[i]
		   }
		}
		for i:=0;i<n;i++{ 
			(*arr)[i]=float64(p1[i])
		}		
}

// ascending=1表示升序,0表示降序
func phsort(arr *[]string,ascending int,t int){
		var p1 []*C.char		
		var n int=len(*arr)
		p1=make([]*C.char,n)
		for i:=0;i<n;i++{ 
			p1[i]=C.CString((*arr)[i])
		}				
		switch t {
			case SORT_BUB://冒泡排序
				C.phbub(&p1[0],C.int(n),0,C.int(n-1))
			case SORT_QCK://快速排序
				C.phqck(&p1[0],C.int(n),0,C.int(n-1))
			case SORT_SHL://希尔排序
				C.phshl(&p1[0],C.int(n),0,C.int(n-1))
			case SORT_HAP://堆排序
				C.phhap(&p1[0],C.int(n),0,C.int(n-1))				
			default:
				C.phqck(&p1[0],C.int(n),0,C.int(n-1))
		}		
		if(ascending==0){
		   for i,j:=0,n-1;i<j;i,j=i+1,j-1{
			  p1[i],p1[j]=p1[j],p1[i]
		   }
		}
		for i:=0;i<n;i++{ 
			(*arr)[i]=C.GoString(p1[i])
		}		
}

// ascending=1表示升序,0表示降序
func pcsort(arr *[]byte,ascending int,t int){
		var p1 []C.char		
		var n int=len(*arr)
		p1=make([]C.char,n)
		for i:=0;i<n;i++{ 
			p1[i]=C.char((*arr)[i])
		}
		switch t {
			case SORT_BUB://冒泡排序
				C.pcbub(&p1[0],C.int(n))
			case SORT_QCK://快速排序
				C.pcqck(&p1[0],C.int(n))
			case SORT_SHL://希尔排序
				C.pcshl(&p1[0],C.int(n))
			case SORT_HAP://堆排序
				C.pchap(&p1[0],C.int(n))				
			default:
				C.pcqck(&p1[0],C.int(n))
		}		
		if(ascending==0){
		   for i,j:=0,n-1;i<j;i,j=i+1,j-1{
			  p1[i],p1[j]=p1[j],p1[i]
		   }
		}
		for i:=0;i<n;i++{ 
			(*arr)[i]=byte(p1[i])
		}		
}

func pcqck(arr *[]byte,ascending int){
	pcsort(arr,ascending,SORT_QCK)
}

func pchap(arr *[]byte,ascending int){
	pcsort(arr,ascending,SORT_HAP)
}

func phshl(arr *[]string,ascending int){
	phsort(arr,ascending,SORT_SHL)
}

func phbub(arr *[]string,ascending int){
	phsort(arr,ascending,SORT_BUB)
}

func pibub(arr *[]int,ascending int){
	pisort(arr,ascending,SORT_BUB)
}

func pihap(arr *[]int,ascending int){
	pisort(arr,ascending,SORT_HAP)
}
 
func main(){
    C.hi()
    fmt.Println("Hello c, welcome to go!")
    fmt.Println("20*30=", C.test_so_func(20, 30))	
    //fmt.Println("20*30=", C.do_test_so_func(20, 30))	
	
	{
		//_lcoss@8计算余弦积分
		var x float64=0.5
		y:=C.lcoss(C.double(x))
		fmt.Printf("Ci(%4.2f)=%12.7f\n", x,float64(y))	
	}
	
	{
		//_lsinn@8计算大写的正弦积分Si(x)=∫[0->x]sint/tdt=si(x)+pi/2,Si(1.00)
		var x float64=1.0
		y:=C.lsinn(C.double(x))
		fmt.Printf("Si(%4.2f)=%12.7f\n", x,float64(y))	
	}	
	
	{
		//_lexpp@8计算指数积分
		var x float64=1.0
		y:=C.lexpp(C.double(x))
		fmt.Printf("Ei(%4.2f)=%12.7f\n", x,float64(y))	
	}	
	
	{
		var a []C.double=[]C.double{
		2,-1,0,
		0,1,1,
		1,0,0}
		var a1 []C.double=[]C.double{
		2,-1,0,
		0,1,1,
		1,0,0}
		var a2 []C.double=[]C.double{
		2,-1,0,
		0,1,1,
		1,0,0}		
		fmt.Println("a=",a) 
		// 求行列式值的全选主元高斯消去法
		det := C.bsdet(&a1[0],3)		
		fmt.Printf("det(a)=%f\n",float64(det)) 
		// 实矩阵求逆的全选主元高斯约当法（Gauss-Jordan）
		i:=C.brinv(&a2[0],3)
		if(i!=0){
		   fmt.Println("a^-1=",a2)  
		}		
		var c []C.double=[]C.double{0,0,0,0,0,0,0,0,0}
		C.brmul(&a[0],&a2[0],3,3,3,&c[0])		
 		fmt.Println("aa^-1=",c) 
		det = C.bsdet(&a2[0],3)
		fmt.Printf("det(a^-1)=%f\n",float64(det)) 
	}
	
	{
		var a []C.double=[]C.double{
		2,3,1,
		4,2,6,
		7,8,9}
		var b []C.double=[]C.double{
		5,3,6,
		7,8,9,
		1,2,4}	
		var c []C.double=[]C.double{0,0,0,0,0,0,0,0,0}
		// 实矩阵相乘
		C.brmul(&a[0],&b[0],3,3,3,&c[0])
		fmt.Println("c=",c) 
		c1:=c[:]
		fmt.Println("c1=",c1) 
	}
	
	{
		var p []string=[]string{"main","gou","zhao","lin","wang","zhang","li","zhen","ma","sub"}
		p1:=p[:]
		fmt.Println("p=",p) 
		phshl(&p,1)//字符串数组按英文字母升序排序
		fmt.Println("p=",p) 
		phbub(&p1,0)//字符串数组按英文字母降序排序
		fmt.Println("p1=",p)			
		/*
		var p1 []*C.char		
		var n int=len(p)
		p1=make([]*C.char,n)
		for i:=0;i<n;i++{ 
			p1[i]=C.CString(p[i])
		}
		var n1 int=len(p1)	
		C.phhap(&p1[0],C.int(n1),0,C.int(n1-1))//n1个字符串排序(按英文字母升序)
		fmt.Println("p=",p) 
		fmt.Println("n=",n) 
		fmt.Println("n1=",n1) 
		fmt.Printf("p1=") 
		for i:=0;i<n1;i++{ 
			fmt.Printf("%s,", C.GoString(p1[i]))
		}
		fmt.Println("") 	
        */		
	}
	
	{
	   var a []int=[]int{8,6,5,4,7,9,2,3,10,1}
	   b:=a[:]
	   fmt.Println("a=",a) 
	   pibub(&a,1)//整数升序排序
	   fmt.Println("a=",a) 
	   pihap(&b,0)//整数降序排序  
	   fmt.Println("b=",b)	   
	}
	
	{
		var a []float64=[]float64{4.5,5.6,7.6,2.34,1,3.4,2.3,2,3};
		b:=a[:]
		fmt.Println("a=",a) 
		prsort(&a,1,SORT_BUB)//双精度浮点数升序排序
		fmt.Println("a=",a) 
		prsort(&b,0,SORT_HAP)//双精度浮点数降序排序  
		fmt.Println("b=",b)
	} 	
	
	{
		var a []byte=[]byte("qwErtyuiopAsdfghjklZxcvbnm");  
		b:=a[:]
		fmt.Println("a=",a) 
		fmt.Println("a=",string(a)) 		
		pcqck(&a,1)//字符串升序排序
		fmt.Println("a=",a) 
		fmt.Println("a=",string(a)) 		
		pchap(&b,0)//字符串降序排序  
		fmt.Println("b=",b)	
		fmt.Println("b=",string(b)) 		
	}
}