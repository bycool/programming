package main

import "fmt"

func main() {
	s1 := []int{1,2,3,4}
	fmt.Println("S1:", s1)

	s2 := make([]int, 5, 10) //type len cap
	fmt.Println("S2:", s2)

}
