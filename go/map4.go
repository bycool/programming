package main

import . "fmt"

func test(m map[int]string) {
	delete(m ,1)
}

func main() {
	m := make(map[int]string, 5)
	m[0] = "m0"
	m[1] = "m1"
	m[2] = "m2"
	m[3] = "m3"
	m[4] = "m4"
	Println("m: ", m)
	test(m)
	Println("m: ", m)
}
