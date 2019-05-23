package main

import "fmt"

func main() {
	const (
		a = 10
		b = 20
		c = 30
	)

	fmt.Printf("a:%d, b:%d, c:%d\n", a, b, c)

	d := 40
	e := 50
	f := 60

	fmt.Printf("d:%d, e:%d, f:%d\n", d, e, f)
	fmt.Printf("d:%x, e:%x, f:%x\n", &d, &e, &f)
	
}
