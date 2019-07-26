package main

import (
	"fmt"
	"time"
	"sync"
)

var tickes int = 6
var l sync.Mutex

func seller(number int, ch chan){
	for {
		l.Lock()
		if tickes <= 0 {
			l.Unlock()
			break
		}
		tickes--
		time.Sleep(time.Second)
		fmt.Printf("seller %d, tickes %d\n", number, tickes)
		l.Unlock()
	}
	fmt.Printf("seller %d quit\n", number)
	ch<-number
}

func main() {
	ch1 = make(chan int, 1)
	ch2 = make(chan int, 1)
	ch3 = make(chan int, 1)

	go seller(1)
	go seller(2)
	go seller(3)

	

	for {

	}
}
