package main
 
import (
    "fmt"
    "os"	
)

type S4 struct {
   m_a1,m_a2,m_a3,m_a4 int
}

//能反映元素阶的置换表达式("描述折线过程")，区别于双行置换表达式("描述折线结果")
var g_S4Name []string=[]string{
"(1)",
"(12)",
"(34)",
"(13)",
"(24)",
"(14)",
"(23)",
"(12)(34)",
"(13)(24)",
"(14)(23)",
"(123)",
"(132)",
"(134)",
"(143)",
"(124)",
"(142)",
"(234)",
"(243)",
"(1234)",
"(1243)",
"(1324)",
"(1342)",
"(1423)",
"(1432)"};

//双行置换表达式
var g_S4 []S4=[]S4{
   S4{1,2,3,4},
   S4{2,1,3,4},
   S4{1,2,4,3},
   S4{3,2,1,4},
   S4{1,4,3,2},
   S4{4,2,3,1},
   S4{1,3,2,4},
   S4{2,1,4,3},
   S4{3,4,1,2},
   S4{4,3,2,1},
   S4{2,3,1,4},
   S4{3,1,2,4},
   S4{3,2,4,1},
   S4{4,2,1,3},
   S4{2,4,3,1},
   S4{4,1,3,2},
   S4{1,3,4,2},
   S4{1,4,2,3},
   S4{2,3,4,1},
   S4{2,4,1,3},
   S4{3,4,2,1},
   S4{3,1,4,2},
   S4{4,3,1,2},
   S4{4,1,2,3}}
 
func (this *S4) isEqual(a S4) bool {
  return (this.m_a1==a.m_a1 && this.m_a2==a.m_a2 && this.m_a3==a.m_a3 && this.m_a4==a.m_a4)
 }
   
func (this *S4) getName() string {
  for i:=0;i<24;i++ {
   if(this.isEqual(g_S4[i])){
    return g_S4Name[i];
	}
  }
  return "Error";
}

func (this *S4) Mul(a S4) S4 {
  var aArr[4]int=[4]int{a.m_a1,a.m_a2,a.m_a3,a.m_a4}
  var ret S4
  ret.m_a1=aArr[this.m_a1-1]
  ret.m_a2=aArr[this.m_a2-1]
  ret.m_a3=aArr[this.m_a3-1]
  ret.m_a4=aArr[this.m_a4-1]
  return ret
 }
 
func (this *S4) InvMul() S4 {
  for i:=0;i<24;i++ {
   var t S4=this.Mul(g_S4[i])
   if(t.isEqual(g_S4[0])){
    return g_S4[i]
	}
  }
  return S4{0,0,0,0}
 }
 
 //群元的逆序数
func (this *S4) Tau() int {
  var aArr[4]int=[4]int{this.m_a1,this.m_a2,this.m_a3,this.m_a4}
  var ret int=0
  for i:=0;i<4;i++ {
	  for j:=i+1;j<4;j++ {
	   if(aArr[i]>aArr[j]){
		ret++
		}
	  }
  }
  return ret
 }
 
//群元索引
func (this *S4) Idx(v *[]S4) int {
  for i:=0;i<24;i++ {
   if(this.isEqual((*v)[i])){
    return i
	}
  }
  return -1
 } 
 
//群元的阶
func getOrder(idx,m S4) int {
 var t S4=idx
  for i:=1;i<=24;i++ {
  t=t.Mul(m)
  if(t.isEqual(idx)){
   return i
   }
 }
 return -1
}

func createS4(sOrderForm string) S4 {
  for i:=0;i<24;i++ {
   if(sOrderForm==g_S4Name[i]){
    return g_S4[i]
	}
  }
  return S4{0,0,0,0}
 }
 
