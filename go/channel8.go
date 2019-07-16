package main

import (
	"fmt"
)

func producter(ch chan<- int) {
	for i:=0; i<10; i++ {
		ch<-i*i
	}
	close(ch)
}

func consumer(ch <-chan int) {
	for num:= range ch {
		fmt.Println(num)
	}
}

func main () {
	ch := make(chan int)

	go producter(ch)

	consumer(ch)
}
