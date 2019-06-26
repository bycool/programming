package main

import "fmt"

type person struct {
	name string
	age  int
}

func (tmp *person) printinfo() {
	fmt.Printf("name = %s, age = %d\n", tmp.name, tmp.age)
}

type student struct {
	person
	id	int
	add	string
}

func (tmp *student) printinfo() {
	fmt.Printf("name = %s, age = %d, id = %d, addr = %s\n", tmp.name, tmp.age, tmp.id, tmp.add)
}

func main() {
	p1 := person{"jiand", 21}
	p1.printinfo()

	s1 := student{person{"dong", 18}, 1, "bj"}
	s1.printinfo()

	s1.person.printinfo()
}
