package main
 
import (
    "fmt"
    //"time"
    "os"
	"io/ioutil"	
	"strings"
	"strconv"	
	"math"	
    "time"	
)

type ZmodnZObj struct {
   m_k,m_mod int
}

var g_Z4Add [][]int=[][]int{//GAP4中Z/4Z的加法表，0*a a   2*a -a对应0 1 2 3
	{1,2,3,4},
	{2,3,4,1},
	{3,4,1,2},
	{4,1,2,3},
}

var g_Z4Mul [][]int=[][]int{//GAP4中Z/4Z的乘法表，0*a a   2*a -a对应0 1 2 3
	{1,1,1,1},
	{1,2,3,4},
	{1,3,1,3},
	{1,4,3,2},
}
   
func (this *ZmodnZObj) isEqual(a ZmodnZObj) bool {
  return (this.m_k==a.m_k && this.m_mod==a.m_mod)
 }
 
func (this *ZmodnZObj) getName() string {
  return fmt.Sprintf("ZmodnZObj(%d,%d)",this.m_k,this.m_mod)
}
 
func (this *ZmodnZObj) Add(a ZmodnZObj) ZmodnZObj {
	var ret ZmodnZObj
	ret.m_mod=this.m_mod
	ret.m_k=(this.m_k+a.m_k)%this.m_mod
	return ret
 }
 
func (this *ZmodnZObj) InvAdd() ZmodnZObj {
	var ret ZmodnZObj
	ret.m_mod=this.m_mod
	ret.m_k=(this.m_mod*2-this.m_k)%this.m_mod
	return ret
 }
 
func (this *ZmodnZObj) Mul(a ZmodnZObj) ZmodnZObj {
	var ret ZmodnZObj
	ret.m_mod=this.m_mod
	ret.m_k=(this.m_k*a.m_k)%this.m_mod
	return ret
 }

//InverseMutable(a ZmodnZObj) bool {
func (this *ZmodnZObj) InvMul(a ZmodnZObj) ZmodnZObj {
	var ret ZmodnZObj
	for i:=0;i<this.m_mod;i++ {
	    ret=ZmodnZObj{this.m_mod,i}
		if(ret.Mul(a)==ZmodnZObj{this.m_mod,1}){
			return ret
		}
	}	
	return ZmodnZObj{0,0}
 }
 
func (this *ZmodnZObj) Idx(v *[]ZmodnZObj) int {
  for i:=0;i<len(*v);i++ {
   if(this.isEqual((*v)[i])){
    return i
	}
  }
  return -1
 } 
 
func IsInFR(v *[]int,m int)int {
	for i:=0;i<len((*v));i++{
		if((*v)[i]==m){
			return i;
		}
	}
	return -1;
}