func A4Set()[]S4{
 //ret:=createS4("(1)"),createS4("(123)"),createS4("(132)"),createS4("(134)"),createS4("(143)"),createS4("(124)"),createS4("(142)"),createS4("(234)"),createS4("(243)"),createS4("(12)(34)"),createS4("(13)(24)"),createS4("(14)(23)")
 ret:=[]S4{}
 for _, v := range g_S4 {
	if(v.Tau()%2==0){
	  ret = append(ret,v)
	}
 }
 return ret
}

func D4Set()[]S4{
 ret:=[]S4{createS4("(1)"),createS4("(1234)"),createS4("(13)(24)"),createS4("(1432)"),createS4("(13)"),createS4("(12)(34)"),createS4("(24)"),createS4("(14)(23)")}
 return ret
}

func C4Set()[]S4{
 ret:=[]S4{createS4("(1)"),createS4("(1234)"),createS4("(13)(24)"),createS4("(1432)")}
 return ret
}

func C2C2Set()[]S4{
 ret:=[]S4{createS4("(1)"),createS4("(12)(34)"),createS4("(13)(24)"),createS4("(14)(23)")}
 return ret
}

func C2Set()[]S4{
 ret:=[]S4{createS4("(1)"),createS4("(12)(34)")}
 return ret
}

func S3Set()[]S4{
 ret:=[]S4{createS4("(1)"),createS4("(12)"),createS4("(13)"),createS4("(23)"),createS4("(123)"),createS4("(132)")}
 return ret
}

// 置换群D4的极大偶置换子群（A4和D4的交集）
func EvenPermutationSet(D4 *[]S4)[]S4{
 ret:=[]S4{}
 for _, v := range (*D4) {
	if(v.Tau()%2==0){
	  ret = append(ret,v)
	}
 }
 return ret
}

func EvenPermutationMulTable(D4 *[]S4)[][]int{
 ret:=[][]int{}
 vAD4:=EvenPermutationSet(D4)
 m:=len(vAD4)
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=vAD4[i].Mul(vAD4[j])
   ij:=IJ.Idx(&vAD4)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
}

func A4MulTable()[][]int{
 ret:=[][]int{}
 vA4:=A4Set()
 m:=len(vA4)
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=vA4[i].Mul(vA4[j])
   ij:=IJ.Idx(&vA4)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
} 
 
func S4MulTable()[][]int{
 ret:=[][]int{}
 m:=24
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=g_S4[i].Mul(g_S4[j])
   ij:=IJ.Idx(&g_S4)
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
   
func test1(n int){
//n:=4
var i,j,k,p int
for i = 1; i <=n; i++ {
for j = 1; j <=n; j++ {
if(i!=j){
for k = 1; k <=n; k++ {
if((k!=i)&&(k!=j)){ 
for p = 1; p <=n; p++ { 
if((p!=i)&&(p!=j)&&(p!=k)){
fmt.Println(i,j,k,p)
} 
}
}
}//end for k
}//end for if(i!=j)
}//end for j
}//end for i
}

func main() {
//test1(4)
 //var a S4
 //fmt.Println(a,a.getName())
 vvS4:=S4MulTable()
 PrintMulTable(vvS4)
 WriteMulTable(vvS4,"S4")
 fmt.Println("逆序数:") 
 for _, v := range g_S4 {
	fmt.Printf("%d ",v.Tau())
 }
 fmt.Println() 
 vvA4:=A4MulTable()
 PrintMulTable(vvA4)
 WriteMulTable(vvA4,"A4")  
 fmt.Println("D4逆序数:") 
 vD4:=D4Set()
 for _, v := range vD4 {
	fmt.Printf("%d ",v.Tau())
 } 
 fmt.Println()  
 fmt.Println("置换群D4的极大偶置换子群V")  
 vvAD4:=EvenPermutationMulTable(&vD4)
 PrintMulTable(vvAD4)
 WriteMulTable(vvAD4,"AD4")
 fmt.Println("C4逆序数:") 
 vC4:=C4Set()
 for _, v := range vC4 {
	fmt.Printf("%d ",v.Tau())
 } 
 fmt.Println()  
}