package main

import (
	"fmt"
	"time"
)

var ch = make(chan int)   //1.创建channel，无阻塞的channel

func printer(msge string) {
	for _,c := range msge {
		fmt.Printf("%c", c)
		time.Sleep(time.Second)
	}
	fmt.Printf("\n")
}

func person1(msge string) {
	printer(msge)
	ch <- 111				//3,因为person2阻塞，所以printer先被person1调用，执行完之后，person1写入数据到channel，所以person2，会从阻塞到执行状态，进行printer的调用
}

func person2(msge string) {
	<-ch                    //2.此处读取channel，因为没数据，所以阻塞。
	printer(msge)
}

func main () {
	go person2("world")
	go person1("hello")

	for {

	}
}
