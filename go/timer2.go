package main

import (
	"fmt"
	"time"
)

func main () {
	
	fmt.Println(time.Now());
	<-time.After(2*time.Second)
	fmt.Println(time.Now());
}

func main02 () {

	fmt.Println(time.Now());
	time.Sleep(2*time.Second)
	fmt.Println(time.Now());
}

func main01 () {

	fmt.Println(time.Now());
	timer := time.NewTimer(2*time.Second)
	<-timer.C
	fmt.Println(time.Now());
}
