package main

import "fmt"

func swap1(a, b int) (int, int) {
	var tmp int = a
	a = b
	b = tmp
	return a, b
}

func swap2(a, b *int) {
	var tmp = *a
	*a = *b
	*b = tmp
}

func main() {
	a, b := 10, 20
	fmt.Printf("a, %d, b: %d\n", a, b)
	x, y := swap1(a, b)
	fmt.Printf("a, %d, b: %d\n", a, b) //swap1的a，b型参在swap1内是局部变量，swap1内的a,b是变了，这个ab不是main的ab
	fmt.Printf("x: %d, y: %d\n", x, y)

	swap2(&a, &b)
	fmt.Printf("a, %d, b: %d\n", a, b)
}
