package main

import "fmt"

type student struct {
	id   int
	name string
	age  int
}

func main() {
	var s student
	s.id = 1
	s.name = "mike"
	s.age = 18
	fmt.Println("s: ", s)

	var t *student
	t = &s
	t.id = 2
	(*t).name = "jack"
	fmt.Println("t: ", t)

    s3 := new(student)
    s3.id = 2
    s3.name = "john"
    s3.age = 20
    fmt.Println("s3: ", s3)

	s4 := student{3,"jia",31}
	s4.name = "jian"
	fmt.Println("s4: ",s4)

}
