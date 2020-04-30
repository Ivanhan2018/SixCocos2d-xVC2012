package main
 
import (
    "fmt"
    "os"	
)

type S9 struct {
   m_a1,m_a2,m_a3,m_a4,m_a5,m_a6,m_a7,m_a8,m_a9 int
}

//双行置换表达式
var g_M9 []S9=[]S9{
S9{1,2,3,4,5,6,7,8,9},
S9{4,5,6,9,3,2,7,1,8},//4阶元a
S9{6,1,7,4,2,5,9,3,8},//4阶元b
S9{9,3,2,8,6,5,7,4,1},//2阶元a^2
S9{8,6,5,1,2,3,7,9,4},//4阶元a^3
S9{5,6,9,4,1,2,8,7,3},//2阶元b^2
S9{2,5,8,4,6,1,3,9,7},//4阶元b^3
S9{4,2,5,8,7,1,9,6,3},//4阶元ab
S9{4,1,2,3,9,6,8,5,7},//4阶元abb
S9{4,6,1,7,8,5,3,2,9},//4阶元abbb
S9{8,7,1,3,5,2,9,4,6},//4阶元aab
S9{3,9,6,7,2,1,8,4,5},//3阶元aabb
S9{7,8,5,9,1,6,3,4,2},//4阶元aabbb
S9{3,5,2,6,1,7,9,8,4},//4阶元aaab
S9{7,2,1,5,6,9,8,3,4},//4阶元aaabb
S9{9,1,6,2,5,8,3,7,4},//4阶元aaabbb
S9{2,4,7,9,5,3,8,6,1},//4阶元ba=aaabbbaaabbbaaabbb
S9{5,9,7,8,3,6,1,2,4},//4阶元baa=aabbbaabbbaabbb
S9{3,8,7,1,6,2,4,5,9},//4阶元baaa=abbbabbbabbb
S9{3,2,8,9,4,5,1,7,6},//4阶元bba=aaabbaaabbaaabb
S9{6,5,1,8,9,3,4,7,2},//3阶元bbaa=aabbaabb
S9{2,3,4,1,8,6,9,7,5},//4阶元bbaaa=abbabbabb
S9{5,3,1,9,2,4,6,8,7},//4阶元bbba=aaabaaabaaab
S9{3,6,4,8,5,9,2,1,7},//4阶元bbbaa=aabaabaab
S9{6,2,9,1,3,8,5,4,7},//4阶元bbbaaa=ababab
S9{8,2,7,6,9,4,3,1,5},//2阶元abab=aaabbaaabb
S9{3,4,1,2,7,6,5,9,8},//2阶元abbabb=aabbbaabbb
S9{7,5,4,3,2,8,1,6,9},//2阶元abbbabbb
S9{4,9,8,1,5,7,6,3,2},//2阶元aabaab=aaabbbaaabbb
S9{2,1,5,7,3,9,4,8,6},//2阶元aaabaaab
S9{9,5,3,1,7,4,8,2,6},//30=1*16
S9{8,3,6,4,7,9,1,5,2},//31=1*17
S9{1,6,2,9,7,8,4,3,5},//32=1*18
S9{9,4,5,6,8,2,1,3,7},//33=1*19
S9{8,9,3,2,1,5,4,6,7},//34=1*20
S9{1,8,6,5,4,3,9,2,7},//35=1*21
S9{9,2,4,7,1,3,6,5,8},//36=1*22
S9{8,5,9,7,4,6,2,3,1},//37=1*23
S9{1,3,8,7,9,2,5,6,4},//38=1*24
S9{6,9,4,5,7,2,3,8,1},//39=1*25
S9{2,7,6,8,1,4,5,3,9},//40=1*26
S9{1,5,7,2,8,9,6,4,3},//41=1*28
S9{7,3,9,6,5,1,4,2,8},//42=1*29
S9{1,4,9,8,2,7,3,5,6},//43=2*7
S9{6,4,8,3,1,9,7,2,5},//44=2*8
S9{5,4,3,7,6,8,9,1,2},//45=2*9
S9{2,8,9,3,7,5,6,1,4},//46=2*10
S9{6,7,3,9,8,1,2,5,4},//47=2*12
S9{9,7,8,5,2,6,4,1,3},//48=2*14
S9{4,8,3,6,2,9,5,7,1},//49=2*25
S9{6,3,5,2,4,7,8,1,9},//50=2*26
S9{7,4,6,1,9,5,2,8,3},//51=2*28
S9{1,7,4,6,3,5,8,9,2},//52=3*16
S9{4,7,9,2,6,3,1,8,5},//53=3*17
S9{6,8,2,7,5,4,1,9,3},//54=3*19
S9{7,1,3,8,4,2,6,9,5},//55=3*22
S9{7,9,2,4,8,3,5,1,6},//56=3*24
S9{5,7,2,1,4,9,3,6,8},//57=3*25
S9{8,1,4,9,6,7,5,2,3},//58=3*26
S9{2,6,3,5,9,7,1,4,8},//59=4*17
S9{5,2,6,3,8,7,4,9,1},//60=4*18
S9{7,6,8,2,3,4,9,5,1},//61=4*21
S9{8,4,2,5,3,1,6,7,9},//62=4*22
S9{1,9,5,3,6,4,2,7,8},//63=4*23
S9{9,6,7,3,4,1,5,8,2},//64=4*26
S9{3,7,5,4,9,8,6,2,1},//65=4*28
S9{5,8,4,2,9,1,7,3,6},//66=5*15
S9{5,1,8,6,7,3,2,4,9},//67=6*13
S9{2,9,1,6,4,8,7,5,3},//68=6*25
S9{3,1,9,5,8,4,7,6,2},//69=7*8
S9{9,8,1,4,3,7,2,6,5},//70=7*12
S9{4,3,7,5,1,8,2,9,6},//71=10*12
}
 
