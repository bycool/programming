package main

import "fmt"

type person struct {
	name string
	age  int
}

type student struct {
	person  //结构体的匿名字段
	int     //基础类型的匿名字段
	name string
}

func main() {
	s := student{person{"jian", 12}, 666, "dong"}
	fmt.Println("s: ", s)
	fmt.Printf("s: %v\n", s)

	fmt.Printf("s.int: %d\n", s.int)
	fmt.Println(s.person, s.int)
}

