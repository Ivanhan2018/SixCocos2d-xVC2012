// 根据群的凯莱表分析其结构的小工具calG.exe
package main
 
import (
    "fmt"
    "os"
    "io/ioutil"	
	"strings"
	"strconv"
	"math"	
    "time"	
    "path"		
)

func ReadAll(filePth string) ([]byte, error) {
 f, err := os.Open(filePth)
 if err != nil {
  return nil, err
 }
 return ioutil.ReadAll(f)
}

func CharArrToStr(v* []byte)string {
	return string((*v)[:])
}

func CharArrToNormal(v* []byte)[]byte {
	ret := []byte{}
	n:=len(*v)
	for i:=0;i<n;i++ {	
		if((*v)[i]==32||(*v)[i]==13||(*v)[i]==10){
			if(len(ret)>0 && ret[len(ret)-1]!=','){
				ret=append(ret,',')
			}
		}else{
			ret=append(ret,(*v)[i])
		}
	}		
	return ret
}

func IsLegalMtx(mtx* [][]int)[]int {
	ret := []int{0,0,0}
	illegal:=-1
	ret[1]=len(*mtx)
	if(ret[1]==0){
		ret[0]=illegal//不是合法矩阵
		return ret
	}
	ret[2]=len((*mtx)[0])
	if(ret[2]==0){
		ret[0]=illegal//不是合法矩阵
		return ret
	}
	for i:=1;i<ret[1];i++{
		if(len((*mtx)[i])!=ret[2]){
			ret[0]=illegal//不是合法矩阵
			return ret
		}
	}
	ret[0]=0//是合法矩阵
	return ret
}

func atoTable(strMtx string)[][]int {
    vvMtx:=[][]int{}
	iAll:=[]int{}
	if(strMtx!=""){	
	    if(strMtx[len(strMtx)-1]==','){	
			strMtx=string(strMtx[0:len(strMtx)-1])
		}
		All:=strings.Split(strMtx,",")
		for i:=0;i<len(All);i++ {
			iElem,_:=strconv.Atoi(All[i])
			iAll=append(iAll,iElem)
		}
	}
	n:=len(iAll)
	n1:=int(math.Sqrt(float64(n)))
	if(n1*n1==n){
		for i:=0;i<n1;i++ {
			iRow:=[]int{}
			for j:=0;j<n1;j++ {
				iElem:=iAll[i*n1+j]
				iRow=append(iRow,iElem)
			}
			vvMtx=append(vvMtx,iRow)
		}
	}
	return vvMtx
}

func ABmul(A* [][]int,B* [][]int)[][]int {
	C:=[][]int{}
	AFlag:=IsLegalMtx(A)
	if(AFlag[0]==-1){
		return C
	}
	BFlag:=IsLegalMtx(B)
	if(BFlag[0]==-1){
		return C
	}
	nB:=BFlag[1]
	n:=AFlag[1]*BFlag[1]

	for a:=0;a<n;a++{
		iRow:=[]int{}
		for b:=0;b<n;b++{
			aj:=a%nB
			ai:=a/nB
			bj:=b%nB
			bi:=b/nB
			i:=(*A)[ai][bi]-1
			j:=(*A)[aj][bj]-1
			c:=nB*i+j+1
			iRow=append(iRow,c)
		}
		C=append(C,iRow)
	}
	return C
}

func Factors(n int)[]int {
	ret := []int{}
	if(n<1){
		return ret
	}
	for i:=1;i<=n;i++{
		if(n%i==0){
			ret=append(ret,i)
		}
	}
	return ret
}

