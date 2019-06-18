package main

import "fmt"

type FuncType func(int, int) int

func add(a int, b int) int {
	return a + b
}

func minus(a int, b int) int {
	return a - b
}

func Cale(a int, b int, funct FuncType) int {
	return funct(a, b)
}

func main(){
	var result int
	result = Cale(10, 20, add)
	fmt.Println(result)
	result = Cale(30, 20, minus)
	fmt.Println(result)
}
