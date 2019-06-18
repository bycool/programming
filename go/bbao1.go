package main

import "fmt"

func main() {
	a := 10
	str := "make"

	f1 := func() {   //定义
		fmt.Println(a)
		fmt.Println(str)
	}

	f1()  //调用

	f2 := func(i, j int) {
		fmt.Printf("i: %d, j: %d\n", i, j)
	}
	f2(1,2)

	func(i, j int) {   //函数体后直接加实参，说明函数是匿名函数
		fmt.Printf("i: %d, j: %d\n", i, j)
	}(3,4)

	//匿名函数有参数有返回值
	x, y := func(i, j int) (max int, min int) {
		if i> j {
			max = i
			min = j
		}else{
			max = j
			min = i
		}
		return max, min
	}(5,6)

	fmt.Printf("x: %d, y: %d\n", x, y)
}
