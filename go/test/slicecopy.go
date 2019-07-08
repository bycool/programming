package main

import "fmt"

func main () {
	src := []int{1,3,4}
	dst := []int{6,6,6,6,6}

	fmt.Printf("src: len: %d, cap: %d\n", len(src), cap(src))
	fmt.Printf("dst: len: %d, cap: %d\n", len(dst), cap(dst))

	//copy(dst, src)
	copy(src, dst)
	fmt.Printf("src: len: %d, cap: %d\n", len(src), cap(src))
	fmt.Printf("dst: len: %d, cap: %d\n", len(dst), cap(dst))
	fmt.Println(src)
}
