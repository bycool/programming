package main

import "fmt"

func test()(int) {
	return 66
}

func test1()(result int) { //给返回值一个名字，主要作用就是在函数内隐士声明一个变量，可以返回它，也可以不返回它。
	result = 66
	return result
}

func test2()(result int) { //给返回值一个名字， 
	result = 66
	var a int = 77
	return a
}

func main() {
	var a = test()
	fmt.Println(a)

	var b = test1()
	fmt.Println(b)

	var c = test2()
	fmt.Println(c)
}
