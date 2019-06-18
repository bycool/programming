package main

import "fmt"

func main() {
	a := [5]int{}
	fmt.Printf("0.len: %d, cap: %d\n", len(a), cap(a))

	s := []int{}
	fmt.Printf("1.len: %d, cap: %d\n", len(s), cap(s))
	s = append(s, 1)
	fmt.Printf("2.len: %d, cap: %d\n", len(s), cap(s))
}
