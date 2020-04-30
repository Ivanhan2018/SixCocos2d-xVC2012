package main
 
import (
    "fmt"
)

func main() { 
	var n int=-1046
	switch (n){
	case -1046:
		var s="武王元年（-1046）牧野之战。"
		fmt.Println(s)
	case -1045:
		var s="武王二年（-1045）武王安抚殷民，分封诸侯。"
		fmt.Println(s)
	default:
		var s="没有记录这一年的大事。"
		fmt.Println(s)
	}
}	