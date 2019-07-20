package main

import "fmt"
import "time"

func main () {

	ch1 := make(chan int)

	go func () {
		for {
		select {
			case num:=<-ch1:
				fmt.Println("child:ch1 : ", num)
		}
		}
	}()

	go func () {
		for i:=0; i<10; i++ {
			fmt.Printf("main. %d->ch1\n", i)
			ch1<-i
			time.Sleep(time.Second)
		}
	}()

	for {
		
	}
}
