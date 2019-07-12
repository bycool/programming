package main

import (
	"fmt"
)

func testa() {
	fmt.Println("aaaaaaaaaaaaa")
}

func testb(x int) {


	defer func() {
		if err:=recover(); err!=nil {
			fmt.Println(err)
		}
	}()

	arr := [10]int{}
	arr[x] = 1
	fmt.Println("bbbbbbbbbbbbb")
}

func main() {
	testa()
	testb(2)
}
