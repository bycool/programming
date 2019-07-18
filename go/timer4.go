package main

import (
	"fmt"
	"time"
)

func main () {
	timer := time.NewTimer(3*time.Second)

	flage := timer.Reset(4*time.Second)
	fmt.Println(flage)

	time.Sleep(2*time.Second)
	fmt.Println("sleep 2 second")

	<-timer.C
	fmt.Println("time up")
}
