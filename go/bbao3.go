package main

import "fmt"

func test02() int {
	var x int
	x++
	return x*x
}

func test01() func() int {
	var x int
	return func() int {
		x++;
		return x*x
	}
}



func main() {
	test02()
	fmt.Printf("%d\n", test02())

	f := test01()
	fmt.Printf("%d\n", f())
	fmt.Printf("%d\n", f())
	//虽然x为test01的局部变量，但是被func()闭包函数使用，则它不会在最后一次func调用完前被释放掉，也不会被重新初始化
}
