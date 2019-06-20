package main

import . "fmt"

func main() {
	srcslice := []int{1,2}
	dstslice := []int{6,6,6,6,6}

	copy(dstslice, srcslice)

	Println("dstslice: ", dstslice)
}
