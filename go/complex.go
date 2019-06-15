package main

import "fmt"

func main() {
	var t complex128
	t = 2.1 + 3.14i
	fmt.Println("t: ", t)

	fmt.Println(real(t))
	fmt.Println(imag(t))
}
