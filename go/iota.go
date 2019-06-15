package main

import "fmt"

func main() {
	const (
		a = iota
		b = iota
		c = iota
	)
	fmt.Println(a, b, c)

	const (
		a1 = iota
		b1
		c1
	)
	fmt.Println(a1, b1, c1)

	const (
		i = iota
		j1, j2, j3 = iota, iota, iota
		k = iota
	)
	fmt.Println(i)
	fmt.Println(j1, j2, j3)
	fmt.Println(k)
}
