package main

import "fmt"

type student struct {
	name	string
	id		int
}

func main () {
	i := make([]interface{}, 3)
	i[0] = 1 //
	i[1] = "hello go"
	i[2] = student{"make", 66}

	for idx, data := range i {
		fmt.Printf("idx: %d,%T, %v\n", idx, data, data)
	}

	fmt.Println(i)

	var i1 interface{};
	i1 = 1
	fmt.Println(i1)
	i1 = "string"
	fmt.Println(i1)
	i1 = student{"make", 11}
	fmt.Println(i1)
}
