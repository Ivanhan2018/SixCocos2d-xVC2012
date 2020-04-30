package main
 
import (
    "fmt"
    "time"
)

var g_C4 [][]int=[][]int{
{1,2,3,4},
{2,1,4,3},
{3,4,2,1},
{4,3,1,2}}

var g_S3 [][]int=[][]int{
{1,2,3,4,5,6},
{2,3,1,6,4,5},
{3,1,2,5,6,4},
{4,5,6,1,2,3},
{5,6,4,3,1,2},
{6,4,5,2,3,1}}

var g_P16 [][]int=[][]int{
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
{1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14},
{2,3,1,0,6,7,5,4,10,11,9,8,14,15,13,12},
{3,2,0,1,7,6,4,5,11,10,8,9,15,14,12,13},
{4,5,6,7,0,1,2,3,14,15,13,12,11,10,8,9},
{5,4,7,6,1,0,3,2,15,14,12,13,10,11,9,8},
{6,7,5,4,2,3,1,0,13,12,15,14,8,9,10,11},
{7,6,4,5,3,2,0,1,12,13,14,15,9,8,11,10},
{8,9,10,11,15,14,12,13,0,1,2,3,6,7,5,4},
{9,8,11,10,14,15,13,12,1,0,3,2,7,6,4,5},
{10,11,9,8,12,13,14,15,2,3,1,0,5,4,7,6},
{11,10,8,9,13,12,15,14,3,2,0,1,4,5,6,7},
{12,13,14,15,10,11,9,8,7,6,4,5,0,1,2,3},
{13,12,15,14,11,10,8,9,6,7,5,4,1,0,3,2},
{14,15,13,12,9,8,11,10,4,5,6,7,2,3,1,0},
{15,14,12,13,8,9,10,11,5,4,7,6,3,2,0,1}}

var g_M16 [][]int=[][]int{
{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15},
{1,0,8,9,10,11,7,6,2,3,4,5,15,14,13,12},
{2,8,4,6,5,1,12,15,10,7,11,0,13,9,3,14},
{3,9,7,0,12,14,8,2,6,1,15,13,4,11,5,10},
{4,10,5,12,1,8,13,14,11,15,0,2,9,7,6,3},
{5,11,1,13,8,10,9,3,0,14,2,4,7,15,12,6},
{6,7,15,2,13,3,10,4,12,8,14,9,5,0,1,11},
{7,6,12,8,14,9,4,10,15,2,13,3,11,1,0,5},
{8,2,10,7,11,0,15,12,4,6,5,1,14,3,9,13},
{9,3,6,1,15,13,2,8,7,0,12,14,10,5,11,4},
{10,4,11,15,0,2,14,13,5,12,1,8,3,6,7,9},
{11,5,0,14,2,4,3,9,1,13,8,10,6,12,15,7},
{12,15,14,4,9,6,11,5,13,10,3,7,1,2,8,0},
{13,14,3,5,7,12,0,1,9,11,6,15,8,4,10,2},
{14,13,9,11,6,15,1,0,3,5,7,12,2,10,4,8},
{15,12,13,10,3,7,5,11,14,4,9,6,0,8,2,1},
}

var g_D4 []int=[]int{
1,2,3,4,5,6,7,8,
2,3,4,1,8,5,6,7,
3,4,1,2,7,8,5,6,
4,1,2,3,6,7,8,5,
5,6,7,8,1,2,3,4,
6,7,8,5,4,1,2,3,
7,8,5,6,3,4,1,2,
8,5,6,7,2,3,4,1,
}

func Arr1_2(a *[]int,m,n int)[][]int{
res := [][]int{}
for i:=0;i<m;i++ {
            t := []int{}
            for j:=0;j<n;j++ {
                r := (*a)[i*n+j]
                t = append(t, r)
            }
            res = append(res,t)
        }
return res
}

// n中取m的排列数
func mathPailie(n int, m int) int {
    return jieCheng(n) / jieCheng(n-m)
}
 
// n中取m的组合数
func mathZuhe(n int, m int) int {
    return jieCheng(n) / (jieCheng(n-m) * jieCheng(m))
}
 
// 阶乘
func jieCheng(n int) int {
    result := 1
    for i := 2; i <= n; i++ {
        result *= i
    }
 
    return result
}

