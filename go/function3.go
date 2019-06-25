package main

import "fmt"

type person struct {
	name string
	age  int
}

func (p *person) setpinfo(name string, age int) {
	p.name = name
	p.age = age
}

func (p person) setvinfo(){
	fmt.Println("setvinfo")
}

func main () {
	p1 := &person{"dong", 21}
	p1.setpinfo("jian",31)
	fmt.Println("p1: ", p1)

	p1.setvinfo()
}