func (this *S9) isEqual(a S9) bool {
  return (this.m_a1==a.m_a1 && this.m_a2==a.m_a2 && this.m_a3==a.m_a3 && this.m_a4==a.m_a4 && this.m_a5==a.m_a5 && this.m_a6==a.m_a6 && this.m_a7==a.m_a7 && this.m_a8==a.m_a8 && this.m_a9==a.m_a9)
 }
   
func (this *S9) getName() string {
  for i:=0;i<72;i++ {
   if(this.isEqual(g_M9[i])){
    return fmt.Sprintf("%d",i+1);
	}
  }
  return "Error";
}

func (this *S9) Mul(a S9) S9 {
  var aArr[9]int=[9]int{a.m_a1,a.m_a2,a.m_a3,a.m_a4,a.m_a5,a.m_a6,a.m_a7,a.m_a8,a.m_a9}
  var ret S9
  ret.m_a1=aArr[this.m_a1-1]
  ret.m_a2=aArr[this.m_a2-1]
  ret.m_a3=aArr[this.m_a3-1]
  ret.m_a4=aArr[this.m_a4-1]
  ret.m_a5=aArr[this.m_a5-1]
  ret.m_a6=aArr[this.m_a6-1]
  ret.m_a7=aArr[this.m_a7-1]
  ret.m_a8=aArr[this.m_a8-1]
  ret.m_a9=aArr[this.m_a9-1] 
  return ret
 }
 
func (this *S9) InvMul() S9 {
  for i:=0;i<72;i++ {
   var t S9=this.Mul(g_M9[i])
   if(t.isEqual(g_M9[0])){
    return g_M9[i]
	}
  }
  return S9{0,0,0,0,0,0,0,0,0}
 }
 
 //群元的逆序数
func (this *S9) Tau() int {
  var aArr[9]int=[9]int{this.m_a1,this.m_a2,this.m_a3,this.m_a4,this.m_a5,this.m_a6,this.m_a7,this.m_a8,this.m_a9}
  var ret int=0
  for i:=0;i<9;i++ {
	  for j:=i+1;j<9;j++ {
	   if(aArr[i]>aArr[j]){
		ret++
		}
	  }
  }
  return ret
 }
 
//群元索引
func (this *S9) Idx(v *[]S9) int {
  for i:=0;i<72;i++ {
   if(this.isEqual((*v)[i])){
    return i
	}
  }
  return -1
 } 
 
//群元的阶
func getOrder(idx,m S9) int {
 var t S9=idx
  for i:=1;i<=72;i++ {
  t=t.Mul(m)
  if(t.isEqual(idx)){
   return i
   }
 }
 return -1
}

func createS9(idx int) S9 {
   if(idx>=0 && idx<72){
    return g_M9[idx]
	}
  return S9{0,0,0,0,0,0,0,0,0}
 }
 
func M9MulTable()[][]int{
 ret:=[][]int{}
 m:=72
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=g_M9[i].Mul(g_M9[j])
   ij:=IJ.Idx(&g_M9)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
}

// 置换群G的极大偶置换子群（A9和G的交集）
func EvenPermutationSet(G *[]S9)[]S9{
 ret:=[]S9{}
 for _, v := range (*G) {
	if(v.Tau()%2==0){
	  ret = append(ret,v)
	}
 }
 return ret
}

func EvenPermutationMulTable(G *[]S9)[][]int{
 ret:=[][]int{}
 vAG:=EvenPermutationSet(G)
 m:=len(vAG)
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=vAG[i].Mul(vAG[j])
   ij:=IJ.Idx(&vAG)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
}

func PrintMulTable(vv [][]int){
	for _, v := range vv {
			for _, v2 := range v {
				fmt.Printf("%d ",v2)
			}
			fmt.Println()
		}
	return
}

func WriteMulTable(vv [][]int,fn string) {
	f, err := os.OpenFile(fmt.Sprintf("%s.txt",fn), os.O_RDWR|os.O_CREATE, os.ModePerm)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	
	n:=len(vv)
	var buf string
	for i:=0;i<n;i++{
		for j:=0;j<n;j++{
			buf = fmt.Sprintf("%d ",vv[i][j])
			f.WriteString(buf)
		}
		f.WriteString("\n");
	}
}

func main() {

 vvM9:=M9MulTable()
 PrintMulTable(vvM9)
 WriteMulTable(vvM9,"M9")
 fmt.Println("M9逆序数:") 
 for _, v := range g_M9 {
	fmt.Printf("%d ",v.Tau())
 }
 fmt.Println()  
 vAM9:=EvenPermutationSet(&g_M9)
 nvAM9:=len(vAM9)
 fmt.Println("置换群M9的极大偶置换子群DM9的阶数|AM9|=",nvAM9)  
}