func FR(A *[][]int,M *[][]int,v *[]int)[]int {

	FR := []int{}
	for i:=0;i<len((*v));i++{
		FR=append(FR,(*v)[i])
	}	
	var cnt,cnt1 int
	cnt1=cnt	
    for {
	    cnt=len(FR)
		for i:=0;i<cnt;i++{
			for j:=0;j<cnt;j++{
			IJ:=(*A)[FR[i]-1][FR[j]-1];
			bIn := IsInFR(&FR,IJ)
			if(bIn==-1){
			FR=append(FR,IJ)
			}
			IJ1:=(*M)[FR[i]-1][FR[j]-1];			
			bIn1 := IsInFR(&FR,IJ1)
			if(bIn1==-1){
			FR=append(FR,IJ1)
			}			
		}
		}
		cnt1=len(FR)
     if cnt1==cnt {
            break
        }
    }
	BubbleSort(&FR)
    return FR
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

func Order(n,m int)[]int {
	ret := []int{}
	var mi int=m
    for {
        if mi==0 {
            break
        }
        ret=append(ret,mi)
        mi=(mi+m)%n
    }	
	ret=append(ret,mi)
	BubbleSort(&ret)
	return ret
}

func ToNormal(v *[]int,a int)int {
	for i:=0;i<len(*v);i++ {
		if((*v)[i]==a){
			return i
		}
	}
	return -1
}

//Zn=Z/nZ=1Z/nZ=ZnmTable(n,1)
func ZnTable(n int)([][]int,[][]int){
	vZn := []ZmodnZObj{}
	for i:=0;i<n;i++{
		vZn=append(vZn,ZmodnZObj{i,n})
	}
    vvAdd:=[][]int{}
    vvMul:=[][]int{}
	 for i:=0;i<n;i++{
	  I:=[]int{}
	  I1:=[]int{}
	  for j:=0;j<n;j++{
	   IJ:=vZn[i].Add(vZn[j])
	   ij:=IJ.Idx(&vZn)
	   I = append(I,ij+1)
	   IJ1:=vZn[i].Mul(vZn[j])
	   ij1:=IJ1.Idx(&vZn)
	   I1 = append(I1,ij1+1)	   
	  }
	  vvAdd = append(vvAdd,I)
	  vvMul = append(vvMul,I1)	  
	 }
	 return vvAdd,vvMul
}

//循环环mZ/nZ=RingByGenerators([ZmodnZObj(m,n)])
func ZnmTable(n,m int)([][]int,[][]int){
	vZnm := Order(n,m)
	s:=len(vZnm)
	vZn := []ZmodnZObj{}
	for i:=0;i<s;i++{
		vZn=append(vZn,ZmodnZObj{vZnm[i],n})
	}
    vvAdd:=[][]int{}
    vvMul:=[][]int{}
	 for i:=0;i<s;i++{
	  I:=[]int{}
	  I1:=[]int{}
	  for j:=0;j<s;j++{
	   IJ:=vZn[i].Add(vZn[j])
	   ij:=IJ.Idx(&vZn)
	   I = append(I,ij+1)
	   IJ1:=vZn[i].Mul(vZn[j])
	   ij1:=IJ1.Idx(&vZn)
	   I1 = append(I1,ij1+1)	   
	  }
	  vvAdd = append(vvAdd,I)
	  vvMul = append(vvMul,I1)	  
	 }
	 return vvAdd,vvMul
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

func WriteTable(vv,vv1 [][]int,fn string) {
	f, err := os.OpenFile(fmt.Sprintf("%s.txt",fn), os.O_RDWR|os.O_CREATE, os.ModePerm)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	
	n:=len(vv)
	var buf string
	buf = fmt.Sprintf("[R%dAdd]\n",n)
	f.WriteString(buf)	
	for i:=0;i<n;i++{
		for j:=0;j<n;j++{
			buf = fmt.Sprintf("%d ",vv[i][j])
			f.WriteString(buf)
		}
		f.WriteString("\n");
	}
	buf = fmt.Sprintf("[R%dMul]\n",n)
	f.WriteString(buf)	
	for i:=0;i<n;i++{
		for j:=0;j<n;j++{
			buf = fmt.Sprintf("%d ",vv1[i][j])
			f.WriteString(buf)
		}
		f.WriteString("\n");
	}	
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

func VOrder(G *[][]int,m int)[]int {
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
	v:=VOrder(G,m)
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

func IsNormalSubgroup(G *[][]int,S *[]int,A *[]int) bool{
 //A是S的子集
 for i:=0;i<len(*A);i++{
  if(IsInFR(S,(*A)[i])==-1){
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
   if(IsInFR(A,ghg1)==-1){
    return false
   }
  }
 }
 return true
}

// 判断子环A是否是环S的理想
func IsIdeal(G *[][]int,M *[][]int,S *[]int,A *[]int) bool{
 //A是S的子集
 for i:=0;i<len(*A);i++{
  if(IsInFR(S,(*A)[i])==-1){
   return false
  }
 }
 //进一步判断是否是理想
 for i:=0;i<len(*S);i++{//任意纯量环元素c
  for j:=0;j<len(*A);j++{//任意向量模元素a
   ca:=(*M)[(*S)[i]-1][(*A)[j]-1]
   ac:=(*M)[(*A)[j]-1][(*S)[i]-1]
   if(IsInFR(A,ca)==-1||IsInFR(A,ac)==-1){
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
		bRet := IsInFR(&(*S)[i],m)
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

// 环R(A,M)的所有子环S(R)
func AllSubrings(A *[][]int,M *[][]int) {
	ZM:=CenterOfG(M)	
	S := [][]int{}
	n:=len(*A)
	nums := []int{}
	for i:=1;i<=n;i++{
		nums=append(nums,i)
	}	
	timeStart := time.Now()
	for m:=1;m<=n;m++{
		indexs := zuheResult(n, m)
		result := findNumsByIndexs(nums, indexs)
		for _, v := range result {
			vFR:=FR(A,M,&v)
			if(IsInS(&S,&vFR)==-1){
			    S=append(S,vFR) 
				bZ:=IsEqual(&ZM,&vFR)
                var str string
                if(bZ){
				   str=",是中心"
                }				
				bN:=IsNormalSubgroup(A,&nums,&vFR)
				bI:=IsIdeal(A,M,&nums,&vFR)	
                if(!bN){
				   fmt.Println("出错了，加法群的子群一定是正规子群")
				}				
				if(bI){
				//fmt.Println(v,"=>",vFR,"是理想")
                H:=quotientGN(A,&nums,&vFR) 
                vvHA:=quotientTable(A,&H,&nums,&vFR)
                vvHM:=quotientTable(M,&H,&nums,&vFR)				
				fmt.Println(v,"=>",vFR,"是理想",str,",商环:",H)
	            fmt.Println(fmt.Sprintf("[R%dAdd]",len(H)))				
                PrintTable(vvHA)
			    fmt.Println(fmt.Sprintf("[R%dMul]",len(H)))				
                PrintTable(vvHM)		
				}else{
				fmt.Println(v,"=>",vFR,"不是理想",str)
				}				
				//fmt.Println(v,"=>",vFR)
			//}else{
			//   fmt.Println(v,"->",vFR)
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
   ij:=IsInFR(S,IJ)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
} 

func AllSubrings1(A *[][]int,M *[][]int,N int) {
	ZM:=CenterOfG(M)	
	S := [][]int{}
	n:=len(*A)
	nums := []int{}
	for i:=1;i<=n;i++{
		nums=append(nums,i)
	}	
	timeStart := time.Now()
	for m:=1;m<=n;m++{
		indexs := zuheResult(n, m)
		result := findNumsByIndexs(nums, indexs)
		for _, v := range result {
			vFR:=FR(A,M,&v)
			if(IsInS(&S,&vFR)==-1){
			    S=append(S,vFR) 
				bZ:=IsEqual(&ZM,&vFR)
                var str string
                if(bZ){
				   str=",是中心"
                }				
				bN:=IsNormalSubgroup(A,&nums,&vFR)
				bI:=IsIdeal(A,M,&nums,&vFR)	
                if(!bN){
				   fmt.Println("出错了，加法群的子群一定是正规子群")
				}				
				if(bI){
				//fmt.Println(v,"=>",vFR,"是理想")
                H:=quotientGN(A,&nums,&vFR) 	
                vvHA:=quotientTable(A,&H,&nums,&vFR)
                vvHM:=quotientTable(M,&H,&nums,&vFR)				
				fmt.Println(v,"=>",vFR,"是理想",str,",商环:",H)
	            fmt.Println(fmt.Sprintf("[R%dAdd]",len(H)))				
                PrintTable(vvHA)
			    fmt.Println(fmt.Sprintf("[R%dMul]",len(H)))				
                PrintTable(vvHM)		
				}else{
				fmt.Println(v,"=>",vFR,"不是理想",str)
				}				
				//fmt.Println(v,"=>",vFR)
			//}else{
			//   fmt.Println(v,"->",vFR)
				if(len(vFR)==N){
					fmt.Println(len(vFR),"阶子环:")
					vvFRA:=SubGroupTable(A,&vFR)	
					fmt.Println(fmt.Sprintf("[R%dAdd]",len(vFR)))				
					PrintTable(vvFRA)
					vvFRM:=SubGroupTable(M,&vFR)	
					fmt.Println(fmt.Sprintf("[R%dMul]",len(vFR)))				
					PrintTable(vvFRM)	
				}			
			}
		}
	}
    timeEnd := time.Now()
    fmt.Println("time consume:", timeEnd.Sub(timeStart))
}

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

func CharArrToNormal2(v* []byte)[]byte {
	ret := []byte{}
	n:=len(*v)
	var ch byte=0
	flag:=0//0:有效数据,1:注释开始,2:注释结束
	for i:=0;i<n;i++ {	
	       ch = (*v)[i]
		   if (ch!='[' && ch!=']' && (flag==0||flag==2)){
				if(ch==32||ch==13||ch==10){
					if(len(ret)>0 && ret[len(ret)-1]!=','){
						ret=append(ret,',')
					}
				}else{
					ret=append(ret,ch)
				}
				flag=0
		   }else{
            if(ch=='['){
             flag=1
           }else if(ch==']'){
             flag=2
           }  
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

func atoTable2(strMtx string)([][]int,[][]int) {
    vvMtx:=[][]int{}
    vvMtx1:=[][]int{}	
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
	n1:=int(math.Sqrt(float64(n/2)))
	if(n1*n1==n/2){
		for i:=0;i<n1;i++ {
			iRow:=[]int{}
			for j:=0;j<n1;j++ {
				iElem:=iAll[i*n1+j]
				iRow=append(iRow,iElem)
			}
			vvMtx=append(vvMtx,iRow)
		}
		for i:=0;i<n1;i++ {
			iRow:=[]int{}
			for j:=0;j<n1;j++ {
				iElem:=iAll[n/2+i*n1+j]
				iRow=append(iRow,iElem)
			}
			vvMtx1=append(vvMtx1,iRow)
		}		
	}
	return vvMtx,vvMtx1
}



func main() {
	var filePth string
	if(len(os.Args)<2){
		fmt.Printf("请输入环R凯莱表文件名：")
		fmt.Scanf("%s",&filePth)
	}else{
		filePth=os.Args[1]
	}
	var N int=8
	if(len(os.Args)>2){
		n,err := strconv.Atoi(os.Args[2])
		if err == nil {
			N=n
		}
	}
	
    ret, _ := ioutil.ReadFile(filePth)
	//ret, _ :=ReadAll(filePth)
	A:=CharArrToNormal2(&ret)
	strA:=CharArrToStr(&A)	
	vvA,vvM:=atoTable2(strA)
	//AFlagA:=IsLegalMtx(&vvA)	
	//AFlagM:=IsLegalMtx(&vvM)		
	//fmt.Println("vvA=",vvA)
	//fmt.Println("vvM=",vvM)	
	//fmt.Println("AFlagA=",AFlagA)	
	//fmt.Println("AFlagM=",AFlagM)	
    AllSubrings1(&vvA,&vvM,N)
}