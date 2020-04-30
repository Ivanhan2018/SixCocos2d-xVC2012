package main
import "fmt"
import "net/http"

func SayHello(w http.ResponseWriter,r *http.Request){
    w.Write([]byte("hello"))
}

func main(){
    http.HandleFunc("/hello",SayHello)
    http.ListenAndServe(":1234",nil)
    fmt.Println("Hello World!")
}