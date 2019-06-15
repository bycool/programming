package main

import "fmt"

func main() {
	var a int = 1

	fmt.Println("1")

	if a == 1 {
		goto ret
	}

	fmt.Println("2")

ret:
	fmt.Println("ret")
}
