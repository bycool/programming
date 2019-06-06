package main

import "fmt"

func main() {
	const (
		a = iota
		b = iota
		c = iota
		d = iota
	)

	fmt.Printf("a: %d, b: %d, c: %d, d: %d\n", a, b, c, d);
}
