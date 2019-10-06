package main

import "fmt"

//接口的定义
type ISayHello interface {
   sayHello()
}

//接口的实现
//美国人
type AmericalPerson struct {}
func (person AmericalPerson)sayHello(){
   fmt.Println("Hello！")
}
//接口的实现
//中国人
type ChinesePerson struct {}
func (person ChinesePerson)sayHello(){
   fmt.Println("你好！")
}

func greet(i ISayHello){
   i.sayHello()
}

func main() {
   ameriacal := AmericalPerson{}
   chinese := ChinesePerson{}
   var i ISayHello
   i = ameriacal
   i.sayHello()
   i = chinese
   i.sayHello()
}