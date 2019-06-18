package main

import "fmt"

func main() {
	a := 666
	s := "make"

	func(){
		a = 777
		s = "file"
		fmt.Printf("%d, %s\n", a, s)
	}()

	fmt.Printf("%d, %s\n", a, s)
}
