package main

import "fmt"

func main () {
	var a int = 20

	var pa *int
	pa = &a

	fmt.Println(*pa)
	fmt.Println(pa)

	*pa = 30
	fmt.Println(a)

	var pb *int = new(int)
	*pb = 40
	fmt.Println(*pb)

	var arr [5]int
	arr[0] = 1
	arr[1] = 2
	arr[2] = 3
	arr[3] = 4
	arr[4] = 5
	var par *[5]int
	par = &arr
	fmt.Println(par)
	
}
