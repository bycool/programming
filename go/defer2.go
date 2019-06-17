package main

import "fmt"

func main() {
	a := 20
	b := 30

	defer func(a, b int) {
		fmt.Printf("a: %d, b: %d\n", a, b)
	}(a, b)

	a = 222
	b = 333

	fmt.Printf("a: %d, b: %d\n", a, b)
	
}