// 根据索引号数组得到元素数组
func findNumsByIndexs(nums []int, indexs [][]int) [][]int {
    if len(indexs) == 0 {
        return [][]int{}
    }
 
    result := make([][]int, len(indexs))
 
    for i, v := range indexs {
        line := make([]int, 0)
        for j, v2 := range v {
            if v2 == 1 {
                line = append(line, nums[j])
            }
        }
        result[i] = line
    }
 
    return result
}

func moveOneToLeft(leftNums []int) {
    //计算有几个1
    sum := 0
    for i := 0; i < len(leftNums); i++ {
        if leftNums[i] == 1 {
            sum++
        }
    }
 
    //将前sum个改为1，之后的改为0
    for i := 0; i < len(leftNums); i++ {
        if i < sum {
            leftNums[i] = 1
        } else {
            leftNums[i] = 0
        }
    }
}

// 将ele复制后添加到arr中，返回新的数组
func addTo(arr [][]int, ele []int) [][]int {
    newEle := make([]int, len(ele))
    copy(newEle, ele)
    arr = append(arr, newEle)
 
    return arr
}

// n中取m
func zuheResult(n int, m int) [][]int {
    if m < 1 || m > n {
        fmt.Println("Illegal argument. Param m must between 1 and len(nums).")
        return [][]int{}
    }
 
    //保存最终结果的数组，总数直接通过数学公式计算
    result := make([][]int, 0, mathZuhe(n, m))
    //保存每一个组合的索引的数组，1表示选中，0表示未选中
    indexs := make([]int, n)
    for i := 0; i < n; i++ {
        if i < m {
            indexs[i] = 1
        } else {
            indexs[i] = 0
        }
    }
 
    //第一个结果
    result = addTo(result, indexs)
    for {
        find := false
        //每次循环将第一次出现的 1 0 改为 0 1，同时将左侧的1移动到最左侧
        for i := 0; i < n-1; i++ {
            if indexs[i] == 1 && indexs[i+1] == 0 {
                find = true
 
                indexs[i], indexs[i+1] = 0, 1
                if i > 1 {
                    moveOneToLeft(indexs[:i])
                }
                result = addTo(result, indexs)
 
                break
            }
        }
 
        //本次循环没有找到 1 0 ，说明已经取到了最后一种情况
        if !find {
            break
        }
    }
 
    return result
}

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

func IsInFG(v *[]int,m int)int {
	for i:=0;i<len((*v));i++{
		if((*v)[i]==m){
			return i;
		}
	}
	return -1;
}

func IsEqual(a *[]int,b *[]int)bool {
    n:=len((*a))
	if(len((*b))!=n){
		return false
	}
	for i:=0;i<n;i++{
		if((*a)[i]!=(*b)[i]){
			return false
		}
	}
	return true
}

func IsInS(S *[][]int,v *[]int)int {
    n:=len((*S))
	for i:=0;i<n;i++{
		bRet := IsEqual(&(*S)[i],v)
			if(bRet){
			   return i
			}
	}
	return -1
}

func FG(G *[][]int,v *[]int)[]int {
	//FG := (*v)
	FG := []int{}
	for i:=0;i<len((*v));i++{
		FG=append(FG,(*v)[i])
	}	
	var cnt,cnt1 int
	cnt1=cnt
    for {
	    cnt=len(FG)
		for i:=0;i<cnt;i++{
			for j:=0;j<cnt;j++{
			IJ:=(*G)[FG[i]-1][FG[j]-1];
			bIn := IsInFG(&FG,IJ)
			if(bIn==-1){
			FG=append(FG,IJ)
			}
		}
		}
		cnt1=len(FG)
     if cnt1==cnt {
            break
        }
    }
	BubbleSort(&FG)
    return FG
}

