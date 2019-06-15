package main

import "fmt"

func main() {
	var (
		a int
		b float64
	)
	a, b = 1, 3.14
	fmt.Println("a: ", a)
	fmt.Println("b: ", b)

	const (
		i int = 10
		j float64 = 3.14
	)
	fmt.Println("i: ", i)
	fmt.Println("j: ", j)

	var (
		x = 10
		y = 3.14
	)
	fmt.Println("x: ", x)
	fmt.Println("y: ", y)

	
}
