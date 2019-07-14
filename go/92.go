package main

import "fmt"
import "time"

func test() {
	for {
		fmt.Println("test")
		time.Sleep(time.Second)
	}
}

func main () {
	go test()
	fmt.Println("go test()")

	for{}
}