func test1() {
var v1 []int=[]int{2,3}
var v2 []int=[]int{2}
var v3 []int=[]int{3}
var v4 []int=[]int{4}
var v1FG []int=FG(&g_C4,&v1)
var v2FG []int=FG(&g_C4,&v2)
var v3FG []int=FG(&g_C4,&v3)
var v4FG []int=FG(&g_C4,&v4)
fmt.Println("v1=",v1)
fmt.Println("v1FG=",v1FG)
fmt.Println("v2=",v2)
fmt.Println("v2FG=",v2FG)
fmt.Println("v3=",v3)
fmt.Println("v3FG=",v3FG)
fmt.Println("v4=",v4)
fmt.Println("v4FG=",v4FG)
nums := []int{1, 2, 3, 4}
bN:=IsNormalSubgroup(&g_C4,&nums,&v2FG)
if(bN){
fmt.Println(v2,"=>",v2FG,"是正规子群")				
}else{
fmt.Println(v2,"=>",v2FG,"不是正规正群")
}
}

func test2() {
	nums := []int{1, 2, 3, 4}
	n:=4
	timeStart := time.Now()
	for m:=1;m<=n;m++{
		indexs := zuheResult(n, m)
		result := findNumsByIndexs(nums, indexs)
		fmt.Println("count:", len(result))
		fmt.Println("result:", result)

		//结果是否正确
		rightCount := mathZuhe(n, m)
		if rightCount == len(result) {
			fmt.Println("结果正确")
		} else {
			fmt.Println("结果错误，正确结果是：", rightCount)
		}
	}
	timeEnd := time.Now()
    fmt.Println("time consume:", timeEnd.Sub(timeStart))	
}

func test3() {
	nums := []int{1, 2, 3, 4}
	n:=4
	timeStart := time.Now()
	for m:=1;m<=n;m++{
		indexs := zuheResult(n, m)
		result := findNumsByIndexs(nums, indexs)
		for _, v := range result {
			vFG:=FG(&g_C4,&v)
			fmt.Println(v,"=>",vFG)
		}
	}
    timeEnd := time.Now()
    fmt.Println("time consume:", timeEnd.Sub(timeStart))
}

func Order(G *[][]int,m int)[]int {
	ret := []int{}
	var mi int=m
	ret=append(ret,1)
    for {
        if mi==1 {
            break
        }
        ret=append(ret,mi)
        mi=(*G)[mi-1][m-1]
    }
	return ret
}

func Inv(G *[][]int,m int)int {
	v:=Order(G,m)
	var ord int=len(v)
	//fmt.Println("v=",v,"m=",m,",ord=",ord,"=>",v[ord-1])
	return v[ord-1]
}

func IsInCenterOfG(G *[][]int,a int) bool{
	for i:=0;i<len(*G);i++{
        ia:=(*G)[i][a-1]
        ai:=(*G)[a-1][i]
		if(ia!=ai){
			return false
		}
	}
	return true
}

func CenterOfG(G *[][]int)[]int {
	ret := []int{}
	for i:=0;i<len(*G);i++{
		if(IsInCenterOfG(G,i+1)){
			ret=append(ret,i+1)
		}
	}
	return ret
}

func DerivedSubgroup(G *[][]int)[]int {
	ret := []int{}
	ret=append(ret,1)
	N:=len(*G)
	for i:=0;i<N;i++{
		I:=Inv(G,i+1)-1
		for j:=i+1;j<N;j++{
			ij:=(*G)[i][j]-1
			J:=Inv(G,j+1)-1
			IJ:=(*G)[I][J]-1
			ijIJ:=(*G)[ij][IJ]
		    if(IsInFG(&ret,ijIJ)==-1){
		      ret=append(ret,ijIJ)
		    }		
		}
	}
	BubbleSort(&ret)
	return ret
}

func IsNormalSubgroup(G *[][]int,S *[]int,A *[]int) bool{
 //A是S的子集
 for i:=0;i<len(*A);i++{
  if(IsInFG(S,(*A)[i])==-1){
   return false
  }
 }
 //进一步判断是否是正规子群
 for i:=0;i<len(*S);i++{
  for j:=0;j<len(*A);j++{
   gh:=(*G)[(*S)[i]-1][(*A)[j]-1]
   g1:=Inv(G,(*S)[i])
   ghg1:=(*G)[gh-1][g1-1]
   //fmt.Println("G=",(*G),"S,=",S,",A=",A,"i=",i,",j=",j,",g=",(*S)[i],",h=",(*A)[j],",g1=",g1,",gh=",gh,",ghg1=",ghg1)
   if(IsInFG(A,ghg1)==-1){
    return false
   }
  }
 }
 return true
}

