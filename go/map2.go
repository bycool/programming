package main

import "fmt"

func main() {
	m1 := map[int]string{0:"str0", 1:"str1", 2:"str2"}
	fmt.Println("m1: ", m1)
	m1[2] = "string"
	fmt.Println("m1: ", m1)
}
