package main

import (
	"fmt"
)

func main () {
	ch := make(chan int)

	go func () {
		for i:=0; i<5; i++ {
			ch<-i
			fmt.Println("i: ", i)
		}
		close(ch)
	}()

	for {
		if num, ok := <-ch; ok==true {
			fmt.Println("num: ", num)
		}else{
			fmt.Println("break")
			break
		}
	}
}
