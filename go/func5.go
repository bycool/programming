package main

import "fmt"

func test()(int, int, int) {
	return 1,2,3
}

func test1()(a int, b string) {
	a = 1
	b = "string"
	return a, b
}

func main() {
	a,b,c := test()
	fmt.Printf("a:%d, b:%d, c:%d\n", a, b, c)

	a1,b1 := test1()
	fmt.Printf("a1:%d, b1: %s\n", a1, b1)

	a2 := test1()
}