func quotientGN(G *[][]int,S *[]int,A *[]int)[][]int {
	ret := [][]int{}
	s:=len(*S)
	n:=len(*A)
    for i:=0;i<s;i++{
		I := []int{}
		for j:=0;j<n;j++{
			ij:=(*G)[(*S)[i]-1][(*A)[j]-1]
			I=append(I,ij)
		}
		BubbleSort(&I)
		if(IsInS(&ret,&I)==-1){
			ret=append(ret,I)
		}
	}
	return ret
}

func IsInS2(S *[][]int,m int)int {
    n:=len((*S))
	for i:=0;i<n;i++{
		bRet := IsInFG(&(*S)[i],m)
			if(bRet>-1){
			   return i
			}
	}
	return -1
}

func quotientTable(G *[][]int,H *[][]int,S *[]int,A *[]int)[][]int {
	ret := [][]int{}
	n:=len(*H)
    for i:=0;i<n;i++{
	    I := []int{}
		for j:=0;j<n;j++{
			ij:=(*G)[(*H)[i][0]-1][(*H)[j][0]-1]
			IJ:=IsInS2(H,ij)
			I=append(I,IJ+1)
		}
		ret=append(ret,I)
	}
	return ret
}

func PrintTable(vv [][]int){
	for _, v := range vv {
			for _, v2 := range v {
				fmt.Printf("%d ",v2)
			}
			fmt.Println()
		}
	return
}

// 群G的所有子群S(G)
func AllSubgroups(G *[][]int) {
	ZG:=CenterOfG(G)
	DG:=DerivedSubgroup(G)
	
	S := [][]int{}
	n:=len(*G)
	//fmt.Println("n:", n)
	//nums := []int{1, 2, 3, 4}
	nums := []int{}
	for i:=1;i<=n;i++{
		nums=append(nums,i)
	}	
	//fmt.Println("nums:", nums)
	timeStart := time.Now()
	for m:=1;m<=n;m++{
		indexs := zuheResult(n, m)
		result := findNumsByIndexs(nums, indexs)
		for _, v := range result {
			vFG:=FG(G,&v)
			if(IsInS(&S,&vFG)==-1){
			    S=append(S,vFG) 
				bZ:=IsEqual(&ZG,&vFG)
				bD:=IsEqual(&DG,&vFG)
                var str string
                if(bZ){
				   str=",是中心"
                }
				if(bD){
				   str+=",是换位子群"
                }
				bN:=IsNormalSubgroup(G,&nums,&vFG)
				if(bN){
				//fmt.Println(v,"=>",vFG,"是正规子群")
                H:=quotientGN(G,&nums,&vFG) 
                vvH:=quotientTable(G,&H,&nums,&vFG)
				fmt.Println(v,"=>",vFG,"是正规子群",str,",商群:",H)
                PrintTable(vvH)			
				}else{
				fmt.Println(v,"=>",vFG,"不是正规子群")
				}
			//}else{
			//   fmt.Println(v,"->",vFG)
			}
		}
	}
    timeEnd := time.Now()
    fmt.Println("time consume:", timeEnd.Sub(timeStart))
}

func main() {
	//|S(C_4)|=3,|S1(C_4)|=3,|N(C_4)|=3
	fmt.Println("S(C_4):")
	AllSubgroups(&g_C4)
	//|S(S_3)|=6,|S1(S_3)|=4,|N(S_3)|=3
	fmt.Println("S(S_3):")	
	AllSubgroups(&g_S3)	
	//|S(GAP4[16,13])|=23,|S1(GAP4[16,13])|=8,|N(GAP4[16,13])|=17
	//|S(GAP4[16,6])|=11,|S1(GAP4[16,6])|=7,|N(GAP4[16,6])|=9	
	for i, v := range g_P16 {
			for j, _ := range v {
				g_P16[i][j]+=1
				g_M16[i][j]+=1
			}
		}
	fmt.Println("S(P_16):")			
	AllSubgroups(&g_P16)
	fmt.Println("S(M_16):")		
	AllSubgroups(&g_M16)
	//|S(D_4)|=10,|S1(D_4)|=5,|N(D_4)|=6
	var D4 [][]int=Arr1_2(&g_D4,8,8)
	fmt.Println("S(D_4):")		
	AllSubgroups(&D4)
}