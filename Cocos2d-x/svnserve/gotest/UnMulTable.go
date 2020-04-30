//go程序输出Abel群U(n)=(Z/nZ)^*的凯莱表
package main
 
import (
    "fmt"
)

func main() {
    var ret int=gcd(12,32)
	fmt.Println(ret)
	var v []int=totient(12)
	fmt.Println(v)
    var U8 [][]int=UnMulTable(8,totient(8))
	fmt.Println(U8)
	PrintUnMulTable(U8);
}

// a helper function not currently being used (although it’s handy,
// for instance, in checking the order of a power of a character).
// harnesses the euclidean algorithm to return the gcd of two numbers.
//利用欧几里得算法计算两个数的最大公约数
func gcd(a,b int)int{
 if(b == 0){return a}
 if(a == 0){return b}
 if(a%b == 0){
 return b
 }else{
 return gcd(b,a%b)
 }
}

func totient(num int)[]int{
 ret := []int{}
 if(num==1){
  ret = append(ret,1)
  return ret
 }
 for i:=1;i<=num-1;i++{
  if(gcd(num,i)==1){
   ret = append(ret,i)
  }
 }
 return ret
}

func UnMulTable(n int,v []int)[][]int{
 ret:=[][]int{}
 m:=len(v)
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   var ij int=(v[i]*v[j])%n
   var index int=-1
   for k:=0;k<m;k++{
    if(v[k]==ij){
     index=k
     break
    }
   }
   I = append(I,index+1)
  }
  ret = append(ret,I)
 }
 return ret
}

func PrintUnMulTable(vv [][]int){
	for _, v := range vv {
			for _, v2 := range v {
				fmt.Printf("%d ",v2)
			}
			fmt.Println()
		}
	return
}

