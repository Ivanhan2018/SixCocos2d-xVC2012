package main

import (
"fmt"
"os"
"strconv"
)

// 生成循环群C_n的凯莱表
func main() {
	var sz string
	if(len(os.Args)<2){
		fmt.Printf("请输入循环群C_n的阶n：")
		fmt.Scanf("%s",&sz)
	}else{
		sz=os.Args[1]
	}

	n,err := strconv.Atoi(sz)
	if err != nil {
		panic(err)
	}
	var sz1 string
	sz1 = fmt.Sprintf("C%d.txt",n)

	f, err := os.OpenFile(sz1, os.O_RDWR|os.O_CREATE, os.ModePerm)
	if err != nil {
		panic(err)
	}
	defer f.Close()
	
	var buf string
	for i:=0;i<n;i++{
		for j:=i;j<i+n;j++{
			buf = fmt.Sprintf("%d ",j%n+1)
			f.WriteString(buf)
		}
		f.WriteString("\n");
	}
}