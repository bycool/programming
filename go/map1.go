package main

import . "fmt"

func main() {
	var m1 map[int]string
//	m1[0] = "m1.0" //error map is nil
	Println("m1: ", m1)
	Printf("len(m1) :%d\n", len(m1))

	m2 := make(map[int]string)
	Println("m2: ", m2)
	Printf("len(m2) :%d\n", len(m2))

	m3 := make(map[int]string, 10)
	m3[0] = "str0"
	m3[1] = "str1"
	m3[2] = "str2"
	Println("m3:" , m3)
	Printf("len(m3) :%d\n", len(m3))

	m4 := map[int]string{0:"str0", 1:"str1", 2:"str2"}
	Println("m4:" , m4)
	Printf("len(m4) :%d\n", len(m4))
	
}
