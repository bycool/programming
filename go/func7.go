package main

import "fmt"

func test3(a int) {
	fmt.Println("a:", a)
}

func test2(b int) {
	test3(b-1)
	fmt.Println("b:", b)
}

func test1(c int) {
	test3(c-1)
	fmt.Println("c:", c)
}

func test(d int) {
	test1(d-1)
	fmt.Println("d:", d)
}

func main() {
	test(5)
	fmt.Println("val:5")
}
