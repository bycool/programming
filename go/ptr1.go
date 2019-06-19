package main

import "fmt"

func main() {
	var a int = 10
	fmt.Printf("val: %d, addr: %p\n", a, &a)

	var b *int = &a
	fmt.Printf("val: %d\n", *b)

	*b = 555
	fmt.Printf("val: %v\n", *b)
	fmt.Printf("val: %d, addr: %p\n", a, &a)
}
