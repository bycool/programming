package main

import "fmt"
import "time"

func main () {
	ch := make(chan int)

	var writeCh chan<- int = ch
	var readCh <-chan int = ch

	go func() {
		ch<-555
		fmt.Println("child.ch:555")
		writeCh<-222
		fmt.Println("child.writech:222")
	}()

	num := <-ch
	fmt.Println("main.ch: ", num)
	num = <-readCh
	fmt.Println("main.readCh: ", num)
	time.Sleep(time.Second)
}
