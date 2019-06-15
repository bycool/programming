package main

import "fmt"

func main() {
	var flag bool
	flag = true
	fmt.Printf("%d\n", flag)
	fmt.Printf("%t\n", flag)
//	fmt.Printf("%d\n", int(flag))   bool不能转变int

	var ch byte
	ch = 'a'
	fmt.Println(int(ch))
}
