package main

import "fmt"

//面向过程的func
func Add1(a, b int) int {
	return a + b
}

//面向对象func,给某个类型绑定一个函数
type long int
func (tmp long)Add2(other long) long {
	return tmp + other
}

func main() {
	var result int
	result = Add1(1, 1)
	fmt.Println(result)

	var a long
	a = 1
	a.Add2(1)
	fmt.Println(a)
	a = a.Add2(1)
	fmt.Println(a)
}
