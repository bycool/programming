package main

import . "fmt"

func main() {
	a := 10
	defer Println(a)
	a = 20
	Println("a: ", a) 
}
