package main

import (
	"fmt"
	"time"
)

func main () {
	var ch = make(chan int)

	go func () {
		for i:=0; i<5; i++ {
			fmt.Println("bef, ch<-", i)
			ch<-i
			time.Sleep(time.Second)
		}
		close(ch)
		fmt.Println("close(ch)")
	}()

	for num:=range ch {
		time.Sleep(time.Second)
		fmt.Println("num: ", num)
	}
	time.Sleep(time.Second)
}
