package main

import "fmt"

func test(a int, b int)(max, min int) {
	if a > b {
		return a, b
	}else{
		return b, a
	}
}

func main() {
	max, min := test(19,1)
	fmt.Printf("max: %d, min: %d\n", max, min)

	max1, min1 := test(1,10)
	fmt.Printf("max1: %d, min1: %d\n", max1, min1)
}
