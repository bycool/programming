package main 

import "fmt"

func Add(a, b int) int {
	return a + b
}

func Minus(a, b int) int {
	return a - b
}

type FuncType func(int, int) int

func main() {
	var r int
	var ft FuncType
	ft = Add
	r = ft(10, 20)
	fmt.Println(r)
	ft = Minus
	r = ft(20, 10)
	fmt.Println(r)
}
