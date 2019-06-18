package main

import "fmt"

func test(a int, b int) {
	fmt.Println("a:", a)
	fmt.Println("b:", b)
}

func test(a int, b int, c int) { //error
	fmt.Println("a:", a)
	fmt.Println("b:", b)
	fmt.Println("c:", c)
}

func main() {
	test(1,2, 3)
}
