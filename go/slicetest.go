package main

import "fmt"

func display(s []int) {
	fmt.Println(s)
}

func main() {
	s := []int{5,4,3,2,1}
	s = append(s,1)
	s = append(s,2)
	s = append(s,3)
	s = append(s,4)
	s = append(s,5)
	display(s)
}
