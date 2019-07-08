package main

import "fmt"

func main () {
	var a []int = []int{1,2,3,4,5,6}
	fmt.Printf("type: %T\n", a)


	a = append(a, 6)
	a = append(a, 6)
	fmt.Printf("cap(a): %d\n", cap(a))
	fmt.Printf("len(a): %d\n", len(a))
	a = append(a, 6)


	for _, d := range a {
		fmt.Println(d)
	}
}
