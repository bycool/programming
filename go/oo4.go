package main

import "fmt"

type person struct {
	name string
	age  int
}

type student struct {
	*person
	id   int
	name string
}

func main() {
	s1 := student{&person{"jian", 30}, 1, "dong"}
	fmt.Println("s1: ",s1)
	fmt.Printf("s1: %v\n", s1)
	fmt.Println(s1.person.name, s1.age, s1.id, s1.name)
}

