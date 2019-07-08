package main

import . "fmt"

func test1() {
	Println("1")
	defer Println("2")
	defer Println("3")
	Println("4")
	defer Println("5")
	Println("6")
}

func main() {
	defer Println("a")
	test1()
	Println("b")
}
