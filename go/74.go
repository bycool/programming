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
//	p1 := person{"jiand", 21}
//	p1.printinfo()

//	f1 := p1.printpinfo  //方法值:取得类型实体变量内的方法，运行，这个方法隐藏了这个实体变量。
//	f1()

	f2 := (*person).printpinfo //方法表达式：获取类型的方法(可以没有类型的实体变量)， 将一个类型的变量给获取的方法。
	p1 := person{"jiand", 21}
	f2(&p1)

}
