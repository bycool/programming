package main

import . "fmt"

func main() {
	s1 := []int{}
	Printf("s1.len: %d, s1.cap: %d\n", len(s1), cap(s1))
	Println("s1: ", s1)

	s1 = append(s1, 1)
	s1 = append(s1, 2)
	s1 = append(s1, 3)
	Printf("s1.len: %d, s1.cap: %d\n", len(s1), cap(s1))
	Println("s1: ", s1)

	s2 := []int{1,2,3}
	Printf("s2.len: %d, s2.cap: %d\n", len(s2), cap(s2))
	Println("s2: ", s2)
}
