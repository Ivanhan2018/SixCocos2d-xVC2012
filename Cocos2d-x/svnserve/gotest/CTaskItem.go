package main
 
import (
    "fmt"
    "sort"
)

// 任务记录
type CTaskItem struct {
	m_nTaskID int
	m_strTaskName string //任务名称
	m_nTaskLevel int //任务等级
	m_nTaskState int //任务状态
}

type TaskItemSlice [] CTaskItem
 
func (a TaskItemSlice) Len() int {    // 重写 Len() 方法
    return len(a)
}
func (a TaskItemSlice) Swap(i, j int){     // 重写 Swap() 方法
    a[i], a[j] = a[j], a[i]
}
func (a TaskItemSlice) Less(i, j int) bool {    // 重写 Less() 方法， 按m_nTaskID从小到大排列顺序
	  if(a[i].m_nTaskID != a[j].m_nTaskID){
		  return a[i].m_nTaskID < a[j].m_nTaskID
		}else{
		  return a[i].m_nTaskState < a[j].m_nTaskState
		  }
}

type TaskItemWrapper struct {
    arr [] CTaskItem
    by func(p, q * CTaskItem) bool
}

func (pw TaskItemWrapper) Len() int {    // 重写 Len() 方法
    return len(pw.arr)
}
func (pw TaskItemWrapper) Swap(i, j int){     // 重写 Swap() 方法
    pw.arr[i], pw.arr[j] = pw.arr[j], pw.arr[i]
}
func (pw TaskItemWrapper) Less(i, j int) bool {    // 重写 Less() 方法
    return pw.by(&pw.arr[i], &pw.arr[j])
}

type SortByTaskItem func(p, q *CTaskItem) bool
func SortTaskItem(arr [] CTaskItem, by SortByTaskItem){    // SortTaskItem 方法
    sort.Sort(TaskItemWrapper{arr, by})
}
 
type Person struct {
    Name string    // 姓名
    Age  int    // 年纪
}
 
// 按照 Person.Age 从大到小排序
type PersonSlice [] Person
 
func (a PersonSlice) Len() int {    // 重写 Len() 方法
    return len(a)
}
func (a PersonSlice) Swap(i, j int){     // 重写 Swap() 方法
    a[i], a[j] = a[j], a[i]
}
func (a PersonSlice) Less(i, j int) bool {    // 重写 Less() 方法， 从大到小排序
    return a[j].Age < a[i].Age 
}

type PersonWrapper struct {
    people [] Person
    by func(p, q * Person) bool
}

func (pw PersonWrapper) Len() int {    // 重写 Len() 方法
    return len(pw.people)
}
func (pw PersonWrapper) Swap(i, j int){     // 重写 Swap() 方法
    pw.people[i], pw.people[j] = pw.people[j], pw.people[i]
}
func (pw PersonWrapper) Less(i, j int) bool {    // 重写 Less() 方法
    return pw.by(&pw.people[i], &pw.people[j])
}

type SortBy func(p, q *Person) bool
func SortPerson(people [] Person, by SortBy){    // SortPerson 方法
    sort.Sort(PersonWrapper{people, by})
}
 
func main() {
	m_vecTask := []CTaskItem{}
	m_vecTask = append(m_vecTask,CTaskItem{1,"任务1",1,4})//提交
	m_vecTask = append(m_vecTask,CTaskItem{1,"任务1",1,1})//未接
	m_vecTask = append(m_vecTask,CTaskItem{2,"任务2",1,1})//未接
	m_vecTask = append(m_vecTask,CTaskItem{2,"任务2",1,2})//已接
	m_vecTask = append(m_vecTask,CTaskItem{4,"任务4",1,1})//未接
	m_vecTask = append(m_vecTask,CTaskItem{3,"任务3",1,4})//提交
	
	for k, v := range m_vecTask {
	  fmt.Println(k,v.m_nTaskID,v.m_strTaskName,v.m_nTaskLevel,v.m_nTaskState)	
	}
	
    sort.Sort(TaskItemSlice(m_vecTask))
    fmt.Println(m_vecTask)	
	
    sort.Sort(sort.Reverse(TaskItemSlice(m_vecTask)))
    fmt.Println(m_vecTask)	

	sort.Sort(TaskItemWrapper{m_vecTask, func (p, q *CTaskItem) bool {
	  if(p.m_nTaskID != q.m_nTaskID){
		  return p.m_nTaskID < q.m_nTaskID
		}else{
		  return p.m_nTaskState < q.m_nTaskState
		  }
    }})
    fmt.Println(m_vecTask)
	
    sort.Sort(TaskItemWrapper{m_vecTask, func (p, q *CTaskItem) bool {
        return p.m_nTaskState < q.m_nTaskState
    }})	
    fmt.Println(m_vecTask)
	
    SortTaskItem(m_vecTask, func (p, q *CTaskItem) bool {
	  if(p.m_nTaskID != q.m_nTaskID){
		  return p.m_nTaskID < q.m_nTaskID
		}else{
		  return p.m_nTaskState < q.m_nTaskState
		  }
    })
    fmt.Println(m_vecTask)	
	
    people := [] Person{
        {"zhang san", 12},
        {"li si", 30},
        {"wang wu", 52},
        {"zhao liu", 26},
    }
 
    fmt.Println(people)
 
    sort.Sort(PersonSlice(people))    // 按照 Age 的逆序排序
    fmt.Println(people)
 
    sort.Sort(sort.Reverse(PersonSlice(people)))    // 按照 Age 的升序排序
    fmt.Println(people)
	
	sort.Sort(PersonWrapper{people, func (p, q *Person) bool {
        return q.Age < p.Age    // Age 递减排序
    }})
    fmt.Println(people)
	
    sort.Sort(PersonWrapper{people, func (p, q *Person) bool {
        return p.Name < q.Name    // Name 递增排序
    }})	
    fmt.Println(people)	
	
    SortPerson(people, func (p, q *Person) bool {
        return q.Age < p.Age    // Age 递减排序
    })
    fmt.Println(people)	
}