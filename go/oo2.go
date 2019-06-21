package main

import "fmt"

type person struct {
	name string
	age  int
}

type student struct {
	person
	id   int
	name string
}

func main() {
	var s student
	s.name = "jian"
	s.age = 19
	s.person.name = "dong"
	fmt.Println("s: ", s)
}
