package main

import (
	"fmt"
	"time"
)

var ch = make(chan int, 10)

func producter () {
	for i:=0;;i++ {
		fmt.Println("producter: cap(ch): ", cap(ch), " len(ch): ", len(ch))
		ch <- i
		fmt.Println("producter: ch<-", i)
		time.Sleep(time.Second/5)
	}
}

func customer1 () {
	for {
		fmt.Println("customer1: cap(ch): ", cap(ch), " len(ch): ", len(ch))
		num := <-ch
		fmt.Println("customer1: <-ch : ", num)
		time.Sleep(2*time.Second)
	}
}
func customer2 () {
	for {
		fmt.Println("customer2: cap(ch): ", cap(ch), " len(ch): ", len(ch))
		num := <-ch
		fmt.Println("customer2: <-ch : ", num)
		time.Sleep(2*time.Second)
	}
}

func main () {
	go producter()
	go customer1()
	go customer2()

	for {

	}
}
