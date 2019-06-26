package main

import "fmt"

type humaner interface {
	//方法只有声明，没有实现
	sayhi()
}

type student struct {
	name string
	id   int
}

func (tmp *student) sayhi() {
	fmt.Printf("student{%s, %d} sayhi\n", tmp.name, tmp.id)
}

type person struct {
	age int
	addr string
}

func (tmp *person) sayhi() {
	fmt.Printf("person(%d %s) sayhi()\n", tmp.addr, tmp.age)
}

func whosayhi(i humaner) {
	i.sayhi()
}

func main () {
	var i humaner

	s1 := student{"hello", 18}

	p1 := person{22, "bj"} 

	i = &s1
	i.sayhi()

	i = &p1
	i.sayhi()

	fmt.Println("----------------------")
	whosayhi(&s1)
	whosayhi(&p1)
}
