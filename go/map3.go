package main

import . "fmt"

func main() {
	m := map[int]string{0:"str0", 1:"str1", 2:"str2"}
	for key, val :=  range m {
		Printf("%d: %s\n", key, val)
	}

	val, ok := m[1]
	if ok == true {
		Println("m[1] = ", val, m[1])
	}

	n := make(map[int]string, 10)
	n[0] = "n0"
	n[1] = "n1"
	n[2] = "n2"
	n[3] = "n3"
	n[4] = "n4"
	for key, val :=  range n {
		Printf("%d: %s\n", key, val)
	}
}
