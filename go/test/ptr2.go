package main

import "fmt"

func test(arr *[5]int) {
	for _,a := range arr {
		fmt.Println(a)
	}
}

func main () {
	var arr [5]int
	arr[0] = 1
	arr[1] = 4
	arr[2] = 2
	arr[3] = 7
	arr[4] = 8
	test(&arr)
}
