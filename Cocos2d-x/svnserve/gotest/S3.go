package main
 
import (
    "fmt"
    "os"	
)

type S3 struct {
   m_a1,m_a2,m_a3 int
}

//能反映元素阶的置换表达式("描述折线过程")，区别于双行置换表达式("描述折线结果")
var g_S3Name []string=[]string{
"I=(1)",
"r=(231)",
"rr=(132)",
"f=(13)",
"fr=(23)",
"frr=(12)"};

//双行置换表达式
var g_S3 []S3=[]S3{
   S3{1,2,3},
   S3{2,3,1},
   S3{3,1,2},
   S3{3,2,1},
   S3{1,3,2},
   S3{2,1,3}}
 
func (this *S3) isEqual(a S3) bool {
  return (this.m_a1==a.m_a1 && this.m_a2==a.m_a2 && this.m_a3==a.m_a3)
 }
   
func (this *S3) getName() string {
  for i:=0;i<6;i++ {
   if(this.isEqual(g_S3[i])){
    return g_S3Name[i];
	}
  }
  return "Error";
}

func (this *S3) Mul(a S3) S3 {
  var aArr[3]int=[3]int{a.m_a1,a.m_a2,a.m_a3}
  var ret S3
  ret.m_a1=aArr[this.m_a1-1]
  ret.m_a2=aArr[this.m_a2-1]
  ret.m_a3=aArr[this.m_a3-1]
  return ret
 }
 
func (this *S3) InvMul() S3 {
  for i:=0;i<6;i++ {
   var t S3=this.Mul(g_S3[i])
   if(t.isEqual(g_S3[0])){
    return g_S3[i]
	}
  }
  return S3{0,0,0}
 }
 
 //群元的逆序数
func (this *S3) Tau() int {
  var aArr[3]int=[3]int{this.m_a1,this.m_a2,this.m_a3}
  var ret int=0
  for i:=0;i<3;i++ {
	  for j:=i+1;j<3;j++ {
	   if(aArr[i]>aArr[j]){
		ret++
		}
	  }
  }
  return ret
 }
 
//群元索引
func (this *S3) Idx(v *[]S3) int {
  for i:=0;i<6;i++ {
   if(this.isEqual((*v)[i])){
    return i
	}
  }
  return -1
 } 
 
//群元的阶
func getOrder(idx,m S3) int {
 var t S3=idx
  for i:=1;i<=6;i++ {
  t=t.Mul(m)
  if(t.isEqual(idx)){
   return i
   }
 }
 return -1
}

func createS3(sOrderForm string) S3 {
  for i:=0;i<6;i++ {
   if(sOrderForm==g_S3Name[i]){
    return g_S3[i]
	}
  }
  return S3{0,0,0}
 }
 
func A3Set()[]S3{
 ret:=[]S3{}
 for _, v := range g_S3 {
	if(v.Tau()%2==0){
	  ret = append(ret,v)
	}
 }
 return ret
}

func A3MulTable()[][]int{
 ret:=[][]int{}
 vA3:=A3Set()
 m:=len(vA3)
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=vA3[i].Mul(vA3[j])
   ij:=IJ.Idx(&vA3)
   I = append(I,ij+1)
  }
  ret = append(ret,I)
 }
 return ret
}
 
func S3MulTable()[][]int{
 ret:=[][]int{}
 m:=6
 for i:=0;i<m;i++{
  I:=[]int{}
  for j:=0;j<m;j++{
   IJ:=g_S3[i].Mul(g_S3[j])
   ij:=IJ.Idx(&g_S3)
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
 vvS3:=S3MulTable()
 PrintMulTable(vvS3)
 WriteMulTable(vvS3,"S3")
 fmt.Println("逆序数:") 
 for _, v := range g_S3 {
	fmt.Printf("%d ",v.Tau())
 }
 fmt.Println() 
 vvA3:=A3MulTable()
 PrintMulTable(vvA3)
 WriteMulTable(vvA3,"A3") 
}