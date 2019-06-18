package main

import "fmt"

func test1(p *[5]int) {
	(*p)[0] = 666
	fmt.Println("test: ", *p)
}
func test2(p [5]*int) {  //?
	p[0] = new(int)
	*(p[0]) = 666
	fmt.Println("test: ", *(p[0]))
}

func main() {
	a := [5]int{1,2,3,4,5}
	test1(&a)
	fmt.Println("main: ", a)
}
