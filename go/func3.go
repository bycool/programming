package main

import "fmt"

func test(args ...int){
	fmt.Println("len(args): ", len(args))
	for i:=0; i<len(args); i++ {
		fmt.Printf("args[%d]: %d\n", i, args[i])
	}
	fmt.Println("------------------------------")
	for _,data := range args {
		fmt.Printf(": %d\n", data)
	}
}

//func test1(args ...int, a int)  //error  a必须在...int列表里

//func test2(args ...int, s string)  // error 不同类型的参数同样必须在列表内，？

func test3(a int, args ...int) {  //ok  不在不定参数列表内的参数要写在不定参数列表前面
	fmt.Println(a)
	
	fmt.Println("len(args): ", len(args))
	for i:=0; i<len(args); i++ {
		fmt.Printf("args[%d]: %d\n", i, args[i])
	}
}

func test4(a string, args ...int) {
	fmt.Println(a)
	
	fmt.Println("len(args): ", len(args))
	for i:=0; i<len(args); i++ {
		fmt.Printf("args[%d]: %d\n", i, args[i])
	}
}

func test5(args ...int) {
	fmt.Printf("test5\n")
	test(args...)
}

func test6(args ...int) {
	fmt.Printf("===============================test6\n")
	test(args[2:4]...)  //args[:]  :前的数字是从这个数字位置开始向后全都传递
                                 // 冒号后的数字表示从0位置到该数字位置的参数为止。
	
}

func main() {
	//test()
	//test4("hello",2,3,4)
	//test5(1,2,3,4,5,6)
	test6(1,2,3,4,5,6, 7, 8, 9)
}
