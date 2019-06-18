package main

import "fmt"

func test(arr  [5]int){
	arr[0] = 666
	fmt.Println("test: ", arr)
}

func main() {
	a := [5]int{1,2,3,4,5}
	test(a)
	fmt.Println("main: ", a)
}
