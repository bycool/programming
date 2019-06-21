package main

import "fmt"

type person struct {
	name string
	age  int
	sex  byte
}

type student struct {
	person    //匿名字段
	id    int
	class int
	grade int
}

func main() {
	var s1 student = student{person{"jian", 30, 'm'}, 1, 2, 3}
	fmt.Println("s1: ", s1)
	fmt.Println(s1.name, s1.age, s1.id, s1.class)   //匿名字段的操作  

	s2 := student{person{"jian", 30, 'm'}, 1, 2, 3}
	fmt.Println("s2: ", s2)

	s3 := student{id:1}
	fmt.Println("s3: ", s3)

	

}

