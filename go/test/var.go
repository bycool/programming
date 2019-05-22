package main

import "fmt"

func main() {
	a := 10
	fmt.Printf("a = %d\n", a)

	var b, c int
	b = 20
	c = 30
	fmt.Printf("b: %d, c: %d\n", b, c);

	const (
		e = 40
		f = 50
	)
	fmt.Printf("e: %d, f: %d\n", e, f)
}
