package main

import "fmt"

type person struct {
	name string
	age  int
}

func (tmp person) printinfo() {
	fmt.Println(tmp)
}

func (tmp *person) setinfo(n string, i int) {
	tmp.name = n
	tmp.age = i
}

func (tmp person) setinfo1(n string, i int) {
	tmp.name = n
	tmp.age = i
}

func main() {
	p1 := person{"jiand", 20}
	p1.printinfo()

	p1.setinfo("dong",30)
	p1.printinfo()

	p1.setinfo1("dong1",301)
	p1.printinfo()
}
