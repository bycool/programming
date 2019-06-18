package main

import "fmt"

func main() {

	defer fmt.Println("bbbbbbbbbbbbbbbbbb")
	defer fmt.Println("aaaaaaaaaaaa")
	defer fmt.Println("cccccccccccccccccccc")
	defer fmt.Println("dddddddddddddd")
	fmt.Println("ffffffffffffff")
}
