package main

import "fmt"

type node struct {
	id int
	age int
	name string
}


func test1(n node) {
	n.id = 2
	n.age = 2
	n.name = "dong"

	fmt.Println("n: ", n)
}

func test2(n *node) {
	n.id = 2
	n.age = 2
	n.name = "dong"

	fmt.Println("n: ", n)
}

func main() {
	a := node{id:1, age:18, name:"jian"}
	fmt.Println("a: ", a)

	test1(a)
	fmt.Println("a: ", a)

	test2(&a)
	fmt.Println("a: ", a)
}
