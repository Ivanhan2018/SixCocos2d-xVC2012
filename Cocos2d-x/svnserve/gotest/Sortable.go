package main
 
import (
    "fmt"
)

// 定义可排序接口
type Sortable interface {
   Len() int
   Less(int, int) bool
   Swap(int, int)
}

func BubbleSortable(arr Sortable) {
   length := arr.Len()
   for i := 0; i < length; i++ {
      for j := i; j < length-i-1; j++ {
         if arr.Less(j, j+1) {
            arr.Swap(j, j+1)
         }
      }
   }
}

// Desc=false表示升序,Desc=true表示降序
func BubbleSortableDesc(arr Sortable,Desc bool) {
    n := arr.Len()
	for i := 1; i < n; i++ {
		for j := 0; j < n-i; j++ {
			if arr.Less(j, j+1)==Desc {
				arr.Swap(j, j+1)
			}
	  }
   }
}

// 定义IntArr类型
type IntArr []int
// 给IntArr提供Len方法
func (arr IntArr) Len() int {
    return len(arr)
}
// 给IntArr提供Less方法
func (arr IntArr) Less(i int, j int) bool {
    return arr[i] < arr[j]
}
// 给IntArr提供Swap方法
func (arr IntArr) Swap(i int, j int) {
    arr[i], arr[j] = arr[j], arr[i]
}

type StrArr []string
func (arr StrArr) Len() int {
    return len(arr)
}
func (arr StrArr) Less(i int, j int) bool {
    return arr[i] < arr[j]
}
func (arr StrArr) Swap(i int, j int) {
    arr[i], arr[j] = arr[j], arr[i]
}


func main() {
   intarr := IntArr{2, 3, 1, -9, 0}
   intarr1 :=intarr[:]
   BubbleSortableDesc(intarr,false)
   fmt.Printf("Asc sorted int arr is: %v\n", intarr)
   BubbleSortableDesc(intarr1,true)   
   fmt.Printf("Desc sorted int arr is: %v\n", intarr1)

   strarr := StrArr{"nut", "ape", "elephant", "zoo", "go"}
   strarr1 :=strarr[:]   
   BubbleSortableDesc(strarr,false)
   fmt.Printf("Asc sorted string arr is: %v\n", strarr)
   BubbleSortableDesc(strarr1,true)
   fmt.Printf("Desc sorted string arr is: %v\n", strarr1)  
}