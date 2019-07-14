package main

import (
	"fmt"
	"time"
)

func main () {

	defer fmt.Println("main process finish")

	ch := make(chan string)
	go func () {
		defer fmt.Println("child process finish")

		for i:=0; i<2; i++ {
			fmt.Println("child. i = ", i)
			time.Sleep(time.Second)
		}
		ch <- "hel"
	}()
	<-ch
}
