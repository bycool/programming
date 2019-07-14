package main

import (
	"fmt"
	"time"
)

var ch = make(chan int)

func person1() {
	fmt.Println("person1")
	ch <- 111               //此处写入channel但是也不会马上打印第二个person1,因为person2内延迟10秒读取channel，所以person1也会被阻塞10秒
	fmt.Println("person1")
}

func person2() {
	fmt.Println("person2")
	time.Sleep(10*time.Second)
	num := <-ch
	fmt.Println("num: ", num)
	fmt.Println("person2")
}

func main () {
	go person1()
	go person2()

	time.Sleep(15*time.Second)
}
