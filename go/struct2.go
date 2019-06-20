package main

import "fmt"

type student struct {
	id    int
	name  string
	sex   byte
	age   int
}

func main() {
	var s1 *student = &student{1,"hello", 'm', 10}
	fmt.Println("s1: ", s1)

	s2 := &student{name:"hello", age:18}
	fmt.Println("s2: ", s2)

}
