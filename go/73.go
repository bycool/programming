package main

import "fmt"

type person struct {
	name string
	age  int
}

func (tmp *person) printinfo() {
	//fmt.Printf("name = %s, age = %d\n", tmp.name, tmp.age)
	fmt.Printf("p: %p %v\n", tmp, tmp)
}

func (tmp person) printpinfo() {
	fmt.Printf("p: %p, %v\n", &tmp, tmp)
}

func main() {
	p1 := person{"jiand", 21}
	p1.printinfo()

	funcp := p1.printinfo
	funcp()

	p1.printpinfo()
	funcpp := p1.printpinfo
	funcpp()

}
