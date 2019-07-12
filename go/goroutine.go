package main

import (
	"fmt"
	"time"
)

func newtask() {
	for {
		fmt.Println("this is newtask")
		time.Sleep(time.Second)
	}
}

func main () {

	go newtask()

	for {
		fmt.Println("this is main goroutine")
		time.Sleep(time.Second)
	}
}


