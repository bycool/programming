package main

import "fmt"

func test(a int) {
	fmt.Println(a)
}

func main() {
	test(1)
	defer test(2)
	defer test(3)
	test(4)
}