// 未知n阶群的群元的阶
func getGnEOrder(A* [][]int,a int)int {
	AFlag:=IsLegalMtx(A)
	if(AFlag[0]==-1){
		return -1
	}
	n:=AFlag[1]
	if(a<0||a>=n){
	    return -1
	}
	t:=0
	for i:=1;i<=n;i++{
		t=(*A)[t][a]-1
		if(t==0){
			return i
		}
	}
	return -1
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
	//fmt.Println("m",m,",n",n)
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

func SubGroupTable(G *[][]int,S *[]int)[][]int{
 ret:=[][]int{}
 m:=len(*S)
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=(*G)[(*S)[i]-1][(*S)[j]-1]
   ij:=IsInFG(S,IJ)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
} 

func main() {
	var filePth string
	if(len(os.Args)<2){
		fmt.Printf("请输入群A凯莱表文件名：")
		fmt.Scanf("%s",&filePth)
	}else{
		filePth=os.Args[1]
	}

    //filePth="M9.txt"
    ret, _ := ioutil.ReadFile(filePth)
	//ret, _ :=ReadAll(filePth)
	A:=CharArrToNormal(&ret)
	strA:=CharArrToStr(&A)	
	vvA:=atoTable(strA)
	AFlag:=IsLegalMtx(&vvA)
	vOrders:=Factors(AFlag[1])
	vCounts:=make([]int,AFlag[1]+1)
	for i:=0;i<AFlag[1];i++ {
		ord:=getGnEOrder(&vvA,i)
		fmt.Printf("G%dElementToOrder(%d)=%d\n",AFlag[1],i,ord);
		vCounts[ord]=vCounts[ord]+1
	}	
	var strF string
	strF = fmt.Sprintf("G%d有",AFlag[1])
	for i:=0;i<len(vOrders);i++{
		strF += fmt.Sprintf("%d个%d阶元，",vCounts[vOrders[i]],vOrders[i])
	}
	if(len(strF)>2){
		strF=string(strF[0:len(strF)-1])
	}
	fmt.Println(strF)
    filenameWithSuffix := path.Base(filePth)
    fileSuffix := path.Ext(filePth)
    filenameOnly := strings.TrimSuffix(filenameWithSuffix, fileSuffix)	
	fmt.Printf("S(%s):\n",filenameOnly)	
	//AllSubgroups(&vvA)
	n:=len(vvA)
	//fmt.Println("n:", n)
	//nums := []int{1, 2, 3, 4}
	nums := []int{}
	for i:=1;i<=n;i++{
		nums=append(nums,i)
	}	
	ZG:=CenterOfG(&vvA)
	DG:=DerivedSubgroup(&vvA)	
    PZG:=quotientGN(&vvA,&nums,&ZG) 
	PDG:=quotientGN(&vvA,&nums,&DG) 
	fmt.Println("中心:",len(ZG),",射影中心:",len(PZG),",换位子群:",len(DG),",射影换位子群:",len(PDG))
	// 打印关心的群
	if(len(ZG)>12 && len(ZG)<n){
	    fmt.Println(len(ZG),"阶中心:",ZG)
	    vvZG:=SubGroupTable(&vvA,&ZG)	
		PrintTable(vvZG)	
	}
	if(len(PZG)>12 && len(PZG)<n){
	    fmt.Println(len(PZG),"阶射影中心:",PZG)
	    vvPZG:=quotientTable(&vvA,&PZG,&nums,&ZG)
		PrintTable(vvPZG)	
	}	
	if(len(DG)>12 && len(DG)<n){
	    fmt.Println(len(DG),"阶换位子群:",DG)
	    vvDG:=SubGroupTable(&vvA,&DG)	
		PrintTable(vvDG)	
	}
	if(len(PDG)>12 && len(PDG)<n){
	    fmt.Println(len(PZG),"阶射影换位子群:",PZG)
	    vvPDG:=quotientTable(&vvA,&PDG,&nums,&DG)	
		PrintTable(vvPDG)	
	}	
    //v:=[]int{2,10,30,50,70}	
	var sz string
	if(len(os.Args)<3){
		fmt.Printf("请输入生成元集（从1到%d,以逗号分隔）：",n)
		fmt.Scanf("%s",&sz)
	}else{
		sz=os.Args[2]
	}	
	v:=[]int{}
	if(sz[len(sz)-1]==','){	
		sz=string(sz[0:len(sz)-1])
	}
	All:=strings.Split(sz,",")
	for i:=0;i<len(All);i++ {
		iElem,_:=strconv.Atoi(All[i])
		v=append(v,iElem)
	}	
	vFG:=FG(&vvA,&v)
	bZ:=IsEqual(&ZG,&vFG)
	bD:=IsEqual(&DG,&vFG)
	var str string
	if(bZ){
	   str=",是中心"
	}
	if(bD){
	   str+=",是换位子群"
	}	
	bN:=IsNormalSubgroup(&vvA,&nums,&vFG)	
	vvFG:=SubGroupTable(&vvA,&vFG)
	if(bN){
	H:=quotientGN(&vvA,&nums,&vFG) 
	vvH:=quotientTable(&vvA,&H,&nums,&vFG)
	fmt.Println(v,"=>",len(vFG),"阶正规子群",str)
	PrintTable(vvFG)	
	fmt.Println(len(H),"阶商群")	
	PrintTable(vvH)	
	}else{
	fmt.Println(v,"=>",len(vFG),"阶非正规子群")
	PrintTable(vvFG)
	}	
}