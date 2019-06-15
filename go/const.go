package main

import "fmt"

func main() {
	const a int = 10
	// a = 20  尝试修改是报错
	fmt.Printf("a: %d, %T\n", a, a)

	const b int = 10
//	b = 10
	fmt.Printf("b: %d, %T\n", b, b)

	const c = 20
	fmt.Printf("c: %d, %T\n", c, c)

	const d = 20.123
	fmt.Printf("d.type : %T\n", d)
	fmt.Println("d: ", d)
}
