package main

import "fmt"

func main() {
	array := []int{1,2,3,0,0,0}
	slice := array[0:3:5]
	fmt.Println(slice)

	a := []int{1,2,3,4,5,0,0,0,0,0}
	s := a[1:4:9]
	fmt.Println("s:", s)
	fmt.Printf("len(s):%d\n", len(s))
}
